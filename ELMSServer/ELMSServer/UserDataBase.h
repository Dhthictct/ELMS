#pragma once

//����msado15.dll�ļ�������EOF����ΪadEOF
#import  "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF","adoEOF")

//�����ֻ��һ���򵥵ķ�װ������ȥ���ϲ������ط�װ�Ƚ���ȫ��ADO�������ݿ���
//���ݿ���
class CUserDataBase
{
public:
	CUserDataBase();
	~CUserDataBase();

	//��������ָ��
	_ConnectionPtr m_pConnection; //����
	_CommandPtr m_pCommand;
	_RecordsetPtr m_pRecordset;//��¼��

	BOOL initDB(); //��ʼ�����ݿ⣬��Ҫ�����������ݿ������
	void closeDB(); //�ر����ݿ⣬�ر�����
					// ��ȡ��ѯ�ļ�¼������Ҫ�����ڲ�ѯ���,����Ϊsql��ѯ��䣬����ֵΪ��¼������
	_RecordsetPtr& GetRecordSet(_bstr_t strSQL);
	// ��Ҫ���ڲ��룬���µ�SQL������������Ϊsql��ѯ��䣬����ֵΪBOOL����
	BOOL ExecuteSQL(_bstr_t strSQL);
	BOOL initDBp();
};

