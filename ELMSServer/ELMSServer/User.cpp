#include "stdafx.h"
#include "User.h"


CUser::CUser()
{
	strcpy_s(m_UserName, "");
	strcpy_s(m_PassWord, "");
}


CUser::CUser(char* strUserName, char* strPwd)
{
	strcpy_s(m_UserName, strUserName);
	strcpy_s(m_PassWord, strPwd);
}


CUser::~CUser()
{
}
//getºÍset·½·¨
char* CUser::getUserName()
{
	return m_UserName;
}
void CUser::setUserName(char* strUserName)
{
	strcpy_s(m_UserName, strUserName);
}
char* CUser::getPassWord()
{
	return m_PassWord;
}
void CUser::setPassWord(char* strPassWord)
{
	strcpy_s(m_PassWord, strPassWord);
}
char* CUser::getRemain()
{
	return m_Remain;
}
void CUser::setRemain(char* uiRemain)
{
	strcpy_s(m_Remain, uiRemain);
}