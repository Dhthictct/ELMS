// SocketServer.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ELMSServer.h"
#include "SocketServer.h"
#include "ELMSServerDlg.h"

#include "UserInfo.h"
// CSocketServer


static int counter = 0;
static int counterp = 0;

CSocketServer::CSocketServer()
{
}

CSocketServer::~CSocketServer()
{
}



// CSocketServer ��Ա����
//��д���麯�������ܿͻ��˷��͹�����Э��
void CSocketServer::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���

	//�������գ��Ƚ��մ�������TCPͨѶЭ��
	int MSGTYPE; //����һ���������յ�Э��
	this->Receive(&MSGTYPE, sizeof(MSGTYPE)); //��ʼ����
	switch (MSGTYPE) //����������Э�飬���ദ��
	{
	case MYMSG_LOGIN: //��¼Э��
	{
		Login();
	}
	break;
	case MYMSG_REGISTER: //ע��Э��
	{
		Register();
	}
	break;
	case MYMSG_SELECTION: //��ѯЭ��
	{
		Query();
	}
	break;
	case MYMSG_SAVE: //����Э��
	{
		Save();
	}
	break;
	case MYMSG_RECHARGE: //��ֵ
	{
		Recharge();
	}
	break;
	case MYMSG_END: 
	{
		Close();
	}
	break;
	case MYMSG_MESSAGE:
	{
		Message();
	}
	break;
	case MYMSG_LOGOFF:
	{
		Logoff();
	}
	break;
	}

	CSocket::OnReceive(nErrorCode);
}


//�����¼
/*********************************
��������Login
���������������¼�����͵�¼�Ƿ�ɹ������ݸ��ͻ���
��������
����ֵ����
ע������:�õ��˼�¼���Ķ�����������Լ��ر�
**********************************/
void CSocketServer::Login()
{
	USES_CONVERSION; //���������ַ���ת��
	bool bRes = false;  //���ڸ��ͻ��˷������ݵı�������ʼ��Ϊfalse
	CUserDataBase db;
	db.initDB(); //��ʼ�����ݿ�
	CUser userInfo;
	CString strData;
	CELMSServerDlg* SrvDlg = (CELMSServerDlg*)AfxGetMainWnd();

	//ADD
	/*COleDateTime time = COleDateTime::GetCurrentTime();
	CString strTime;
	strTime.Format(_T("%d��%d��%d�� %02d:%02d:%02d"), time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
	strData += _T(" ");
	strData += strTime;
	strData += _T("\r\n");*/

	//�����жϽ��յ������Ƿ���ȷ
	if (this->Receive(&userInfo, sizeof(CUser)) != sizeof(CUser))
	{
		//�������ʧ�ܣ��ͷ������ݣ���ʱbRes��ֵΪfalse
		this->Send(&bRes, sizeof(bRes));
		db.closeDB(); //���ر����ݿ�
		/*strData += _T("�ͻ��˵�¼ʧ�ܣ�\r\n");
		SrvDlg->m_Edt_Log.SetSel(-1, -1);
		SrvDlg->m_Edt_Log.ReplaceSel(strData);*/
		return;
	}

	//�ַ�����ת��
	CString strUserName = A2T(userInfo.getUserName());
	CString strPassWord = A2T(userInfo.getPassWord());
	//ת�����ж�
	if (strUserName.IsEmpty() || strPassWord.IsEmpty())
	{
		//���Ϊ�գ��ͷ������ݣ���ʱbRes��ֵΪfalse
		this->Send(&bRes, sizeof(bRes));
		db.closeDB(); //�ر����ݿ�����,������
		/*strData += _T("�ͻ��˵�¼ʧ�ܣ�\r\n");
		SrvDlg->m_Edt_Log.SetSel(-1, -1);
		SrvDlg->m_Edt_Log.ReplaceSel(strData);*/
		return;
	}

	//����sql���
	_bstr_t bstrSQL = _T("select * from user");
	_variant_t vUserName, vPassword;

	//����GetRecordSet�������õ���¼��
	_RecordsetPtr & pRes = db.GetRecordSet(bstrSQL);

	try
	{
		//�жϼ�¼�����Ϊ�գ�����false���ݣ�������
		if (pRes == NULL)
		{
			this->Send(&bRes, sizeof(bRes));
			db.closeDB();
			/*strData += _T("�ͻ��˵�¼ʧ�ܣ�\r\n");
			SrvDlg->m_Edt_Log.SetSel(-1, -1);
			SrvDlg->m_Edt_Log.ReplaceSel(strData);*/
			return;
		}
		//����ʹ��adoEOF�Լ�¼�����б���
		while (!pRes->adoEOF)
		{
			vUserName = pRes->GetCollect(_T("username"));//����Ϊ���ݿ������
			vPassword = pRes->GetCollect(_T("password"));

			//���õ���ֵ��༭���е�ֵ���бȽϣ������漰�����ַ����������
			if (!::wcscmp(strUserName.GetString(), (LPCWSTR)(_bstr_t)vUserName) && !::wcscmp(strPassWord.GetString(), (LPCWSTR)(_bstr_t)vPassword.bstrVal))
			{
				pRes->Close();//�����ƥ�䣬�ر������¼ָ�룬��Ҫ�ֶ���ȥ�ͷ�
				db.closeDB(); //�ر����ݿ�����
				bRes = true; //��������Ϊtrue������
				this->Send(&bRes, sizeof(bRes));
				/*strData += _T("�ͻ��˵�¼�ɹ���\r\n");
				SrvDlg->m_Edt_Log.SetSel(-1, -1);
				SrvDlg->m_Edt_Log.ReplaceSel(strData);*/
				return;
			}
			else
			{
				pRes->MoveNext();//���û�в�ѯ�������ƶ������¼ָ�뵽��һ��
			}

		}
		//���ֹرգ�����������
		pRes->Close();
		db.closeDB();
		this->Send(&bRes, sizeof(bRes));
		/*strData += _T("�ͻ��˵�¼ʧ�ܣ�\r\n");
		SrvDlg->m_Edt_Log.SetSel(-1, -1);
		SrvDlg->m_Edt_Log.ReplaceSel(strData);*/
		return;
	}
	catch (_com_error e)
	{
		//���߽���Ĳ�����־д���ļ� CFile��
		this->Send(&bRes, sizeof(bRes));
		db.closeDB();
		strData += _T("�ͻ��˵�¼ʧ�ܣ�\r\n");
		SrvDlg->m_Edt_Log.SetSel(-1, -1);
		SrvDlg->m_Edt_Log.ReplaceSel(strData);
	}
}

