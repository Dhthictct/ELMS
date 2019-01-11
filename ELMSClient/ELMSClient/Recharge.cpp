// Recharge.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ELMSClient.h"
#include "Recharge.h"
#include "afxdialogex.h"
#include <atlconv.h> //�ַ���ת������������ͷ�ļ�
#include "UserView.h"
#include "ELMSClientDlg.h"
// CRecharge �Ի���

IMPLEMENT_DYNAMIC(CRecharge, CDialogEx)

CRecharge::CRecharge(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_RECHARGE, pParent)
	, m_Edt_Recharge(0)
{

}

CRecharge::~CRecharge()
{
}

void CRecharge::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Edt_Recharge);
}


BEGIN_MESSAGE_MAP(CRecharge, CDialogEx)
	ON_BN_CLICKED(IDOK, &CRecharge::OnBnClickedOk)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CRecharge ��Ϣ�������


void CRecharge::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	if (m_Edt_Recharge < 0)
	{
		MessageBox(_T("��ֵ����Ϊ��������������"));
	}

	//�����ַ���
	CString m_Context;
	m_Context.Format(_T("�ɹ���ֵ%dԪ"), m_Edt_Recharge);
	CString str;
	str.Format(_T("%d"), m_Edt_Recharge);
	
	//�ַ�ת��
	USES_CONVERSION;
	CUser userInfo;
	userInfo.setUserName(T2A(stUsername));
	userInfo.setPassWord(T2A(stPassword));
	CString strRemain;
	strRemain.Format(_T("%d"),m_Edt_Recharge);
	userInfo.setRemain(T2A(strRemain));

	//�õ������ڵĴ��ھ��
	//��Ϊ�����Ǵ�����ģ̬�Ի������Կ���ʹ���������
	//��ȻҲ����ʹ����Ƶ�е�AfxGetMainWnd()����������Ҫע����һ����������
	CELMSClientDlg* mainDlg = (CELMSClientDlg*)(AfxGetMainWnd());//��ȡ�����ڵĴ��ھ��			

	//����Э��
	int MSGTYPE = MYMSG_RECHARGE;

	//�������ݣ��ȷ���Э�飬�ڽ��û�������Ϣ���͹�ȥ
	mainDlg->m_SockClient.Send(&MSGTYPE, sizeof(MSGTYPE));
	mainDlg->m_SockClient.Send(&userInfo, sizeof(CUser));
	
	//������������������շ������˴�����������
	bool bRes = false;
	int sum;

	//�������ݣ��õ������ڣ��Ի��򣬿ؼ���Ҳ�Ǵ��ڣ��е��׽���
	mainDlg->m_SockClient.Receive(&bRes, sizeof(bRes));
	mainDlg->m_SockClient.Receive(&sum, sizeof(sum));

	//�������
	CUserView dlg;
	//dlg.m_Edt_Remain = sum ;

	if (bRes)
	{
		dlg.sUsername = stUsername;
		dlg.sPassword = stPassword;
		dlg.m_Edt_Remain = sum;
		MessageBox(m_Context);
		UpdateData(FALSE);
		OnOK();
		dlg.DoModal();
	}
	else
	{
		MessageBox(_T("��ֵʧ��"));
	}
	//CDialogEx::OnOK();
}


void CRecharge::OnPaint()
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
