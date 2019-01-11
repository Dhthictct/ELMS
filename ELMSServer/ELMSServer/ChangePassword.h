#pragma once


// CChangePassword 对话框

class CChangePassword : public CDialogEx
{
	DECLARE_DYNAMIC(CChangePassword)

public:
	CChangePassword(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CChangePassword();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_CHANGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 管理员账户
	CString m_Edt_Username;
	// 管理员密码
	CString m_Edt_Password;
	// 新密码
	CString m_Edt_NewPwd;
	// 验证密码
	CString m_Edt_NewOncePwd;
	afx_msg void OnBnClickedBtnChange();
};
