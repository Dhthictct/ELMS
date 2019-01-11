
// ELMSServerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "SocketListen.h"

// CELMSServerDlg �Ի���
class CELMSServerDlg : public CDialogEx ,public CSocket
{
// ����
public:
	CELMSServerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ELMSSERVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_Edt_Log;
	// �����׽���
	CSocketListen m_SockListen;
	afx_msg void OnBnClickedBtnLogin();
	CString m_Edt_Username;
	CString m_Edt_Password;
	afx_msg void OnBnClickedBtnChange();
	void OnAccept(CString szIP, UINT nPort);
	UINT m_UserPort;
	CString m_Username;
	CString m_IP;
	CString m_Remain;
	//void OnReceive(CUser User);
};