/*********************************
��������Register
��������������ע�Ტ����ע���Ƿ�ɹ������ݸ��ͻ���
��������
����ֵ����
ע������:��
**********************************/
void CSocketServer::Register()
{
	//��Login�������ƵĴ���
	USES_CONVERSION;
	bool bRes = false;
	CUserDataBase db;
	CUser userInfo;

	this->Receive(&userInfo, sizeof(CUser));

	CString strUserName = A2T(userInfo.getUserName());
	CString strPassWord = A2T(userInfo.getPassWord());
	CString strRemain;
	strRemain = "0";
	
	if (strUserName.IsEmpty() || strPassWord.IsEmpty())
	{
		this->Send(&bRes, sizeof(bRes));
		return;
	}
	/*_bstr_t strSQL = _T("insert into user(username,password��remain) values('");
	strSQL = strSQL + strUserName + _T("','");
	strSQL = strSQL + strPassWord + _T("','");
	strSQL = strSQL + strRemain + _T("')");*/

	_bstr_t strSQL = _T("insert into user(username,password,remain) values('");
	strSQL = strSQL + strUserName + _T("','");
	strSQL = strSQL + strPassWord + _T("','");
	strSQL = strSQL + strRemain + _T("')");
	//д����־�ļ�
	CFile file;
	if (!file.Open(_T("log"), CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite))
	{
		AfxMessageBox(_T("��ʧ�ܣ�"));
	}
	file.SeekToEnd(); //�ƶ����ļ���ĩβ
	char aLog[1024] = { '\0' };

	db.initDB();
	if (!db.ExecuteSQL(strSQL))
	{
		db.closeDB();
		this->Send(&bRes, sizeof(bRes));
		strcpy_s(aLog, "�ͻ��˷���ע����Ϣ��ע��ʧ�ܣ�\n");
		file.Write(aLog, strlen(aLog));
		file.Close();
		return;
	}
	else
	{
		db.closeDB();
		bRes = true;
		this->Send(&bRes, sizeof(bRes));
		strcpy_s(aLog, "�ͻ��˷���ע����Ϣ��ע��ɹ���\n");
		file.Write(aLog, strlen(aLog));
		file.Close();
	}
}


