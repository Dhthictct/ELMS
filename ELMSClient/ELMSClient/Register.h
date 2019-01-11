#pragma once

#include "afxwin.h"

// CRegister 对话框

class CRegister : public CDialogEx
{
	DECLARE_DYNAMIC(CRegister)

public:
	CRegister(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRegister();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REGISTER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 注册时的用户名，最多16个字符
	CString m_Edt_Reg_UserName;
	// 注册时的密码，最多16个字符
	CString m_Edt_Reg_PassWord;
	// // 注册时的第二次密码，最多16个字符
	CString m_Edt_Reg_OncePassWord;
	afx_msg void OnBnClickedBtnRegister();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	// 会员类型
	CComboBox m_cbtable;
};
