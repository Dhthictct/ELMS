#pragma once
#include"SocketClient.h"

// CUserView 对话框

class CUserView : public CDialogEx
{
	DECLARE_DYNAMIC(CUserView)

public:
	CUserView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserView();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USERVIEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	UINT m_Edt_Hour;
	int m_Edt_Minute;
	int m_Edt_Second;
	// 余额
	double m_Edt_Remain;
	//当前用户名
	CString sUsername;
	//当前密码
	CString sPassword;
	CSocketClient m_SockClient;
	int temp;//临时余额
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnRecharge();
	afx_msg void OnBnClickedBtnRemain();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
	afx_msg void OnClose();
	afx_msg void OnBnClickedBtnEnd();
	void GameOver();
};
