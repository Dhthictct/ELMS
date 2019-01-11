// UserView.cpp : 实现文件
//

#include "stdafx.h"
#include "ELMSClient.h"
#include "UserView.h"
#include "afxdialogex.h"
#include "ELMSClientDlg.h"
#include "Recharge.h"

// CUserView 对话框

IMPLEMENT_DYNAMIC(CUserView, CDialogEx)

CUserView::CUserView(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_USERVIEW, pParent)
	, m_Edt_Hour(0)
	, m_Edt_Minute(0)
	, m_Edt_Second(0)
	, m_Edt_Remain(0)
{

}

CUserView::~CUserView()
{
}

void CUserView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDT_HOUR, m_Edt_Hour);
	DDX_Text(pDX, IDC_EDT_MINUTE, m_Edt_Minute);
	DDV_MinMaxInt(pDX, m_Edt_Minute, 0, 59);
	DDX_Text(pDX, IDC_EDT_SECOND, m_Edt_Second);
	DDV_MinMaxInt(pDX, m_Edt_Second, 0, 59);
	DDX_Text(pDX, IDC_EDT_REMAIN, m_Edt_Remain);
}


BEGIN_MESSAGE_MAP(CUserView, CDialogEx)
	ON_BN_CLICKED(IDOK, &CUserView::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_RECHARGE, &CUserView::OnBnClickedBtnRecharge)
	ON_BN_CLICKED(IDC_BTN_REMAIN, &CUserView::OnBnClickedBtnRemain)
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_END, &CUserView::OnBnClickedBtnEnd)
END_MESSAGE_MAP()


// CUserView 消息处理程序


void CUserView::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	USES_CONVERSION;
	CUser userInfo;
	userInfo.setUserName(T2A(sUsername));
	userInfo.setPassWord(T2A(sPassword));
	CString strRemain;
	strRemain = "0";
	userInfo.setRemain(T2A(strRemain));
	CELMSClientDlg* mainDlg = (CELMSClientDlg*)(AfxGetMainWnd());//获取父窗口的窗口句柄					 //CUserView* mainDlg = (CUserView*)(this->GetParent());//获取父窗口的窗口句柄													   //构建协议
	int MSGTYPE = MYMSG_SELECTION;
	//发送内容，先发送协议，在将用户对象信息发送过去
	mainDlg->m_SockClient.Send(&MSGTYPE, sizeof(MSGTYPE));
	mainDlg->m_SockClient.Send(&userInfo, sizeof(CUser));

	//定义这一个变量，用来接收服务器端传过来的内容
	//接收内容，得到主窗口（对话框，控件等也是窗口）中的套接字
	bool bRes = false;
	int sum;
	mainDlg->m_SockClient.Receive(&bRes, sizeof(bRes));
	mainDlg->m_SockClient.Receive(&sum, sizeof(sum));
	m_Edt_Remain = sum;
	temp = sum;
	m_Edt_Hour = m_Edt_Remain / 5;
	if (!m_Edt_Hour && !m_Edt_Minute && !m_Edt_Second)
	{
		SetWindowText(_T("您的余额为零，请充值！"));
	}
	else
	{
		SetWindowText(_T("读书中"));
		SetTimer(IDC_EDT_SECOND, 1000, NULL);
		UpdateData(FALSE);
		
	}
	
	//CDialogEx::OnOK();
}





void CUserView::OnBnClickedBtnRecharge()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CRecharge dlg;
	//dlg.m_Edt_Recharge = 2;

	dlg.stUsername = sUsername;
	dlg.stPassword = sPassword;
	ShowWindow(SW_HIDE);
	if (IDOK == dlg.DoModal())
	{
		m_Edt_Hour += dlg.m_Edt_Recharge;
	}
	//ShowWindow(SW_SHOW);//显示主对话框
	UpdateData(FALSE);
}


void CUserView::OnBnClickedBtnRemain()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Edt_Remain = (double)(m_Edt_Hour * 5 + temp % 5);
	UpdateData(FALSE);
}


