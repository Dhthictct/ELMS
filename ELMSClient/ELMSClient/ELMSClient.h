
// ELMSClient.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CELMSClientApp: 
// �йش����ʵ�֣������ ELMSClient.cpp
//

class CELMSClientApp : public CWinApp
{
public:
	CELMSClientApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CELMSClientApp theApp;