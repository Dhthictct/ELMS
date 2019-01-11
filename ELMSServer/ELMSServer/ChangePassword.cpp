// ChangePassword.cpp : 实现文件
//

#include "stdafx.h"
#include "ELMSServer.h"
#include "ChangePassword.h"
#include "afxdialogex.h"
#include "ELMSServerDlg.h"

// CChangePassword 对话框

IMPLEMENT_DYNAMIC(CChangePassword, CDialogEx)

CChangePassword::CChangePassword(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_CHANGE, pParent)
	, m_Edt_Username(_T(""))
	, m_Edt_Password(_T(""))
	, m_Edt_NewPwd(_T(""))
	, m_Edt_NewOncePwd(_T(""))
{

}

CChangePassword::~CChangePassword()
{
}

void CChangePassword::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDT_USERNAME, m_Edt_Username);
	DDX_Text(pDX, IDC_EDT_PASSWORD, m_Edt_Password);
	DDX_Text(pDX, IDC_EDT_NEWPASSWORD, m_Edt_NewPwd);
	DDX_Text(pDX, IDC_EDT_NEWONCEPASSWORD, m_Edt_NewOncePwd);
}


BEGIN_MESSAGE_MAP(CChangePassword, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_CHANGE, &CChangePassword::OnBnClickedBtnChange)
END_MESSAGE_MAP()


// CChangePassword 消息处理程序


void CChangePassword::OnBnClickedBtnChange()
{
	// TODO: 在此添加控件通知处理程序代码
	USES_CONVERSION;
	UpdateData(TRUE);
	CUserDataBase db;
	CString strUserName = m_Edt_Username;
	CString strPassWord = m_Edt_Password;
	
	if (strUserName.IsEmpty() || strPassWord.IsEmpty())
	{
		MessageBox(_T("用户名和密码不能为空"));
		return;
	}
	if (m_Edt_NewPwd != m_Edt_NewOncePwd)
	{
		MessageBox(_T("两次密码不一致，请检查密码"));
	}
	/*_bstr_t strSQL = _T("insert into user(username,password，remain) values('");
	strSQL = strSQL + strUserName + _T("','");
	strSQL = strSQL + strPassWord + _T("','");
	strSQL = strSQL + strRemain + _T("')");*/

	_bstr_t bstrSQL = _T("select * from administrator");
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
			if (!::wcscmp(strUserName.GetString(), (LPCWSTR)(_bstr_t)vUserName) && !::wcscmp(strPassWord.GetString(), (LPCWSTR)(_bstr_t)vPassword.bstrVal))
			{
				/*_bstr_t strSQL = _T("insert into administrator(username,password) values('");
				strSQL = strSQL + strUserName + _T("','");
				strSQL = strSQL + strPassWord + _T("','");*/
				CString strsql;
				strsql.Format(_T("update administrator set password = %s where username=%s"), m_Edt_NewPwd, strUserName);
				pRes = db.m_pConnection->Execute(_bstr_t(strsql), NULL, adCmdText);
				db.closeDB(); //关闭数据库连接
				MessageBox(_T("修改成功"));
				OnOK();
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
		MessageBox(_T("修改失败"));
		OnOK();
	}

	
	//写入日志文件
	/*CFile file;
	if (!file.Open(_T("log"), CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite))
	{
		AfxMessageBox(_T("打开失败！"));
	}
	file.SeekToEnd(); //移动到文件的末尾
	char aLog[1024] = { '\0' };
	*/
}
