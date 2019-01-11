
// ELMSServerDlg.cpp : 实现文件
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


// CELMSServerDlg 对话框



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


// CELMSServerDlg 消息处理程序

BOOL CELMSServerDlg::OnInitDialog()
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
	//监听套接字，创建端口，开始监听
	BOOL bResult = m_SockListen.Create(9413);
	UINT unError = GetLastError();
	//常见的创建失败，有两种，一种是未初始化socket，一种是端口被占用
	if (unError == WSANOTINITIALISED) //WSANOTINITIALISED为10093
	{
		AfxMessageBox(_T("未初始化套接字相关或初始化失败！")); //就是未调用AfxSocketInit函数或函数失败
	}
	if (unError == WSAEADDRINUSE)
	{
		AfxMessageBox(_T("端口被占用！"));
	}
	//开始监听
	//Listen函数，有一个参数，默认值为5.这个参数表示，有最大允许多少人在连接的状态中
	m_SockListen.Listen();
	

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CELMSServerDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CELMSServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CELMSServerDlg::OnBnClickedBtnLogin()
{
	// TODO: 在此添加控件通知处理程序代码
	USES_CONVERSION; //用来进行字符串转换
	CUserDataBase db;
	db.initDB(); //初始化数据库
	CELMSServerDlg* SrvDlg = (CELMSServerDlg*)AfxGetMainWnd();

	UpdateData(TRUE);
	//字符串的转换
	CString strUserName = m_Edt_Username;
	CString strPassWord = m_Edt_Password;

	//构建sql语句
	_bstr_t bstrSQL = _T("select * from Administrator");
	_variant_t vUserName, vPassword;

	//调用GetRecordSet函数，得到记录集
	_RecordsetPtr & pRes = db.GetRecordSet(bstrSQL);

	try
	{
		//判断记录集如果为空，发送false内容，并返回
		if (pRes == NULL)
		{
			db.closeDB();
			return;
		}
		//否则，使用adoEOF对记录集进行遍历
		while (!pRes->adoEOF)
		{
			vUserName = pRes->GetCollect(_T("username"));//参数为数据库的列名
			vPassword = pRes->GetCollect(_T("password"));

			//将得到的值与编辑框中的值进行比较，这里涉及到了字符编码的问题
			if (!::wcscmp(strUserName.GetString(), (LPCWSTR)(_bstr_t)vUserName) && !::wcscmp(strPassWord.GetString(), (LPCWSTR)(_bstr_t)vPassword.bstrVal))
			{
				pRes->Close();//如果相匹配，关闭这个记录指针，需要手动的去释放
				db.closeDB(); //关闭数据库连接
				//MessageBox(_T("登录成功"));
				
				CUserInfo dlg;
				ShowWindow(SW_HIDE);
				dlg.DoModal();
				ShowWindow(SW_SHOW);
				return;
			}
			else
			{
				pRes->MoveNext();//如果没有查询到，就移动这个记录指针到下一行
			}

		}
		//各种关闭，并发送内容
		pRes->Close();
		db.closeDB();
		MessageBox(_T("登录失败"));
		return;
	}
	catch (_com_error e)
	{
		//或者将其的操作日志写入文件 CFile类
		db.closeDB();
		MessageBox(_T("登录失败"));
	}
}


void CELMSServerDlg::OnBnClickedBtnChange()
{
	// TODO: 在此添加控件通知处理程序代码
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



