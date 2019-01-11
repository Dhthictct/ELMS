// SocketClient.cpp : ʵ���ļ�
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


// CSocketClient ��Ա����


void CSocketClient::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���

	
	int MSGTYPE;
	this->Receive(&MSGTYPE, sizeof(MSGTYPE)); //����
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
			//HWND hWnd = FindWindow(_T("CUserView"), _T("����ҳ��"));

			HWND hWnd = FindWindow(NULL, _T("������"));
			CUserView* p = (CUserView*)CWnd::FromHandle(hWnd);
			p->GameOver();
		}
		
	}
	break;
	}
	CSocket::OnReceive(nErrorCode);
}
