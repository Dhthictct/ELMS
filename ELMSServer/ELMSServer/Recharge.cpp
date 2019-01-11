// Recharge.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ELMSServer.h"
#include "Recharge.h"
#include "afxdialogex.h"


// CRecharge �Ի���

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


// CRecharge ��Ϣ�������


void CRecharge::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	USES_CONVERSION;
	CUserDataBase db;
	_bstr_t bstrSQL = _T("select * from user");

	CString strUsername = m_Username;
	int strRemain = m_Money;
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
				db.closeDB(); //�ر����ݿ�����
				MessageBox(_T("��ֵ�ɹ�"));
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
	}
	//CDialogEx::OnOK();
}