void CSocketServer::Recharge()
{
	/*bool bRes = true;;
	this->Send(&bRes, sizeof(bRes));
	return;*/
	
	USES_CONVERSION;
	bool bRes = false;
	CUserDataBase db;
	CUser userInfo;

	this->Receive(&userInfo, sizeof(CUser));

	CString strUserName = A2T(userInfo.getUserName());
	CString strPassWord = A2T(userInfo.getPassWord());
	CString strRemain = A2T(userInfo.getRemain());
	int addRemain = _ttoi(strRemain);

	_bstr_t bstrSQL = _T("select * from user");
	_variant_t vUserName, vPassword, vRemain;

	//����GetRecordSet�������õ���¼��
	_RecordsetPtr & pRes = db.GetRecordSet(bstrSQL);
	try
	{
		//�жϼ�¼�����Ϊ�գ�����false���ݣ�������
		if (pRes == NULL)
		{
			this->Send(&bRes, sizeof(bRes));
			return;
		}
		//����ʹ��adoEOF�Լ�¼�����б���
		while (!pRes->adoEOF)
		{
			vUserName = pRes->GetCollect(_T("username"));//����Ϊ���ݿ������
			vPassword = pRes->GetCollect(_T("password"));
			vRemain = pRes->GetCollect(_T("remain"));
			if (!::wcscmp(strUserName.GetString(), (LPCWSTR)(_bstr_t)vUserName) && !::wcscmp(strPassWord.GetString(), (LPCWSTR)(_bstr_t)vPassword.bstrVal))
			{
				strRemain = vRemain;
				int sum = addRemain + _ttoi(strRemain);
				strRemain.Format(_T("%d"), sum);
				CString strsql;
				strsql.Format(_T("update user set remain = %s where username=%s"),strRemain,strUserName);
				pRes = db.m_pConnection->Execute(_bstr_t(strsql), NULL, adCmdText);
				
				//_bstr_t strSQL = _T("update user set remain=%s where pkcolumn =  strUserName", strRemain);
				/*
				strRemain = vRemain;
				int sum = addRemain + _ttoi(strRemain);
				strRemain.Format(_T("%d"), sum);
				_bstr_t strSQL = _T("insert into db_user(username,password��remain) values('");
				strSQL = strSQL + strUserName + _T("','");
				strSQL = strSQL + strPassWord + _T("','");
				strSQL = strSQL + strRemain + _T("')");*/

				//pRes->Close();//�����ƥ�䣬�ر������¼ָ�룬��Ҫ�ֶ���ȥ�ͷ�
				bRes = true; //��������Ϊtrue������
				db.closeDB(); //�ر����ݿ�����
				this->Send(&bRes, sizeof(bRes));
				this->Send(&sum, sizeof(sum));
				CUserInfo dlg;
				dlg.m_Username = vUserName;
				//dlg.m_Userport = 
				dlg.DoModal();
				
				return;
			}
			else
			{
				pRes->MoveNext();//���û�в�ѯ�������ƶ������¼ָ�뵽��һ��
			}
		}
		pRes->Close();
		db.closeDB();
		this->Send(&bRes, sizeof(bRes));
		return;
	}
	catch (_com_error e)
	{
		//���߽���Ĳ�����־д���ļ� CFile��
		this->Send(&bRes, sizeof(bRes));
		db.closeDB();
	}
}

void CSocketServer::Query()
{
	USES_CONVERSION;
	bool bRes = false;
	CUserDataBase db;
	CUser userInfo;
	this->Receive(&userInfo, sizeof(CUser));
	CString strUserName = A2T(userInfo.getUserName());
	CString strPassWord = A2T(userInfo.getPassWord());
	CString strRemain = A2T(userInfo.getRemain());
	_bstr_t bstrSQL = _T("select * from user");
	_variant_t vUserName, vPassword, vRemain;
	//����GetRecordSet�������õ���¼��
	_RecordsetPtr & pRes = db.GetRecordSet(bstrSQL);
	try
	{
		//�жϼ�¼�����Ϊ�գ�����false���ݣ�������
		if (pRes == NULL)
		{
			this->Send(&bRes, sizeof(bRes));
			return;
		}
		//����ʹ��adoEOF�Լ�¼�����б���
		while (!pRes->adoEOF)
		{
			vUserName = pRes->GetCollect(_T("username"));//����Ϊ���ݿ������
			vPassword = pRes->GetCollect(_T("password"));
			vRemain = pRes->GetCollect(_T("remain"));
			if (!::wcscmp(strUserName.GetString(), (LPCWSTR)(_bstr_t)vUserName) && !::wcscmp(strPassWord.GetString(), (LPCWSTR)(_bstr_t)vPassword.bstrVal))
			{
				strRemain = vRemain;
				int sum = _ttoi(strRemain);
				strRemain.Format(_T("%d"), sum);
				CString strsql;
				strsql.Format(_T("update user set remain = %s where username=%s"), strRemain, strUserName);

				CELMSServerDlg* mainDlg = (CELMSServerDlg*)(AfxGetMainWnd());
				mainDlg->m_Remain = strRemain;
				pRes = db.m_pConnection->Execute(_bstr_t(strsql), NULL, adCmdText);
				bRes = true; //��������Ϊtrue������
				db.closeDB(); //�ر����ݿ�����
				this->Send(&bRes, sizeof(bRes));
				this->Send(&sum, sizeof(sum));
				return;
			}
			else
			{
				pRes->MoveNext();//���û�в�ѯ�������ƶ������¼ָ�뵽��һ��
			}
		}
		pRes->Close();
		db.closeDB();
		this->Send(&bRes, sizeof(bRes));
		return;
	}
	catch (_com_error e)
	{
		//���߽���Ĳ�����־д���ļ� CFile��
		this->Send(&bRes, sizeof(bRes));
		db.closeDB();
	}
}

