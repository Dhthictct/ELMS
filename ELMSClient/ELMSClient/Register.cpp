// Register.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ELMSClient.h"
#include "Register.h"
#include "afxdialogex.h"

#include "ELMSClientDlg.h"

// CRegister �Ի���

IMPLEMENT_DYNAMIC(CRegister, CDialogEx)

CRegister::CRegister(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_REGISTER, pParent)
	, m_Edt_Reg_UserName(_T(""))
	, m_Edt_Reg_PassWord(_T(""))
	, m_Edt_Reg_OncePassWord(_T(""))
{

}

CRegister::~CRegister()
{
}

void CRegister::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDT_USERNAME, m_Edt_Reg_UserName);
	DDV_MaxChars(pDX, m_Edt_Reg_UserName, 16);
	DDX_Text(pDX, IDC_EDT_REGPASSEWORD, m_Edt_Reg_PassWord);
	DDV_MaxChars(pDX, m_Edt_Reg_PassWord, 16);
	DDX_Text(pDX, IDC_EDT_REGONCEPASSWORD, m_Edt_Reg_OncePassWord);
	DDV_MaxChars(pDX, m_Edt_Reg_OncePassWord, 16);
	DDX_Control(pDX, IDC_COMBO1, m_cbtable);
}


BEGIN_MESSAGE_MAP(CRegister, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_REGISTER, &CRegister::OnBnClickedBtnRegister)
	ON_BN_CLICKED(IDCANCEL, &CRegister::OnBnClickedCancel)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CRegister ��Ϣ�������


void CRegister::OnBnClickedBtnRegister()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//���ע�����
	USES_CONVERSION;
	UpdateData(TRUE); //��ȡ�ؼ���ֵ
	if (m_Edt_Reg_UserName.IsEmpty() || m_Edt_Reg_PassWord.IsEmpty() || m_Edt_Reg_OncePassWord.IsEmpty())
	{
		//�����һ��Ϊ�գ���ȫ����Ϊ���ˣ�������
		MessageBox(_T("��������ݻ���Ϊ�գ����������룡"), _T("ע����ʾ"), MB_OK | MB_ICONWARNING);
		m_Edt_Reg_UserName = _T("");
		m_Edt_Reg_PassWord = _T("");
		m_Edt_Reg_OncePassWord = _T("");
		UpdateData(FALSE);
		return;
	}


	//�ж��������
	int nUserl, nPwdl, nOPwdl;
	nUserl= m_Edt_Reg_UserName.GetLength();
	nPwdl = m_Edt_Reg_PassWord.GetLength();
	nOPwdl = m_Edt_Reg_OncePassWord.GetLength();
	if (nPwdl < 6 || nOPwdl < 6)
	{
		MessageBox(_T("��������Ϊ��λ\r\n��������"));
		return;
	}
	for (int i = 0; i < nUserl; ++i)
	{
		/*if (('a' <= m_Edt_Reg_PassWord[i] && m_Edt_Reg_PassWord[i] <= 'z') || 
			('A' <= m_Edt_Reg_PassWord[i] && m_Edt_Reg_PassWord[i] <= 'Z') || 
			('0' <= m_Edt_Reg_PassWord[i] && m_Edt_Reg_PassWord[i] <= '9'))
		{
		}*/
		if ('!' <= m_Edt_Reg_PassWord[i] && m_Edt_Reg_PassWord[i] <= '~')
		{

		}
		else
		{
			MessageBox(_T("����ֻ������ĸ�����ֺͱ�����������\r\n��������������"));
			m_Edt_Reg_PassWord = _T("");
			m_Edt_Reg_OncePassWord = _T("");
			UpdateData(FALSE);
			return;
		}
	}
	

	//�Ƚ����������Ƿ�һ��
	if (m_Edt_Reg_PassWord != m_Edt_Reg_OncePassWord)
	{
		MessageBox(_T("���ε��������벻һ�£����������룡"), _T("ע����ʾ"), MB_OK | MB_ICONWARNING);
		//m_Edt_Reg_UserName = _T("");
		m_Edt_Reg_PassWord = _T("");
		m_Edt_Reg_OncePassWord = _T("");
		UpdateData(FALSE);
		return;
	}

	//ת����������CUser������Ϣ
	CUser userInfo;
	userInfo.setUserName(T2A(m_Edt_Reg_UserName));
	userInfo.setPassWord(T2A(m_Edt_Reg_PassWord));

	///�õ������ڵĴ��ھ��
	//��Ϊ�����Ǵ�����ģ̬�Ի������Կ���ʹ���������
	//��ȻҲ����ʹ����Ƶ�е�AfxGetMainWnd()����������Ҫע����һ����������
	CELMSClientDlg* mainDlg = (CELMSClientDlg*)(this->GetParent());//��ȡ�����ڵĴ��ھ��
	//����Э��
	int MSGTYPE = MYMSG_REGISTER;
	//�������ݣ��ȷ���Э�飬�ڽ��û�������Ϣ���͹�ȥ
	mainDlg->m_SockClient.Send(&MSGTYPE, sizeof(MSGTYPE));
	mainDlg->m_SockClient.Send(&userInfo, sizeof(CUser));

	//������һ���������������շ������˴�����������
	bool bRes = false;
	//�������ݣ��õ������ڣ��Ի��򣬿ؼ���Ҳ�Ǵ��ڣ��е��׽���
	mainDlg->m_SockClient.Receive(&bRes, sizeof(bRes));
	if (bRes)
	{
		//�����ж�
		MessageBox(_T("ע��ɹ������μ��û���������"), _T("ע����ʾ"), MB_OK | MB_ICONINFORMATION);
		EndDialog(1001); //�ú��������ر�ģ̬�Ի��򣬲���Ϊ�رյĲ����������������DoModal()�����ķ���ֵ
	}
	else
	{
		//���û�ɹ����һ�Ҫ����ע�ᣬ�ͽ��д���
		if (IDYES == MessageBox(_T("ע��ʧ�ܣ��Ƿ���Ҫ����ע��"), _T("ע����ʾ"), MB_YESNO | MB_ICONERROR))
		{
			m_Edt_Reg_UserName = _T("");
			m_Edt_Reg_PassWord = _T("");
			m_Edt_Reg_OncePassWord = _T("");
			UpdateData(FALSE);
		}
		else
		{
			//û�ɹ�����ע�ᣬ�͹ر����ģ̬�Ի���
			EndDialog(1002);
		}

	}
}


void CRegister::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (IDOK == MessageBox(_T("ע����δ�ɹ������Ҫ�˳���"), _T("ע����ʾ"), MB_OKCANCEL | MB_ICONQUESTION))
		CDialogEx::OnCancel();
}


void CRegister::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CImage img1;
	img1.Load(_T("theme\\1.jpg"));
	CRect clientRect;//�����С��
	GetClientRect(&clientRect);//��ȡ�ͻ����Ĵ�С
	img1.Draw(dc, 0, 0, clientRect.Width(), clientRect.Height());
}


BOOL CRegister::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_cbtable.AddString(_T("��Ա�û�"));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
