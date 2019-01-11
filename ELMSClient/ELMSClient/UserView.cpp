// UserView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ELMSClient.h"
#include "UserView.h"
#include "afxdialogex.h"
#include "ELMSClientDlg.h"
#include "Recharge.h"

// CUserView �Ի���

IMPLEMENT_DYNAMIC(CUserView, CDialogEx)

CUserView::CUserView(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_USERVIEW, pParent)
	, m_Edt_Hour(0)
	, m_Edt_Minute(0)
	, m_Edt_Second(0)
	, m_Edt_Remain(0)
{

}

CUserView::~CUserView()
{
}

void CUserView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDT_HOUR, m_Edt_Hour);
	DDX_Text(pDX, IDC_EDT_MINUTE, m_Edt_Minute);
	DDV_MinMaxInt(pDX, m_Edt_Minute, 0, 59);
	DDX_Text(pDX, IDC_EDT_SECOND, m_Edt_Second);
	DDV_MinMaxInt(pDX, m_Edt_Second, 0, 59);
	DDX_Text(pDX, IDC_EDT_REMAIN, m_Edt_Remain);
}


BEGIN_MESSAGE_MAP(CUserView, CDialogEx)
	ON_BN_CLICKED(IDOK, &CUserView::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_RECHARGE, &CUserView::OnBnClickedBtnRecharge)
	ON_BN_CLICKED(IDC_BTN_REMAIN, &CUserView::OnBnClickedBtnRemain)
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_END, &CUserView::OnBnClickedBtnEnd)
END_MESSAGE_MAP()


// CUserView ��Ϣ�������


void CUserView::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	USES_CONVERSION;
	CUser userInfo;
	userInfo.setUserName(T2A(sUsername));
	userInfo.setPassWord(T2A(sPassword));
	CString strRemain;
	strRemain = "0";
	userInfo.setRemain(T2A(strRemain));
	CELMSClientDlg* mainDlg = (CELMSClientDlg*)(AfxGetMainWnd());//��ȡ�����ڵĴ��ھ��					 //CUserView* mainDlg = (CUserView*)(this->GetParent());//��ȡ�����ڵĴ��ھ��													   //����Э��
	int MSGTYPE = MYMSG_SELECTION;
	//�������ݣ��ȷ���Э�飬�ڽ��û�������Ϣ���͹�ȥ
	mainDlg->m_SockClient.Send(&MSGTYPE, sizeof(MSGTYPE));
	mainDlg->m_SockClient.Send(&userInfo, sizeof(CUser));

	//������һ���������������շ������˴�����������
	//�������ݣ��õ������ڣ��Ի��򣬿ؼ���Ҳ�Ǵ��ڣ��е��׽���
	bool bRes = false;
	int sum;
	mainDlg->m_SockClient.Receive(&bRes, sizeof(bRes));
	mainDlg->m_SockClient.Receive(&sum, sizeof(sum));
	m_Edt_Remain = sum;
	temp = sum;
	m_Edt_Hour = m_Edt_Remain / 5;
	if (!m_Edt_Hour && !m_Edt_Minute && !m_Edt_Second)
	{
		SetWindowText(_T("�������Ϊ�㣬���ֵ��"));
	}
	else
	{
		SetWindowText(_T("������"));
		SetTimer(IDC_EDT_SECOND, 1000, NULL);
		UpdateData(FALSE);
		
	}
	
	//CDialogEx::OnOK();
}





void CUserView::OnBnClickedBtnRecharge()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CRecharge dlg;
	//dlg.m_Edt_Recharge = 2;

	dlg.stUsername = sUsername;
	dlg.stPassword = sPassword;
	ShowWindow(SW_HIDE);
	if (IDOK == dlg.DoModal())
	{
		m_Edt_Hour += dlg.m_Edt_Recharge;
	}
	//ShowWindow(SW_SHOW);//��ʾ���Ի���
	UpdateData(FALSE);
}


void CUserView::OnBnClickedBtnRemain()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_Edt_Remain = (double)(m_Edt_Hour * 5 + temp % 5);
	UpdateData(FALSE);
}