void CSocketServer::Save()
{
	USES_CONVERSION;
	bool bRes = false;
	CUserDataBase db;
	CUser userInfo;
	int sum;
	this->Receive(&userInfo, sizeof(CUser));
	this->Receive(&sum, sizeof(sum));
	CString strUserName = A2T(userInfo.getUserName());
	CString strPassWord = A2T(userInfo.getPassWord());
	CString strRemain = A2T(userInfo.getRemain());
	_bstr_t bstrSQL = _T("select * from user");
	_variant_t vUserName, vPassword, vRemain;
	//����GetRecordSet�������õ���¼��
	_RecordsetPtr & pRes = db.GetRecordSet(bstrSQL);
	try
	{
		//�жϼ�¼�����Ϊ�գ�����false���ݣ�������
		if (pRes == NULL)
		{
			this->Send(&bRes, sizeof(bRes));
			return;
		}
		//����ʹ��adoEOF�Լ�¼�����б���
		while (!pRes->adoEOF)
		{
			vUserName = pRes->GetCollect(_T("username"));//����Ϊ���ݿ������
			vPassword = pRes->GetCollect(_T("password"));
			vRemain = pRes->GetCollect(_T("remain"));
			if (!::wcscmp(strUserName.GetString(), (LPCWSTR)(_bstr_t)vUserName) && !::wcscmp(strPassWord.GetString(), (LPCWSTR)(_bstr_t)vPassword.bstrVal))
			{
				strRemain.Format(_T("%d"), sum);
				CString strsql;
				strsql.Format(_T("update user set remain = %s where username=%s"), strRemain, strUserName);
				pRes = db.m_pConnection->Execute(_bstr_t(strsql), NULL, adCmdText);
				bRes = true; //��������Ϊtrue������
				db.closeDB(); //�ر����ݿ�����
				this->Send(&bRes, sizeof(bRes));
				return;
			}
			else
			{
				pRes->MoveNext();//���û�в�ѯ�������ƶ������¼ָ�뵽��һ��
			}
		}
		pRes->Close();
		db.closeDB();
		this->Send(&bRes, sizeof(bRes));
		return;
	}
	catch (_com_error e)
	{
		//���߽���Ĳ�����־д���ļ� CFile��
		this->Send(&bRes, sizeof(bRes));
		db.closeDB();
	}
}


