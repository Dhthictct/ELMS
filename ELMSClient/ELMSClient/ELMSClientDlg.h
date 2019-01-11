
// ELMSClientDlg.h : 头文件
//

#pragma once

#include "Register.h"
#include "User.h"
#include "SocketClient.h"

// CELMSClientDlg 对话框
class CELMSClientDlg : public CDialogEx
{
// 构造
public:
	CELMSClientDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ELMSCLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// 登录界面的用户名，最多16个字符
	CString m_Edt_Login_UserName;
	// 登录界面的密码，最多20个字符
	CString m_Edt_Login_PassWord;
	// 客户端套接字
	CSocketClient m_SockClient;
	afx_msg void OnBnClickedBtnRegister();
	afx_msg void OnBnClickedBtnLogin();
	afx_msg void OnBnClickedCancel();
	//用户名临时变量
	CString strUsername;
	CString strPassword;
	afx_msg void OnBnClickedBtnAboutus();
};
