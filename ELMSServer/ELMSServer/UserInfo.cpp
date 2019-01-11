// UserInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "ELMSServer.h"
#include "UserInfo.h"
#include "afxdialogex.h"
#include "ELMSServerDlg.h"
#include "SocketServer.h"
#include "Recharge.h"
// CUserInfo 对话框

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


// CUserInfo 消息处理程序


BOOL CUserInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//获取ListControl的位置和大小
	//根据rect来设置每一子项的大小
	CRect rect;
	m_ListControl_UserInfo.GetClientRect(&rect);
	m_ListControl_UserInfo.SetExtendedStyle(m_ListControl_UserInfo.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	
	m_ListControl_UserInfo.InsertColumn(0, _T("用户"), LVCFMT_CENTER, rect.Width() / 5, 0);
	m_ListControl_UserInfo.InsertColumn(1, _T("位置"), LVCFMT_CENTER, rect.Width() / 5, 0);
	m_ListControl_UserInfo.InsertColumn(2, _T("端口"), LVCFMT_CENTER, rect.Width() / 5, 0);
	m_ListControl_UserInfo.InsertColumn(3, _T("IP"),   LVCFMT_CENTER, rect.Width() / 5, 0);
	m_ListControl_UserInfo.InsertColumn(4, _T("余额"), LVCFMT_CENTER, rect.Width() / 5, 0);


	/*CString str;
	str.Format(_T("%u"), m_Userport);
	m_ListControl_UserInfo.InsertItem(0, m_Username);
	m_ListControl_UserInfo.SetItemText(0, 1, str);*/

	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
void CUserInfo::OnReceive(int nErrorCode)
{
	//m_Username = User.getUserName();
	/*int MSGTYPE; //定义一个用来接收的协议
	this->Receive(&MSGTYPE, sizeof(MSGTYPE)); //开始接收
	switch (MSGTYPE) //将接收来的协议，分类处理
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
	// TODO: 在此添加控件通知处理程序代码
	
	/*CRect rect;
	m_ListControl_UserInfo.GetClientRect(&rect);
	m_ListControl_UserInfo.SetExtendedStyle(m_ListControl_UserInfo.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ListControl_UserInfo.InsertColumn(0, _T("用户"), LVCFMT_CENTER, rect.Width() / 2, 0);
	m_ListControl_UserInfo.InsertColumn(1, _T("端口"), LVCFMT_CENTER, rect.Width() / 2, 0);
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
	// TODO: 在此添加控件通知处理程序代码
	USES_CONVERSION;
	/*
	CUserDataBase db;
	db.initDB(); //初始化数据库
	_bstr_t bstrSQL = _T("select * from user");//构建sql语句，选择表
	_variant_t vUserName, vPassword, vRemain;
	_RecordsetPtr & pRes = db.GetRecordSet(bstrSQL);	//调用GetRecordSet函数，得到记录集
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

	//CUserInfo* p = (CUserInfo*)FindWindow(_T("CUserInfo"), _T("管理页面"));
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
	while (!pRes->adoEOF)//如果指针未指向表末
	{
		vUserName = pRes->GetCollect(_T("username"));
		vPassword = pRes->GetCollect(_T("password"));
		vRemain = pRes->GetCollect(_T("remain"));
		bool bRes = true;


		if (!::wcscmp(strUserName, (LPCWSTR)(_bstr_t)vUserName))//字符编码
		{

			CString str;
			str.Format(_T("UPDATE user SET remain = %d WHERE username = %s"), strRemain, strUserName);
			_bstr_t updateSQL = str;
			db.initDB();
			db.ExecuteSQL(updateSQL);

			//CELMSServerDlg *p = (CELMSServerDlg*)AfxGetMainWnd();
			CUserInfo* p = (CUserInfo*)FindWindow(_T("CUserInfo"), _T("管理页面"));
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
			pRes->MoveNext();//移动记录指针到下一行
		}
	}
	pRes->Close();
	db.closeDB();*/
}



void CUserInfo::OnLvnItemchangedListUserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	CString str;    // 字符串 
					//是NMHDR的派生类（结构体）之一，它专用于LISTVIEW的WM_NOTIFY消息
	NMLISTVIEW *pNMListView = (NMLISTVIEW*)pNMHDR;

	if (-1 != pNMListView->iItem)        // 如果iItem不是-1，就说明有列表项被选择   
	{
		// 获取被选择列表项第一个子项的文本   
		m_Username = m_ListControl_UserInfo.GetItemText(pNMListView->iItem, 0);
		// 将选择的内容弹出来  
		
	}
}



void CUserInfo::OnBnClickedBtnRecharge()
{
	// TODO: 在此添加控件通知处理程序代码
	CRecharge dlg;
	ShowWindow(SW_HIDE);
	dlg.DoModal();
	ShowWindow(SW_SHOW);
}
