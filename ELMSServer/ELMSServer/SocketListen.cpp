// SocketListen.cpp : 实现文件
//

#include "stdafx.h"
#include "ELMSServer.h"
#include "SocketListen.h"
#include "SocketServer.h"
#include "ELMSServerDlg.h"

#include "UserInfo.h"
// CSocketListen

CSocketListen::CSocketListen()
{
	
}

CSocketListen::~CSocketListen()
{
}


// CSocketListen 成员函数
//监听套接字，有新用户连接
void CSocketListen::OnAccept(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	CSocketServer* pSockServer = new CSocketServer;
	Accept(*pSockServer);


	CString szIP;
	UINT nPort;
	CString Username;
	pSockServer->GetPeerName(szIP, nPort);
	
	CELMSServerDlg* Dlg = (CELMSServerDlg*)AfxGetMainWnd();
	Dlg->OnAccept(szIP, nPort);

	static int i = 0;
	theApp.Mess[i].pSocketS= pSockServer;
	++i;

	/*CUserInfo* pDlg = (CUserInfo*)AfxGetMainWnd();
	pDlg->OnAccept(szIP, nPort);*/

	CSocket::OnAccept(nErrorCode);
}

//监听套接字，有用户断开连接（关闭客户端，下线等）
void CSocketListen::OnClose(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	delete this;
	CSocket::OnClose(nErrorCode);
}