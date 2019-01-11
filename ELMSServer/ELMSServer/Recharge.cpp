// Recharge.cpp : 实现文件
//

#include "stdafx.h"
#include "ELMSServer.h"
#include "Recharge.h"
#include "afxdialogex.h"


// CRecharge 对话框

IMPLEMENT_DYNAMIC(CRecharge, CDialogEx)

CRecharge::CRecharge(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_RECHARGE, pParent)
	, m_Username(_T(""))
	, m_Money(0)
{

}

CRecharge::~CRecharge()
{
}

void CRecharge::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDT_RECHARGE_USER, m_Username);
	DDX_Text(pDX, IDC_EDT_RECHARGE_MONEY, m_Money);
}


BEGIN_MESSAGE_MAP(CRecharge, CDialogEx)
	ON_BN_CLICKED(IDOK, &CRecharge::OnBnClickedOk)
END_MESSAGE_MAP()


// CRecharge 消息处理程序


void CRecharge::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	USES_CONVERSION;
	CUserDataBase db;
	_bstr_t bstrSQL = _T("select * from user");

	CString strUsername = m_Username;
	int strRemain = m_Money;
	_variant_t vUserName, vPassword, vRemain;

	//调用GetRecordSet函数，得到记录集
	_RecordsetPtr & pRes = db.GetRecordSet(bstrSQL);
	try
	{
		//判断记录集如果为空，发送false内容，并返回
		if (pRes == NULL)
		{
			return;
		}
		//否则，使用adoEOF对记录集进行遍历
		while (!pRes->adoEOF)
		{
			vUserName = pRes->GetCollect(_T("username"));//参数为数据库的列名
			vPassword = pRes->GetCollect(_T("password"));
			vRemain = pRes->GetCollect(_T("remain"));
			if ((!::wcscmp(m_Username.GetString(), (LPCWSTR)(_bstr_t)vUserName)))
			{
				CString strRemain;
				strRemain = vRemain;
				int sum = _ttoi(strRemain)+m_Money;
				strRemain.Format(_T("%d"), sum);
				CString strsql;
				strsql.Format(_T("update user set remain = %s where username=%s"), strRemain, m_Username);
				pRes = db.m_pConnection->Execute(_bstr_t(strsql), NULL, adCmdText);	
				db.closeDB(); //关闭数据库连接
				MessageBox(_T("充值成功"));
				return;
			}
			else
			{
				pRes->MoveNext();//如果没有查询到，就移动这个记录指针到下一行
			}
		}
		pRes->Close();
		db.closeDB();
		return;
	}
	catch (_com_error e)
	{
		//或者将其的操作日志写入文件 CFile类
		db.closeDB();
	}
	//CDialogEx::OnOK();
}
