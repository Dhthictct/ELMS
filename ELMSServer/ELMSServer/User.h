#pragma once
class CUser
{
public:
	CUser();
	~CUser();
	//有参构造函数
	CUser(char* strUserName, char* strPwd);

	//get和set函数
	char* getUserName();
	void setUserName(char* strUserName);
	char* getPassWord();
	void setPassWord(char* strPassWord);
	char* getRemain();
	void setRemain(char* Remain);

	//定义成private，就必须要写get和set方法
	//这里如果将成员定义成CString类型，服务器端接受不到具体的值，收到的是错误的指针
private:
	char m_UserName[16];
	char m_PassWord[16];
	char m_Remain[4];
};

