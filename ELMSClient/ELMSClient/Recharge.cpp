// Recharge.cpp : 实现文件
//

#include "stdafx.h"
#include "ELMSClient.h"
#include "Recharge.h"
#include "afxdialogex.h"
#include <atlconv.h> //字符串转换宏所包含的头文件
#include "UserView.h"
#include "ELMSClientDlg.h"
// CRecharge 对话框

IMPLEMENT_DYNAMIC(CRecharge, CDialogEx)

CRecharge::CRecharge(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_RECHARGE, pParent)
	, m_Edt_Recharge(0)
{

}

CRecharge::~CRecharge()
{
}

void CRecharge::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Edt_Recharge);
}


BEGIN_MESSAGE_MAP(CRecharge, CDialogEx)
	ON_BN_CLICKED(IDOK, &CRecharge::OnBnClickedOk)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CRecharge 消息处理程序


void CRecharge::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if (m_Edt_Recharge < 0)
	{
		MessageBox(_T("充值金额不能为负，请重新输入"));
	}

	//构建字符串
	CString m_Context;
	m_Context.Format(_T("成功充值%d元"), m_Edt_Recharge);
	CString str;
	str.Format(_T("%d"), m_Edt_Recharge);
	
	//字符转换
	USES_CONVERSION;
	CUser userInfo;
	userInfo.setUserName(T2A(stUsername));
	userInfo.setPassWord(T2A(stPassword));
	CString strRemain;
	strRemain.Format(_T("%d"),m_Edt_Recharge);
	userInfo.setRemain(T2A(strRemain));

	//得到主窗口的窗口句柄
	//因为这里是创建的模态对话框，所以可以使用这个函数
	//当然也可以使用视频中的AfxGetMainWnd()函数，但是要注意哪一个是主窗口
	CELMSClientDlg* mainDlg = (CELMSClientDlg*)(AfxGetMainWnd());//获取主窗口的窗口句柄			

	//构建协议
	int MSGTYPE = MYMSG_RECHARGE;

	//发送内容，先发送协议，在将用户对象信息发送过去
	mainDlg->m_SockClient.Send(&MSGTYPE, sizeof(MSGTYPE));
	mainDlg->m_SockClient.Send(&userInfo, sizeof(CUser));
	
	//定义这变量，用来接收服务器端传过来的内容
	bool bRes = false;
	int sum;

	//接收内容，得到主窗口（对话框，控件等也是窗口）中的套接字
	mainDlg->m_SockClient.Receive(&bRes, sizeof(bRes));
	mainDlg->m_SockClient.Receive(&sum, sizeof(sum));

	//更新余额
	CUserView dlg;
	//dlg.m_Edt_Remain = sum ;

	if (bRes)
	{
		dlg.sUsername = stUsername;
		dlg.sPassword = stPassword;
		dlg.m_Edt_Remain = sum;
		MessageBox(m_Context);
		UpdateData(FALSE);
		OnOK();
		dlg.DoModal();
	}
	else
	{
		MessageBox(_T("充值失败"));
	}
	//CDialogEx::OnOK();
}


void CRecharge::OnPaint()
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
