#pragma once


// CRecharge �Ի���

class CRecharge : public CDialogEx
{
	DECLARE_DYNAMIC(CRecharge)

public:
	CRecharge(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRecharge();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RECHARGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_Username;
	int m_Money;
};
