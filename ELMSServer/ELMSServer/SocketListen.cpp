// SocketListen.cpp : ʵ���ļ�
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


// CSocketListen ��Ա����
//�����׽��֣������û�����
void CSocketListen::OnAccept(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
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

//�����׽��֣����û��Ͽ����ӣ��رտͻ��ˣ����ߵȣ�
void CSocketListen::OnClose(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	delete this;
	CSocket::OnClose(nErrorCode);
}