
// ELMSServerDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "SocketListen.h"

// CELMSServerDlg 对话框
class CELMSServerDlg : public CDialogEx ,public CSocket
{
// 构造
public:
	CELMSServerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ELMSSERVER_DIALOG };
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
	CEdit m_Edt_Log;
	// 监听套接字
	CSocketListen m_SockListen;
	afx_msg void OnBnClickedBtnLogin();
	CString m_Edt_Username;
	CString m_Edt_Password;
	afx_msg void OnBnClickedBtnChange();
	void OnAccept(CString szIP, UINT nPort);
	UINT m_UserPort;
	CString m_Username;
	CString m_IP;
	CString m_Remain;
	//void OnReceive(CUser User);
};
