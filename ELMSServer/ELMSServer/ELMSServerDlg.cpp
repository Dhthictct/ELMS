
// ELMSServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ELMSServer.h"
#include "ELMSServerDlg.h"
#include "afxdialogex.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "ChangePassword.h"
#include "UserInfo.h"

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CELMSServerDlg �Ի���



CELMSServerDlg::CELMSServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ELMSSERVER_DIALOG, pParent)
	, m_Edt_Username(_T(""))
	, m_Edt_Password(_T(""))
	, m_UserPort(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CELMSServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDT_ADR_USERNAME, m_Edt_Username);
	DDX_Text(pDX, IDC_EDT_ADR_PASSWORD, m_Edt_Password);
}

BEGIN_MESSAGE_MAP(CELMSServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_LOGIN, &CELMSServerDlg::OnBnClickedBtnLogin)
	ON_BN_CLICKED(IDC_BTN_CHANGE, &CELMSServerDlg::OnBnClickedBtnChange)
END_MESSAGE_MAP()


// CELMSServerDlg ��Ϣ�������

BOOL CELMSServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//�����׽��֣������˿ڣ���ʼ����
	BOOL bResult = m_SockListen.Create(9413);
	UINT unError = GetLastError();
	//�����Ĵ���ʧ�ܣ������֣�һ����δ��ʼ��socket��һ���Ƕ˿ڱ�ռ��
	if (unError == WSANOTINITIALISED) //WSANOTINITIALISEDΪ10093
	{
		AfxMessageBox(_T("δ��ʼ���׽�����ػ��ʼ��ʧ�ܣ�")); //����δ����AfxSocketInit��������ʧ��
	}
	if (unError == WSAEADDRINUSE)
	{
		AfxMessageBox(_T("�˿ڱ�ռ�ã�"));
	}
	//��ʼ����
	//Listen��������һ��������Ĭ��ֵΪ5.���������ʾ���������������������ӵ�״̬��
	m_SockListen.Listen();
	

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CELMSServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CELMSServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CELMSServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CELMSServerDlg::OnBnClickedBtnLogin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	USES_CONVERSION; //���������ַ���ת��
	CUserDataBase db;
	db.initDB(); //��ʼ�����ݿ�
	CELMSServerDlg* SrvDlg = (CELMSServerDlg*)AfxGetMainWnd();

	UpdateData(TRUE);
	//�ַ�����ת��
	CString strUserName = m_Edt_Username;
	CString strPassWord = m_Edt_Password;

	//����sql���
	_bstr_t bstrSQL = _T("select * from Administrator");
	_variant_t vUserName, vPassword;

	//����GetRecordSet�������õ���¼��
	_RecordsetPtr & pRes = db.GetRecordSet(bstrSQL);

	try
	{
		//�жϼ�¼�����Ϊ�գ�����false���ݣ�������
		if (pRes == NULL)
		{
			db.closeDB();
			return;
		}
		//����ʹ��adoEOF�Լ�¼�����б���
		while (!pRes->adoEOF)
		{
			vUserName = pRes->GetCollect(_T("username"));//����Ϊ���ݿ������
			vPassword = pRes->GetCollect(_T("password"));

			//���õ���ֵ��༭���е�ֵ���бȽϣ������漰�����ַ����������
			if (!::wcscmp(strUserName.GetString(), (LPCWSTR)(_bstr_t)vUserName) && !::wcscmp(strPassWord.GetString(), (LPCWSTR)(_bstr_t)vPassword.bstrVal))
			{
				pRes->Close();//�����ƥ�䣬�ر������¼ָ�룬��Ҫ�ֶ���ȥ�ͷ�
				db.closeDB(); //�ر����ݿ�����
				//MessageBox(_T("��¼�ɹ�"));
				
				CUserInfo dlg;
				ShowWindow(SW_HIDE);
				dlg.DoModal();
				ShowWindow(SW_SHOW);
				return;
			}
			else
			{
				pRes->MoveNext();//���û�в�ѯ�������ƶ������¼ָ�뵽��һ��
			}

		}
		//���ֹرգ�����������
		pRes->Close();
		db.closeDB();
		MessageBox(_T("��¼ʧ��"));
		return;
	}
	catch (_com_error e)
	{
		//���߽���Ĳ�����־д���ļ� CFile��
		db.closeDB();
		MessageBox(_T("��¼ʧ��"));
	}
}


void CELMSServerDlg::OnBnClickedBtnChange()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CChangePassword dlg;
	ShowWindow(SW_HIDE);
	dlg.DoModal();
	ShowWindow(SW_SHOW);
}


void CELMSServerDlg::OnAccept(CString szIP, UINT nPort)
{
	CString str;
	str.Format(_T("%s-%d:\r\n"), szIP, nPort);
	m_UserPort = nPort;
	m_IP = szIP;
	/*int nLen = m_txt.GetWindowTextLength();
	m_txt.SetSel(nLen, -1);
	m_txt.ReplaceSel(str);*/
}



