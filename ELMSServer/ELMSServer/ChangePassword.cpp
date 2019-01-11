// ChangePassword.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ELMSServer.h"
#include "ChangePassword.h"
#include "afxdialogex.h"
#include "ELMSServerDlg.h"

// CChangePassword �Ի���

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


// CChangePassword ��Ϣ�������


void CChangePassword::OnBnClickedBtnChange()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	USES_CONVERSION;
	UpdateData(TRUE);
	CUserDataBase db;
	CString strUserName = m_Edt_Username;
	CString strPassWord = m_Edt_Password;
	
	if (strUserName.IsEmpty() || strPassWord.IsEmpty())
	{
		MessageBox(_T("�û��������벻��Ϊ��"));
		return;
	}
	if (m_Edt_NewPwd != m_Edt_NewOncePwd)
	{
		MessageBox(_T("�������벻һ�£���������"));
	}
	/*_bstr_t strSQL = _T("insert into user(username,password��remain) values('");
	strSQL = strSQL + strUserName + _T("','");
	strSQL = strSQL + strPassWord + _T("','");
	strSQL = strSQL + strRemain + _T("')");*/

	_bstr_t bstrSQL = _T("select * from administrator");
	_variant_t vUserName, vPassword, vRemain;
	//����GetRecordSet�������õ���¼��
	_RecordsetPtr & pRes = db.GetRecordSet(bstrSQL);
	try
	{
		//�жϼ�¼�����Ϊ�գ�����false���ݣ�������
		if (pRes == NULL)
		{
			return;
		}
		//����ʹ��adoEOF�Լ�¼�����б���
		while (!pRes->adoEOF)
		{
			vUserName = pRes->GetCollect(_T("username"));//����Ϊ���ݿ������
			vPassword = pRes->GetCollect(_T("password"));
			if (!::wcscmp(strUserName.GetString(), (LPCWSTR)(_bstr_t)vUserName) && !::wcscmp(strPassWord.GetString(), (LPCWSTR)(_bstr_t)vPassword.bstrVal))
			{
				/*_bstr_t strSQL = _T("insert into administrator(username,password) values('");
				strSQL = strSQL + strUserName + _T("','");
				strSQL = strSQL + strPassWord + _T("','");*/
				CString strsql;
				strsql.Format(_T("update administrator set password = %s where username=%s"), m_Edt_NewPwd, strUserName);
				pRes = db.m_pConnection->Execute(_bstr_t(strsql), NULL, adCmdText);
				db.closeDB(); //�ر����ݿ�����
				MessageBox(_T("�޸ĳɹ�"));
				OnOK();
				return;
			}
			else
			{
				pRes->MoveNext();//���û�в�ѯ�������ƶ������¼ָ�뵽��һ��
			}
		}
		pRes->Close();
		db.closeDB();
		return;
	}
	catch (_com_error e)
	{
		//���߽���Ĳ�����־д���ļ� CFile��
		db.closeDB();
		MessageBox(_T("�޸�ʧ��"));
		OnOK();
	}

	
	//д����־�ļ�
	/*CFile file;
	if (!file.Open(_T("log"), CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite))
	{
		AfxMessageBox(_T("��ʧ�ܣ�"));
	}
	file.SeekToEnd(); //�ƶ����ļ���ĩβ
	char aLog[1024] = { '\0' };
	*/
}
