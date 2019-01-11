#pragma once
#include "afxcmn.h"


// CUserInfo 对话框

class CUserInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CUserInfo)

public:
	CUserInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserInfo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USERINFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListControl_UserInfo;
	virtual BOOL OnInitDialog();
	void OnAccept(CString szIP, UINT nPort);
	int m_Pos;//位置
	CString m_Username;//用户
	UINT m_Userport;//用户端口
	CString m_IP;//IP
	CString m_Remain;
	virtual void OnReceive(int nErrorCode);
	afx_msg void OnBnClickedBtnSee();
	int j;
	afx_msg void OnBnClickedBtnEnd();
	afx_msg void OnLvnItemchangedListUserinfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnRecharge();
};
