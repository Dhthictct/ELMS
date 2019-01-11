#pragma once

#include "afxwin.h"

// CRegister �Ի���

class CRegister : public CDialogEx
{
	DECLARE_DYNAMIC(CRegister)

public:
	CRegister(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRegister();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REGISTER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ע��ʱ���û��������16���ַ�
	CString m_Edt_Reg_UserName;
	// ע��ʱ�����룬���16���ַ�
	CString m_Edt_Reg_PassWord;
	// // ע��ʱ�ĵڶ������룬���16���ַ�
	CString m_Edt_Reg_OncePassWord;
	afx_msg void OnBnClickedBtnRegister();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	// ��Ա����
	CComboBox m_cbtable;
};
