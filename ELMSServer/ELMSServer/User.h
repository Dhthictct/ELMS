#pragma once
class CUser
{
public:
	CUser();
	~CUser();
	//�вι��캯��
	CUser(char* strUserName, char* strPwd);

	//get��set����
	char* getUserName();
	void setUserName(char* strUserName);
	char* getPassWord();
	void setPassWord(char* strPassWord);
	char* getRemain();
	void setRemain(char* Remain);

	//�����private���ͱ���Ҫдget��set����
	//�����������Ա�����CString���ͣ��������˽��ܲ��������ֵ���յ����Ǵ����ָ��
private:
	char m_UserName[16];
	char m_PassWord[16];
	char m_Remain[4];
};

