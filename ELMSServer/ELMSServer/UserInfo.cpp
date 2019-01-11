// UserInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ELMSServer.h"
#include "UserInfo.h"
#include "afxdialogex.h"
#include "ELMSServerDlg.h"
#include "SocketServer.h"
#include "Recharge.h"
// CUserInfo �Ի���

IMPLEMENT_DYNAMIC(CUserInfo, CDialogEx)

CUserInfo::CUserInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_USERINFO, pParent)
	, m_Username(_T(""))
	, m_Userport(0)
	, j(0)
{
	m_Username = _T("");
	m_Userport = 0;
}

CUserInfo::~CUserInfo()
{
}

void CUserInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_USERINFO, m_ListControl_UserInfo);
}


BEGIN_MESSAGE_MAP(CUserInfo, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_SEE, &CUserInfo::OnBnClickedBtnSee)
	ON_BN_CLICKED(IDC_BTN_END, &CUserInfo::OnBnClickedBtnEnd)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_USERINFO, &CUserInfo::OnLvnItemchangedListUserinfo)
	ON_BN_CLICKED(IDC_BTN_RECHARGE, &CUserInfo::OnBnClickedBtnRecharge)
END_MESSAGE_MAP()


// CUserInfo ��Ϣ�������


BOOL CUserInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//��ȡListControl��λ�úʹ�С
	//����rect������ÿһ����Ĵ�С
	CRect rect;
	m_ListControl_UserInfo.GetClientRect(&rect);
	m_ListControl_UserInfo.SetExtendedStyle(m_ListControl_UserInfo.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	
	m_ListControl_UserInfo.InsertColumn(0, _T("�û�"), LVCFMT_CENTER, rect.Width() / 5, 0);
	m_ListControl_UserInfo.InsertColumn(1, _T("λ��"), LVCFMT_CENTER, rect.Width() / 5, 0);
	m_ListControl_UserInfo.InsertColumn(2, _T("�˿�"), LVCFMT_CENTER, rect.Width() / 5, 0);
	m_ListControl_UserInfo.InsertColumn(3, _T("IP"),   LVCFMT_CENTER, rect.Width() / 5, 0);
	m_ListControl_UserInfo.InsertColumn(4, _T("���"), LVCFMT_CENTER, rect.Width() / 5, 0);


	/*CString str;
	str.Format(_T("%u"), m_Userport);
	m_ListControl_UserInfo.InsertItem(0, m_Username);
	m_ListControl_UserInfo.SetItemText(0, 1, str);*/

	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
void CUserInfo::OnReceive(int nErrorCode)
{
	//m_Username = User.getUserName();
	/*int MSGTYPE; //����һ���������յ�Э��
	this->Receive(&MSGTYPE, sizeof(MSGTYPE)); //��ʼ����
	switch (MSGTYPE) //����������Э�飬���ദ��
	{
	case MYMSG_SEE:
	{
		CELMSServerDlg* SrvDlg = (CELMSServerDlg*)AfxGetMainWnd();
		CUser userInfo;
		this->Receive(&userInfo, sizeof(userInfo));
		m_Username = userInfo.getUserName();
	}
	}*/
}

void CUserInfo::OnBnClickedBtnSee()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	/*CRect rect;
	m_ListControl_UserInfo.GetClientRect(&rect);
	m_ListControl_UserInfo.SetExtendedStyle(m_ListControl_UserInfo.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ListControl_UserInfo.InsertColumn(0, _T("�û�"), LVCFMT_CENTER, rect.Width() / 2, 0);
	m_ListControl_UserInfo.InsertColumn(1, _T("�˿�"), LVCFMT_CENTER, rect.Width() / 2, 0);
	*/
	CELMSServerDlg* mainDlg = (CELMSServerDlg*)(AfxGetMainWnd());
	//CUserInfo* childDlg = (CUserInfo*)(FindWindow(_T("CUserInfo"), _T("IDD_USERINFO")));
	m_Username = mainDlg->m_Username;
	m_Userport = mainDlg->m_UserPort;
	m_IP = mainDlg->m_IP;
	m_Remain = mainDlg->m_Remain;
	mainDlg = NULL;
	CString str;
	str.Format(_T("%u"), m_Userport);
	m_ListControl_UserInfo.InsertItem(j, m_Username);
	//m_ListControl_UserInfo.InsertItem(j, strUser);
	CString pos;
	pos.Format(_T("%d"), j);
	m_ListControl_UserInfo.SetItemText(j, 1, pos);
	m_ListControl_UserInfo.SetItemText(j, 2, str);
	m_ListControl_UserInfo.SetItemText(j, 3, m_IP);
	m_ListControl_UserInfo.SetItemText(j, 4, m_Remain);
	++j;
}

