#pragma once
#include "afxcmn.h"


// CUserInfo �Ի���

class CUserInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CUserInfo)

public:
	CUserInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUserInfo();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USERINFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListControl_UserInfo;
	virtual BOOL OnInitDialog();
	void OnAccept(CString szIP, UINT nPort);
	int m_Pos;//λ��
	CString m_Username;//�û�
	UINT m_Userport;//�û��˿�
	CString m_IP;//IP
	CString m_Remain;
	virtual void OnReceive(int nErrorCode);
	afx_msg void OnBnClickedBtnSee();
	int j;
	afx_msg void OnBnClickedBtnEnd();
	afx_msg void OnLvnItemchangedListUserinfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnRecharge();
};
