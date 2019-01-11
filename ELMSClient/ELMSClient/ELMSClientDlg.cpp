
// ELMSClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ELMSClient.h"
#include "ELMSClientDlg.h"
#include "afxdialogex.h"

#include "UserView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CELMSClientDlg 对话框



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


// CELMSClientDlg 消息处理程序

BOOL CELMSClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	//客户端创建随机端口
	if (!m_SockClient.Create())
	{
		AfxMessageBox(_T("创建网络失败!"));
		return FALSE;
	}

	//开始连接
	if (!m_SockClient.Connect(_T("127.0.0.1"), 9413))
	{
		int nER = GetLastError();
		MessageBox(_T("连接服务器失败！"));
		return FALSE;
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CELMSClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//画背景图
		CPaintDC dc(this);
		CImage img1;
		img1.Load(_T("theme\\1.jpg"));
		CRect clientRect;//区域大小类
		GetClientRect(&clientRect);//获取客户区的大小
		img1.Draw(dc, 0, 0, clientRect.Width(), clientRect.Height());
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CELMSClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CELMSClientDlg::OnBnClickedBtnRegister()
{
	// TODO: 在此添加控件通知处理程序代码
	CRegister regDlg;
	//隐藏主对话框
	ShowWindow(SW_HIDE);
	INT_PTR nResult = regDlg.DoModal(); //可以获取DoModal函数的值
	//regDlg.DoModal();
	ShowWindow(SW_SHOW);//显示主对话框
}


void CELMSClientDlg::OnBnClickedBtnLogin()
{
	// TODO: 在此添加控件通知处理程序代码
	//得到控件值
	UpdateData(TRUE);
	//字符转换
	USES_CONVERSION;
	//判断
	if (m_Edt_Login_UserName.IsEmpty() || m_Edt_Login_PassWord.IsEmpty())
	{
		MessageBox(_T("用户名或密码为空，请重新输入"), _T("登录提示"), MB_OK | MB_ICONWARNING);
		m_Edt_Login_UserName = _T("");
		m_Edt_Login_PassWord = _T("");
		//显示控件值
		UpdateData(FALSE);
		return;
	}
	
	CUser userInfo;
	userInfo.setUserName(T2A(m_Edt_Login_UserName));
	userInfo.setPassWord(T2A(m_Edt_Login_PassWord));
	
	//m_SockClient.Send(&userInfo, sizeof(CUser));

	//先发送协议,再发送内容
	int MSGTYPE = MYMSG_LOGIN;
	m_SockClient.Send(&MSGTYPE, sizeof(MSGTYPE));

	//然后发送协议的内容
	int i = m_SockClient.Send(&userInfo, sizeof(CUser));
	bool bSrvRes = false;

	//接收服务器端发送过来的结果并对结果进行处理
	m_SockClient.Receive(&bSrvRes, sizeof(bSrvRes));
	if (bSrvRes)
	{
		//MessageBox(_T("登录成功！"),_T("登录提示"));
		//显示用户的图书管理界面

		int MSGTYPE = MYMSG_MESSAGE;
		m_SockClient.Send(&MSGTYPE, sizeof(MSGTYPE));

		//然后发送协议的内容
		int i = m_SockClient.Send(&userInfo, sizeof(CUser));

		CUserView dlg;
		ShowWindow(SW_HIDE);
		dlg.sUsername = m_Edt_Login_UserName;
		dlg.sPassword = m_Edt_Login_PassWord;
		dlg.DoModal();
		ShowWindow(SW_SHOW);//显示主对话框
	}
	else
	{
		if (IDOK == MessageBox(_T("登录失败！"), _T("登录提示"), MB_OKCANCEL | MB_ICONERROR))
		{
			m_Edt_Login_UserName = _T("");
			m_Edt_Login_PassWord = _T("");
			UpdateData(FALSE);
		}
	}
}

//取消，或退出程序的处理
void CELMSClientDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	if (IDOK == MessageBox(_T("真的要退出吗？"), _T("提示"), MB_OKCANCEL | MB_ICONQUESTION))
		CDialogEx::OnCancel();
}



void CELMSClientDlg::OnBnClickedBtnAboutus()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(_T("收费五元/时\r\n会员六折"));
}
