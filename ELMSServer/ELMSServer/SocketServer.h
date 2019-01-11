#pragma once

// CSocketServer 命令目标
//服务器端套接字，主要为客户端服务（接受和发送内容）
class CSocketServer : public CSocket
{
public:
	CSocketServer();
	virtual ~CSocketServer();
	virtual void OnReceive(int nErrorCode); //接受协议
	void Login(); //用于登录协议的处理
	void Register();//用于注册协议的处理
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


