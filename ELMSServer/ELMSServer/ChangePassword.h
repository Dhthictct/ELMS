#pragma once


// CChangePassword �Ի���

class CChangePassword : public CDialogEx
{
	DECLARE_DYNAMIC(CChangePassword)

public:
	CChangePassword(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChangePassword();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_CHANGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ����Ա�˻�
	CString m_Edt_Username;
	// ����Ա����
	CString m_Edt_Password;
	// ������
	CString m_Edt_NewPwd;
	// ��֤����
	CString m_Edt_NewOncePwd;
	afx_msg void OnBnClickedBtnChange();
};
