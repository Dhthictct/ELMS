#pragma once
#include"SocketClient.h"

// CUserView �Ի���

class CUserView : public CDialogEx
{
	DECLARE_DYNAMIC(CUserView)

public:
	CUserView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUserView();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USERVIEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	UINT m_Edt_Hour;
	int m_Edt_Minute;
	int m_Edt_Second;
	// ���
	double m_Edt_Remain;
	//��ǰ�û���
	CString sUsername;
	//��ǰ����
	CString sPassword;
	CSocketClient m_SockClient;
	int temp;//��ʱ���
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnRecharge();
	afx_msg void OnBnClickedBtnRemain();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
	afx_msg void OnClose();
	afx_msg void OnBnClickedBtnEnd();
	void GameOver();
};
