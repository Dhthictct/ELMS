#pragma once
#include "SocketServer.h"
// CSocketListen ����Ŀ��
//�����׽��֣�ֻ�������
class CSocketListen : public CSocket
{
public:
	CSocketListen();
	virtual ~CSocketListen();
	virtual void OnAccept(int nErrorCode); //�пͻ������ӷ�������
	virtual void OnClose(int nErrorCode);//�пͻ��˶Ͽ���������
};