void CUserView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nIDEvent)
	{
	case IDC_EDT_SECOND:
	{
		CELMSClientDlg* mainDlg = (CELMSClientDlg*)(AfxGetMainWnd());//��ȡ�����ڵĴ��ھ��

		//CELMSClientDlg* mainDlg = (CELMSClientDlg*)(AfxGetMainWnd());//��ȡ�����ڵĴ��ھ��
		//Ȼ����Э�������

		UpdateData(TRUE);
		USES_CONVERSION;

		CUser userInfo;
		userInfo.setUserName(T2A(sUsername));
		userInfo.setPassWord(T2A(sPassword));
		int MSGTYPE = MYMSG_SEE;
		mainDlg->m_SockClient.Send(&MSGTYPE, sizeof(MSGTYPE));
		mainDlg->m_SockClient.Send(&userInfo, sizeof(userInfo));
		if (--m_Edt_Second < 0)
		{
			m_Edt_Second = 59;
			if (--m_Edt_Minute < 0)
			{
				m_Edt_Minute = 59;
				--m_Edt_Hour;
				if (!m_Edt_Hour)
				{
					MessageBox(_T("����ʣ��ʱ�伴�����㣬��������Ķ��뾡���ֵ"));
				}
				else if (!m_Edt_Hour && !m_Edt_Minute && !m_Edt_Second)
				{
					UpdateData(TRUE);
					USES_CONVERSION;

					CUser userInfo;
					userInfo.setUserName(T2A(sUsername));
					userInfo.setPassWord(T2A(sPassword));

					struct node
					{
						int hour, minute, second;
					}time;
					time.hour = m_Edt_Hour;
					time.minute = m_Edt_Minute;
					time.second = m_Edt_Second;
					//�ȷ���Э��,�ٷ�������
					CELMSClientDlg* mainDlg = (CELMSClientDlg*)(AfxGetMainWnd());//��ȡ�����ڵĴ��ھ��
					int MSGTYPE = MYMSG_END;
					mainDlg->m_SockClient.Send(&MSGTYPE, sizeof(MSGTYPE));
					bool bSrvRes = false;
					bool tm = false;
					//Ȼ����Э�������
					mainDlg->m_SockClient.Send(&userInfo, sizeof(CUser));

					mainDlg->m_SockClient.Send(&time, sizeof(time));
					//���շ������˷��͹����Ľ�����Խ�����д���
					mainDlg->m_SockClient.Receive(&bSrvRes, sizeof(bSrvRes));
					mainDlg->m_SockClient.Receive(&tm, sizeof(tm));
					if (!bSrvRes)
					{
						//MessageBox(_T("��¼�ɹ���"),_T("��¼��ʾ"));

						//��ʾ�û���ͼ��������
						MessageBox(_T("�����쳣"));
						CUserView::OnOK();
						//MessageBox(_T("����ʱ�䵽"));
						//EndDialog(IDD_USERVIEW);
					}
					if (tm)
					{
						MessageBox(_T("ǿ���»�"));
						//EndDialog(IDD_USERVIEW);
					}
					//MessageBox(_T("����ʱ�䵽"));
					OnOK();
				}

			}
		}
		UpdateData(FALSE);
		//CELMSClientDlg* mainDlg = (CELMSClientDlg*)(AfxGetMainWnd());//��ȡ�����ڵĴ��ھ��
		bool end = false;
		//mainDlg->m_SockClient.Receive(&end, sizeof(end));
		if (end)
		{
			OnCancel();
		}
	}
	default:
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CUserView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CImage img1;
	img1.Load(_T("theme\\1.jpg"));
	CRect clientRect;//�����С��
	GetClientRect(&clientRect);//��ȡ�ͻ����Ĵ�С
	img1.Draw(dc, 0, 0, clientRect.Width(), clientRect.Height());
}


void CUserView::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	KillTimer(IDC_EDT_SECOND);
	CDialogEx::OnClose();
}




void CUserView::OnBnClickedBtnEnd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	USES_CONVERSION;
	CUser userInfo;
	userInfo.setUserName(T2A(sUsername));
	userInfo.setPassWord(T2A(sPassword));
	CString strRemain;
	strRemain = "0";
	if (!m_Edt_Hour && !m_Edt_Minute && !m_Edt_Second)
	{
		CDialogEx::OnCancel();
	}
	else
	{
		userInfo.setRemain(T2A(strRemain));
		CELMSClientDlg* mainDlg = (CELMSClientDlg*)(AfxGetMainWnd());//��ȡ�����ڵĴ��ھ��					 //CUserView* mainDlg = (CUserView*)(this->GetParent());//��ȡ�����ڵĴ��ھ��													   //����Э��
		int MSGTYPE = MYMSG_SAVE;
		//�������ݣ��ȷ���Э�飬�ڽ��û�������Ϣ���͹�ȥ
		mainDlg->m_SockClient.Send(&MSGTYPE, sizeof(MSGTYPE));
		mainDlg->m_SockClient.Send(&userInfo, sizeof(CUser));
		int sum = temp % 5 + m_Edt_Hour * 5;
		mainDlg->m_SockClient.Send(&sum, sizeof(sum));
		//������һ���������������շ������˴�����������
		//�������ݣ��õ������ڣ��Ի��򣬿ؼ���Ҳ�Ǵ��ڣ��е��׽���
		bool bRes = false;
		mainDlg->m_SockClient.Receive(&bRes, sizeof(bRes));
		//mainDlg->m_SockClient.Receive(&sum, sizeof(sum));
		if (bRes)
		{
			CDialogEx::OnOK();
		}
		else
		{
			MessageBox(_T("�»�ʧ��"));
		}
	}
}


void CUserView::GameOver()
{
	CDialogEx::OnCancel();
}
