
// ELMSClientDlg.h : ͷ�ļ�
//

#pragma once

#include "Register.h"
#include "User.h"
#include "SocketClient.h"

// CELMSClientDlg �Ի���
class CELMSClientDlg : public CDialogEx
{
// ����
public:
	CELMSClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ELMSCLIENT_DIALOG };
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
	// ��¼������û��������16���ַ�
	CString m_Edt_Login_UserName;
	// ��¼��������룬���20���ַ�
	CString m_Edt_Login_PassWord;
	// �ͻ����׽���
	CSocketClient m_SockClient;
	afx_msg void OnBnClickedBtnRegister();
	afx_msg void OnBnClickedBtnLogin();
	afx_msg void OnBnClickedCancel();
	//�û�����ʱ����
	CString strUsername;
	CString strPassword;
	afx_msg void OnBnClickedBtnAboutus();
};