void CUserView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	case IDC_EDT_SECOND:
	{
		CELMSClientDlg* mainDlg = (CELMSClientDlg*)(AfxGetMainWnd());//获取父窗口的窗口句柄

		//CELMSClientDlg* mainDlg = (CELMSClientDlg*)(AfxGetMainWnd());//获取父窗口的窗口句柄
		//然后发送协议的内容

		UpdateData(TRUE);
		USES_CONVERSION;

		CUser userInfo;
		userInfo.setUserName(T2A(sUsername));
		userInfo.setPassWord(T2A(sPassword));
		int MSGTYPE = MYMSG_SEE;
		mainDlg->m_SockClient.Send(&MSGTYPE, sizeof(MSGTYPE));
		mainDlg->m_SockClient.Send(&userInfo, sizeof(userInfo));
		if (--m_Edt_Second < 0)
		{
			m_Edt_Second = 59;
			if (--m_Edt_Minute < 0)
			{
				m_Edt_Minute = 59;
				--m_Edt_Hour;
				if (!m_Edt_Hour)
				{
					MessageBox(_T("您的剩余时间即将不足，如需继续阅读请尽快充值"));
				}
				else if (!m_Edt_Hour && !m_Edt_Minute && !m_Edt_Second)
				{
					UpdateData(TRUE);
					USES_CONVERSION;

					CUser userInfo;
					userInfo.setUserName(T2A(sUsername));
					userInfo.setPassWord(T2A(sPassword));

					struct node
					{
						int hour, minute, second;
					}time;
					time.hour = m_Edt_Hour;
					time.minute = m_Edt_Minute;
					time.second = m_Edt_Second;
					//先发送协议,再发送内容
					CELMSClientDlg* mainDlg = (CELMSClientDlg*)(AfxGetMainWnd());//获取父窗口的窗口句柄
					int MSGTYPE = MYMSG_END;
					mainDlg->m_SockClient.Send(&MSGTYPE, sizeof(MSGTYPE));
					bool bSrvRes = false;
					bool tm = false;
					//然后发送协议的内容
					mainDlg->m_SockClient.Send(&userInfo, sizeof(CUser));

					mainDlg->m_SockClient.Send(&time, sizeof(time));
					//接收服务器端发送过来的结果并对结果进行处理
					mainDlg->m_SockClient.Receive(&bSrvRes, sizeof(bSrvRes));
					mainDlg->m_SockClient.Receive(&tm, sizeof(tm));
					if (!bSrvRes)
					{
						//MessageBox(_T("登录成功！"),_T("登录提示"));

						//显示用户的图书管理界面
						MessageBox(_T("出现异常"));
						CUserView::OnOK();
						//MessageBox(_T("阅览时间到"));
						//EndDialog(IDD_USERVIEW);
					}
					if (tm)
					{
						MessageBox(_T("强制下机"));
						//EndDialog(IDD_USERVIEW);
					}
					//MessageBox(_T("阅览时间到"));
					OnOK();
				}

			}
		}
		UpdateData(FALSE);
		//CELMSClientDlg* mainDlg = (CELMSClientDlg*)(AfxGetMainWnd());//获取父窗口的窗口句柄
		bool end = false;
		//mainDlg->m_SockClient.Receive(&end, sizeof(end));
		if (end)
		{
			OnCancel();
		}
	}
	default:
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CUserView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	CImage img1;
	img1.Load(_T("theme\\1.jpg"));
	CRect clientRect;//区域大小类
	GetClientRect(&clientRect);//获取客户区的大小
	img1.Draw(dc, 0, 0, clientRect.Width(), clientRect.Height());
}


void CUserView::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	KillTimer(IDC_EDT_SECOND);
	CDialogEx::OnClose();
}




void CUserView::OnBnClickedBtnEnd()
{
	// TODO: 在此添加控件通知处理程序代码
	USES_CONVERSION;
	CUser userInfo;
	userInfo.setUserName(T2A(sUsername));
	userInfo.setPassWord(T2A(sPassword));
	CString strRemain;
	strRemain = "0";
	if (!m_Edt_Hour && !m_Edt_Minute && !m_Edt_Second)
	{
		CDialogEx::OnCancel();
	}
	else
	{
		userInfo.setRemain(T2A(strRemain));
		CELMSClientDlg* mainDlg = (CELMSClientDlg*)(AfxGetMainWnd());//获取父窗口的窗口句柄					 //CUserView* mainDlg = (CUserView*)(this->GetParent());//获取父窗口的窗口句柄													   //构建协议
		int MSGTYPE = MYMSG_SAVE;
		//发送内容，先发送协议，在将用户对象信息发送过去
		mainDlg->m_SockClient.Send(&MSGTYPE, sizeof(MSGTYPE));
		mainDlg->m_SockClient.Send(&userInfo, sizeof(CUser));
		int sum = temp % 5 + m_Edt_Hour * 5;
		mainDlg->m_SockClient.Send(&sum, sizeof(sum));
		//定义这一个变量，用来接收服务器端传过来的内容
		//接收内容，得到主窗口（对话框，控件等也是窗口）中的套接字
		bool bRes = false;
		mainDlg->m_SockClient.Receive(&bRes, sizeof(bRes));
		//mainDlg->m_SockClient.Receive(&sum, sizeof(sum));
		if (bRes)
		{
			CDialogEx::OnOK();
		}
		else
		{
			MessageBox(_T("下机失败"));
		}
	}
}


void CUserView::GameOver()
{
	CDialogEx::OnCancel();
}
