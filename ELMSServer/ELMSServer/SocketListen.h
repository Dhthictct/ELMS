#pragma once
#include "SocketServer.h"
// CSocketListen 命令目标
//监听套接字，只负责监听
class CSocketListen : public CSocket
{
public:
	CSocketListen();
	virtual ~CSocketListen();
	virtual void OnAccept(int nErrorCode); //有客户端连接服务器端
	virtual void OnClose(int nErrorCode);//有客户端断开服务器端
};


