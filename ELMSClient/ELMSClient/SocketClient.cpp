// SocketClient.cpp : 实现文件
//

#include "stdafx.h"
#include "ELMSClient.h"
#include "SocketClient.h"
#include "ELMSClientDlg.h"
#include "UserView.h"

// CSocketClient

CSocketClient::CSocketClient()
{
}

CSocketClient::~CSocketClient()
{
}


// CSocketClient 成员函数


void CSocketClient::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	
	int MSGTYPE;
	this->Receive(&MSGTYPE, sizeof(MSGTYPE)); //接收
	switch (MSGTYPE)
	{
	case MYMSG_END:
	{
		//End();
		bool end = false;
		this->Receive(&end, sizeof(end));
		if (end)
		{
			//CELMSClientDlg* p = (CELMSClientDlg*)AfxGetMainWnd();
			/*CELMSClientDlg dlg;
			dlg.DoModal();*/
			//HWND hWnd = FindWindow(_T("CUserView"), _T("管理页面"));

			HWND hWnd = FindWindow(NULL, _T("读书中"));
			CUserView* p = (CUserView*)CWnd::FromHandle(hWnd);
			p->GameOver();
		}
		
	}
	break;
	}
	CSocket::OnReceive(nErrorCode);
}
