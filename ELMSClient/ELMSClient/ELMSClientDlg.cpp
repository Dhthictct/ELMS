
// ELMSClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ELMSClient.h"
#include "ELMSClientDlg.h"
#include "afxdialogex.h"

#include "UserView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CELMSClientDlg �Ի���



CELMSClientDlg::CELMSClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ELMSCLIENT_DIALOG, pParent)
	, m_Edt_Login_UserName(_T(""))
	, m_Edt_Login_PassWord(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CELMSClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDT_LOGIN_USERNAME, m_Edt_Login_UserName);
	DDV_MaxChars(pDX, m_Edt_Login_UserName, 16);
	DDX_Text(pDX, IDC_EDT_LOGIN_PASSWORD, m_Edt_Login_PassWord);
	DDV_MaxChars(pDX, m_Edt_Login_PassWord, 16);
}

BEGIN_MESSAGE_MAP(CELMSClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_REGISTER, &CELMSClientDlg::OnBnClickedBtnRegister)
	ON_BN_CLICKED(IDC_BTN_LOGIN, &CELMSClientDlg::OnBnClickedBtnLogin)
	ON_BN_CLICKED(IDC_BTN_ABOUTUS, &CELMSClientDlg::OnBnClickedBtnAboutus)
END_MESSAGE_MAP()


// CELMSClientDlg ��Ϣ�������

BOOL CELMSClientDlg::OnInitDialog()
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

	//�ͻ��˴�������˿�
	if (!m_SockClient.Create())
	{
		AfxMessageBox(_T("��������ʧ��!"));
		return FALSE;
	}

	//��ʼ����
	if (!m_SockClient.Connect(_T("127.0.0.1"), 9413))
	{
		int nER = GetLastError();
		MessageBox(_T("���ӷ�����ʧ�ܣ�"));
		return FALSE;
	}

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CELMSClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	if (nID == SC_MOVE || nID == SC_MINIMIZE || nID == SC_MAXIMIZE )
		return;

	/*if (nID == SC_MOVE || nID == SC_MINIMIZE || nID == SC_MAXIMIZE)
	{
		return;
	}*/
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CELMSClientDlg::OnPaint()
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
		//������ͼ
		CPaintDC dc(this);
		CImage img1;
		img1.Load(_T("theme\\1.jpg"));
		CRect clientRect;//�����С��
		GetClientRect(&clientRect);//��ȡ�ͻ����Ĵ�С
		img1.Draw(dc, 0, 0, clientRect.Width(), clientRect.Height());
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CELMSClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CELMSClientDlg::OnBnClickedBtnRegister()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CRegister regDlg;
	//�������Ի���
	ShowWindow(SW_HIDE);
	INT_PTR nResult = regDlg.DoModal(); //���Ի�ȡDoModal������ֵ
	//regDlg.DoModal();
	ShowWindow(SW_SHOW);//��ʾ���Ի���
}


void CELMSClientDlg::OnBnClickedBtnLogin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�õ��ؼ�ֵ
	UpdateData(TRUE);
	//�ַ�ת��
	USES_CONVERSION;
	//�ж�
	if (m_Edt_Login_UserName.IsEmpty() || m_Edt_Login_PassWord.IsEmpty())
	{
		MessageBox(_T("�û���������Ϊ�գ�����������"), _T("��¼��ʾ"), MB_OK | MB_ICONWARNING);
		m_Edt_Login_UserName = _T("");
		m_Edt_Login_PassWord = _T("");
		//��ʾ�ؼ�ֵ
		UpdateData(FALSE);
		return;
	}
	
	CUser userInfo;
	userInfo.setUserName(T2A(m_Edt_Login_UserName));
	userInfo.setPassWord(T2A(m_Edt_Login_PassWord));
	
	//m_SockClient.Send(&userInfo, sizeof(CUser));

	//�ȷ���Э��,�ٷ�������
	int MSGTYPE = MYMSG_LOGIN;
	m_SockClient.Send(&MSGTYPE, sizeof(MSGTYPE));

	//Ȼ����Э�������
	int i = m_SockClient.Send(&userInfo, sizeof(CUser));
	bool bSrvRes = false;

	//���շ������˷��͹����Ľ�����Խ�����д���
	m_SockClient.Receive(&bSrvRes, sizeof(bSrvRes));
	if (bSrvRes)
	{
		//MessageBox(_T("��¼�ɹ���"),_T("��¼��ʾ"));
		//��ʾ�û���ͼ��������

		int MSGTYPE = MYMSG_MESSAGE;
		m_SockClient.Send(&MSGTYPE, sizeof(MSGTYPE));

		//Ȼ����Э�������
		int i = m_SockClient.Send(&userInfo, sizeof(CUser));

		CUserView dlg;
		ShowWindow(SW_HIDE);
		dlg.sUsername = m_Edt_Login_UserName;
		dlg.sPassword = m_Edt_Login_PassWord;
		dlg.DoModal();
		ShowWindow(SW_SHOW);//��ʾ���Ի���
	}
	else
	{
		if (IDOK == MessageBox(_T("��¼ʧ�ܣ�"), _T("��¼��ʾ"), MB_OKCANCEL | MB_ICONERROR))
		{
			m_Edt_Login_UserName = _T("");
			m_Edt_Login_PassWord = _T("");
			UpdateData(FALSE);
		}
	}
}

//ȡ�������˳�����Ĵ���
void CELMSClientDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (IDOK == MessageBox(_T("���Ҫ�˳���"), _T("��ʾ"), MB_OKCANCEL | MB_ICONQUESTION))
		CDialogEx::OnCancel();
}



void CELMSClientDlg::OnBnClickedBtnAboutus()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MessageBox(_T("�շ���Ԫ/ʱ\r\n��Ա����"));
}
