#pragma once

// CSocketServer ����Ŀ��
//���������׽��֣���ҪΪ�ͻ��˷��񣨽��ܺͷ������ݣ�
class CSocketServer : public CSocket
{
public:
	CSocketServer();
	virtual ~CSocketServer();
	virtual void OnReceive(int nErrorCode); //����Э��
	void Login(); //���ڵ�¼Э��Ĵ���
	void Register();//����ע��Э��Ĵ���
	void Recharge();
	void Query();
	void Save();
	void Close();
	void Message();
	UINT m_uPort;
	CString strUser;
	CString IP;
	void Logoff();
	void setcounter();
	int getcounter();
};