void CUserInfo::OnAccept(CString szIP, UINT nPort)
{
	CString str;
	str.Format(_T("%s-%d:\r\n"), szIP, nPort);
	m_Userport = nPort;
	/*int nLen = m_txt.GetWindowTextLength();
	m_txt.SetSel(nLen, -1);
	m_txt.ReplaceSel(str);*/
}


void CUserInfo::OnBnClickedBtnEnd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	USES_CONVERSION;
	/*
	CUserDataBase db;
	db.initDB(); //��ʼ�����ݿ�
	_bstr_t bstrSQL = _T("select * from user");//����sql��䣬ѡ���
	_variant_t vUserName, vPassword, vRemain;
	_RecordsetPtr & pRes = db.GetRecordSet(bstrSQL);	//����GetRecordSet�������õ���¼��
	CELMSServerDlg* SrvDlg = (CELMSServerDlg*)AfxGetMainWnd();

	int MSGTYPE = MYMSG_LOGOFF;
	int i = 0;
	int ii = 0;
	while (theApp.Mess[i].portS != m_Userport)
	{
		i++;
	}
	CSocketServer *p = theApp.Mess[i].pSocketS;
	CString s;
	s.Format(_T("%d"), m_Userport);

	//CUserInfo* p = (CUserInfo*)FindWindow(_T("CUserInfo"), _T("����ҳ��"));
	int i = 0;
	int ii = 0;
	while (theApp.Mess[i].portS != m_Userport)
	{
		i++;
	}
	CString s;
	s.Format(_T("%d"), m_Userport);
	while (m_ListControl_UserInfo.GetItemText(ii, 2) != s)
	{
		ii++;
	}

	p->SendTo(&MSGTYPE, sizeof(MSGTYPE), theApp.Mess[i].portS);*/
	/*CELMSServerDlg* mainDlg = (CELMSServerDlg*)(AfxGetMainWnd());
	int MSGTYPE = MYMSG_END;
	this->Send(&MSGTYPE, sizeof(MSGTYPE));
	bool end = true;
	this->Send(&end, sizeof(end));*/
	
	theApp.Mess[0].pSocketS->Logoff();

	/*CUser userInfo;
	this->Receive(&userInfo, sizeof(CUser));

	CString strUserName = A2T(userInfo.getUserName());
	CString strPassWord = A2T(userInfo.getPassWord());
	CString strRemain = A2T(userInfo.getRemain());*/

	/*
	if (pRes == NULL)
	{
		db.closeDB();
		return;
	}
	while (!pRes->adoEOF)//���ָ��δָ���ĩ
	{
		vUserName = pRes->GetCollect(_T("username"));
		vPassword = pRes->GetCollect(_T("password"));
		vRemain = pRes->GetCollect(_T("remain"));
		bool bRes = true;


		if (!::wcscmp(strUserName, (LPCWSTR)(_bstr_t)vUserName))//�ַ�����
		{

			CString str;
			str.Format(_T("UPDATE user SET remain = %d WHERE username = %s"), strRemain, strUserName);
			_bstr_t updateSQL = str;
			db.initDB();
			db.ExecuteSQL(updateSQL);

			//CELMSServerDlg *p = (CELMSServerDlg*)AfxGetMainWnd();
			CUserInfo* p = (CUserInfo*)FindWindow(_T("CUserInfo"), _T("����ҳ��"));
			int i = 0;
			int ii = 0;
			while (theApp.Mess[i].portS != m_uPort)
			{
				i++;
			}
			CString s;
			s.Format(_T("%d"), m_uPort);
			while (p->m_ListControl_UserInfo.GetItemText(ii, 2) != s)
			{
				ii++;
			}
			p->m_ListControl_UserInfo.DeleteItem(ii);
			counter--;

			return;


		}
		else
		{
			pRes->MoveNext();//�ƶ���¼ָ�뵽��һ��
		}
	}
	pRes->Close();
	db.closeDB();*/
}



void CUserInfo::OnLvnItemchangedListUserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	CString str;    // �ַ��� 
					//��NMHDR�������ࣨ�ṹ�壩֮һ����ר����LISTVIEW��WM_NOTIFY��Ϣ
	NMLISTVIEW *pNMListView = (NMLISTVIEW*)pNMHDR;

	if (-1 != pNMListView->iItem)        // ���iItem����-1����˵�����б��ѡ��   
	{
		// ��ȡ��ѡ���б����һ��������ı�   
		m_Username = m_ListControl_UserInfo.GetItemText(pNMListView->iItem, 0);
		// ��ѡ������ݵ�����  
		
	}
}



void CUserInfo::OnBnClickedBtnRecharge()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CRecharge dlg;
	ShowWindow(SW_HIDE);
	dlg.DoModal();
	ShowWindow(SW_SHOW);
}
