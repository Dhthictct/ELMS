#pragma once

#include "SocketClient.h"
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
	int m_Edt_Recharge;
	CString stUsername;
	CString stPassword;
	afx_msg void OnBnClickedOk();
	afx_msg void OnPaint();
	CSocketClient m_SockClient;
};
