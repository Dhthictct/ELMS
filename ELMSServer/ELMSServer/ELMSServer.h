
// ELMSServer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "SocketServer.h"

// CELMSServerApp: 
// �йش����ʵ�֣������ ELMSServer.cpp
//

class CELMSServerApp : public CWinApp
{
public:
	CELMSServerApp();

// ��д
public:
	virtual BOOL InitInstance();

	typedef struct node
	{
		CSocketServer* pSocketS;
		UINT portS;
	}ps;
	ps Mess[100]; //��¼ָ��

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CELMSServerApp theApp;