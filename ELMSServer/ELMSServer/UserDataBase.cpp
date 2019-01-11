#include "stdafx.h"
#include "UserDataBase.h"


CUserDataBase::CUserDataBase()
{
}


CUserDataBase::~CUserDataBase()
{
}


//����ע�͵�����
/*********************************
��������initDB
������������ʼ�����ݿ�����
��������
����ֵ��BOOL���ͣ�TRUE�ɹ�������FALSE
ע������:��
**********************************/
BOOL CUserDataBase::initDB()
{

	try
	{
		//�����������ַ���
		_bstr_t strConn = _T("Driver=MySQL ODBC 5.3 Unicode Driver;SERVER=127.0.0.1;UID=root;DATABASE=userdatabase;PORT=3306");
		//��ʼ��
		m_pConnection.CreateInstance(_T("ADODB.Connection"));
		//����open����
		m_pConnection->Open(strConn, _T("root"), _T("ai2727262396"), adModeUnknown);

	}
	catch (_com_error e)
	{
		//��ʾ������Ϣ
		AfxMessageBox(e.Description());
		return FALSE;
	}

	return TRUE;
}

/*********************************
��������closeDB
�����������ر����ݿ�����
��������
����ֵ����
ע������:����ֻ�ǹر������ݿ������
**********************************/
void CUserDataBase::closeDB()
{
	//�ж��Ƿ�Ϊ�գ������Ϊ�գ��͹ر�������ӵ�����ָ��
	if (m_pConnection != NULL)
	{
		m_pConnection->Close();
	}
}


// ��ȡ��ѯ�ļ�¼������Ҫ�����ڲ�ѯ���
/*********************************
��������GetRecordSet
������������ȡ��ѯ�ļ�¼������Ҫ�����ڲ�ѯ���
������strSQL  _bstr_t���ͣ�������sql���
����ֵ����¼������ _RecordsetPtr&�����ΪNULL����ʾδ��ѯ�������ѯ����
ע������:��Ҫ�Լ��ֶ���ȥ�ر������¼��
**********************************/
_RecordsetPtr& CUserDataBase::GetRecordSet(_bstr_t strSQL)
{
	//TODO: insert return statement here
	try
	{
		//���жϣ��Ƿ������������ݿ�
		if (m_pConnection == NULL)
		{
			//���򣬾��������ݿ�
			initDB();
		}
		//��ʼ��
		m_pRecordset.CreateInstance(_T("ADODB.Recordset"));
		//����open������ �õ���ѯ�ļ�¼��
		m_pRecordset->Open(strSQL, (IDispatch*)m_pConnection, adOpenStatic, adLockReadOnly, adCmdText);
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.Description());
		m_pRecordset = NULL; //������쳣������ΪNULL
	}

	return m_pRecordset; //����ɹ������صõ��ļ�¼��
}


// ��Ҫ���ڲ��룬���µ�SQL������
/*********************************
��������ExecuteSQL
������������ȡ��ѯ�ļ�¼�Ľ������Ҫ�����ڲ��룬���µ�sql���
������strSQL  _bstr_t���ͣ�������sql���
����ֵ���ɹ�ΪTRUE������ΪFALSE
ע������:��
**********************************/
BOOL CUserDataBase::ExecuteSQL(_bstr_t strSQL)
{
	try
	{
		//������Ĵ���һ�������ж�
		if (m_pConnection == NULL)
		{
			initDB();
		}
		//��ʼ����������
		m_pCommand.CreateInstance(_T("ADODB.Command"));
		m_pCommand->CommandText = strSQL;
		m_pCommand->ActiveConnection = m_pConnection;
		//�������ݿ�
		m_pCommand->Execute(NULL, NULL, adCmdText);
	}
	catch (_com_error e)
	{
		AfxMessageBox(_T("��ӻ����ʧ�ܣ�"));
		return FALSE; //ʧ��ΪFALSE
	}
	return TRUE; //�ɹ�ΪTRUE
}


BOOL CUserDataBase::initDBp()

{
	try
	{
		//�����������ַ���
		_bstr_t strConn = _T("Driver=MySQL ODBC 5.3 Unicode Driver;SERVER=127.0.0.1;UID=root;DATABASE=userdatabase;PORT=3306");
		//��ʼ��
		m_pConnection.CreateInstance(_T("ADODB.Connection"));
		//����open����
		m_pConnection->Open(strConn, _T("root"), _T("ai2727262396"), adModeUnknown);

	}
	catch (_com_error e)
	{
		//��ʾ������Ϣ
		AfxMessageBox(e.Description());
		return FALSE;
	}
	return TRUE;
	return 0;
}