void CSocketServer::Close()
{
	USES_CONVERSION;
	bool bRes = false;
	bool tm = false;
	CUserDataBase db;
	CUser userInfo;
	int sum;
	struct node
	{
		int hour, minute, second;
	}time;
	this->Receive(&userInfo, sizeof(CUser));
	this->Receive(&sum, sizeof(sum));
	this->Receive(&time, sizeof(time));
	CString strUserName = A2T(userInfo.getUserName());
	CString strPassWord = A2T(userInfo.getPassWord());
	CString strRemain = A2T(userInfo.getRemain());
	_bstr_t bstrSQL = _T("select * from user");
	_variant_t vUserName, vPassword, vRemain;
	//����GetRecordSet�������õ���¼��
	_RecordsetPtr & pRes = db.GetRecordSet(bstrSQL);
	try
	{
		//�жϼ�¼�����Ϊ�գ�����false���ݣ�������
		if (pRes == NULL)
		{
			this->Send(&bRes, sizeof(bRes));
			return;
		}
		//����ʹ��adoEOF�Լ�¼�����б���
		while (!pRes->adoEOF)
		{
			vUserName = pRes->GetCollect(_T("username"));//����Ϊ���ݿ������
			vPassword = pRes->GetCollect(_T("password"));
			vRemain = pRes->GetCollect(_T("remain"));
			if (!::wcscmp(strUserName.GetString(), (LPCWSTR)(_bstr_t)vUserName) && !::wcscmp(strPassWord.GetString(), (LPCWSTR)(_bstr_t)vPassword.bstrVal))
			{
				bRes = true; //��������Ϊtrue������
				db.closeDB(); //�ر����ݿ�����
				this->Send(&bRes, sizeof(bRes));
				if (!time.hour && !time.minute && !time.second)
				{
					tm = true;
					this->Send(&tm, sizeof(tm));
				}
				else
				{
					this->Send(&tm, sizeof(tm));
				}
				return;
			}
			else
			{
				pRes->MoveNext();//���û�в�ѯ�������ƶ������¼ָ�뵽��һ��
			}
		}
		pRes->Close();
		db.closeDB();
		this->Send(&bRes, sizeof(bRes));
		return;
	}
	catch (_com_error e)
	{
		//���߽���Ĳ�����־д���ļ� CFile��
		this->Send(&bRes, sizeof(bRes));
		db.closeDB();
	}
}
void CSocketServer::Message()
{
	USES_CONVERSION;
	CUser userInfo;
	/*int sum;
	struct node
	{
		int hour, minute, second;
	}time;
	this->Receive(&sum, sizeof(sum));

	this->Receive(&time, sizeof(time));*/
	this->Receive(&userInfo, sizeof(CUser));
	CString strUserName = A2T(userInfo.getUserName());
	CString strPassWord = A2T(userInfo.getPassWord());
	//CString strRemain = A2T(userInfo.getRemain());
	CELMSServerDlg* mainDlg = (CELMSServerDlg*)(AfxGetMainWnd());
	mainDlg->m_Username = strUserName;
	mainDlg->m_UserPort = m_uPort;
	//mainDlg->m_IP = IP;
	mainDlg = NULL;
	//strUser = strUserName;
	return;
}


void CSocketServer::Logoff()
{
	USES_CONVERSION;
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/*CUserDataBase db;
	db.initDB(); //��ʼ�����ݿ�
	_bstr_t bstrSQL = _T("select * from user");//����sql��䣬ѡ���
	_variant_t vUserName, vPassword, vCardNum, vCardType, vFeeLeft;
	_RecordsetPtr & pRes = db.GetRecordSet(bstrSQL);	//����GetRecordSet�������õ���¼��
	CUser userInfo;
	this->Receive(&userInfo, sizeof(CUser));

	CString strUserName = A2T(userInfo.getUserName());
	CString strPassWord = A2T(userInfo.getPassWord());
	CString strRemain = A2T(userInfo.getRemain());
	//GetPeerName(back.ip, back.port);

	if (pRes == NULL)
	{
		db.closeDB();
		return;
	}
	while (!pRes->adoEOF)//���ָ��δָ���ĩ
	{
		vUserName = pRes->GetCollect(_T("username"));
		vPassword = pRes->GetCollect(_T("password"));
		vCardType = pRes->GetCollect(_T("remain"));
		bool bRes = true;


		if (!::wcscmp(strUserName, (LPCWSTR)(_bstr_t)vUserName))//�ַ�����
		{

			CString str;
			str.Format(_T("UPDATE user SET remain = %d WHERE username = %s"), strRemain, strUserName);
			_bstr_t updateSQL = str;
			db.initDB();
			db.ExecuteSQL(updateSQL);

			//CELMSServerDlg *p = (CELMSServerDlg*)AfxGetMainWnd();
			CUserInfo* p = (CUserInfo*)FindWindow(_T("CUserInfo"),_T("����ҳ��"));
			int i = 0;
			int ii = 0;
			while (theApp.Mess[i].portS != m_uPort)
			{
				i++;
			}
			CString s;
			s.Format(_T("%d"), m_uPort);
			while (p->m_ListControl_UserInfo.GetItemText(ii, 2) != s)
			{
				ii++;
			}
			p->m_ListControl_UserInfo.DeleteItem(ii);
			counter--;

			return;


		}
		else
		{
			pRes->MoveNext();//�ƶ���¼ָ�뵽��һ��
		}
	}
	pRes->Close();
	db.closeDB();*/
	CELMSServerDlg* mainDlg = (CELMSServerDlg*)(AfxGetMainWnd());
	int MSGTYPE = MYMSG_END;
	this->Send(&MSGTYPE, sizeof(MSGTYPE));
	bool end = true;
	this->Send(&end, sizeof(end));


}
void CSocketServer::setcounter()
{
	counter--;
}

int CSocketServer::getcounter()
{
	return counter;
}