#pragma once
class CUser
{
public:
	CUser();
	~CUser();
	//有参构造函数
	CUser(char* strUserName, char* strPwd);
	//各种get和set方法
	char* getUserName();
	void setUserName(char* strUserName);
	char* getPassWord();
	void setPassWord(char* strPassWord);
	char* getRemain();
	void setRemain(char* Remain);
	

	//定义成private，就必须要写get和set方法
private:
	char m_UserName[16];
	char m_PassWord[16];
	char m_Remain[4];
};

