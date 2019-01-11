// SocketServer.cpp : 实现文件
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



// CSocketServer 成员函数
//重写的虚函数，接受客户端发送过来的协议
void CSocketServer::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	//用来接收，先接收传过来的TCP通讯协议
	int MSGTYPE; //定义一个用来接收的协议
	this->Receive(&MSGTYPE, sizeof(MSGTYPE)); //开始接收
	switch (MSGTYPE) //将接收来的协议，分类处理
	{
	case MYMSG_LOGIN: //登录协议
	{
		Login();
	}
	break;
	case MYMSG_REGISTER: //注册协议
	{
		Register();
	}
	break;
	case MYMSG_SELECTION: //查询协议
	{
		Query();
	}
	break;
	case MYMSG_SAVE: //保存协议
	{
		Save();
	}
	break;
	case MYMSG_RECHARGE: //充值
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


//检验登录
/*********************************
函数名：Login
函数描述：检验登录并发送登录是否成功的内容给客户端
参数：无
返回值：无
注意事项:得到了记录集的对象，用完后，需自己关闭
**********************************/
void CSocketServer::Login()
{
	USES_CONVERSION; //用来进行字符串转换
	bool bRes = false;  //用于给客户端发送内容的变量，初始化为false
	CUserDataBase db;
	db.initDB(); //初始化数据库
	CUser userInfo;
	CString strData;
	CELMSServerDlg* SrvDlg = (CELMSServerDlg*)AfxGetMainWnd();

	//ADD
	/*COleDateTime time = COleDateTime::GetCurrentTime();
	CString strTime;
	strTime.Format(_T("%d年%d月%d日 %02d:%02d:%02d"), time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
	strData += _T(" ");
	strData += strTime;
	strData += _T("\r\n");*/

	//用来判断接收的数据是否正确
	if (this->Receive(&userInfo, sizeof(CUser)) != sizeof(CUser))
	{
		//如果接受失败，就发送内容，此时bRes的值为false
		this->Send(&bRes, sizeof(bRes));
		db.closeDB(); //并关闭数据库
		/*strData += _T("客户端登录失败！\r\n");
		SrvDlg->m_Edt_Log.SetSel(-1, -1);
		SrvDlg->m_Edt_Log.ReplaceSel(strData);*/
		return;
	}

	//字符串的转换
	CString strUserName = A2T(userInfo.getUserName());
	CString strPassWord = A2T(userInfo.getPassWord());
	//转化后，判断
	if (strUserName.IsEmpty() || strPassWord.IsEmpty())
	{
		//如果为空，就发送内容，此时bRes的值为false
		this->Send(&bRes, sizeof(bRes));
		db.closeDB(); //关闭数据库连接,并返回
		/*strData += _T("客户端登录失败！\r\n");
		SrvDlg->m_Edt_Log.SetSel(-1, -1);
		SrvDlg->m_Edt_Log.ReplaceSel(strData);*/
		return;
	}

	//构建sql语句
	_bstr_t bstrSQL = _T("select * from user");
	_variant_t vUserName, vPassword;

	//调用GetRecordSet函数，得到记录集
	_RecordsetPtr & pRes = db.GetRecordSet(bstrSQL);

	try
	{
		//判断记录集如果为空，发送false内容，并返回
		if (pRes == NULL)
		{
			this->Send(&bRes, sizeof(bRes));
			db.closeDB();
			/*strData += _T("客户端登录失败！\r\n");
			SrvDlg->m_Edt_Log.SetSel(-1, -1);
			SrvDlg->m_Edt_Log.ReplaceSel(strData);*/
			return;
		}
		//否则，使用adoEOF对记录集进行遍历
		while (!pRes->adoEOF)
		{
			vUserName = pRes->GetCollect(_T("username"));//参数为数据库的列名
			vPassword = pRes->GetCollect(_T("password"));

			//将得到的值与编辑框中的值进行比较，这里涉及到了字符编码的问题
			if (!::wcscmp(strUserName.GetString(), (LPCWSTR)(_bstr_t)vUserName) && !::wcscmp(strPassWord.GetString(), (LPCWSTR)(_bstr_t)vPassword.bstrVal))
			{
				pRes->Close();//如果相匹配，关闭这个记录指针，需要手动的去释放
				db.closeDB(); //关闭数据库连接
				bRes = true; //将内容置为true并发送
				this->Send(&bRes, sizeof(bRes));
				/*strData += _T("客户端登录成功！\r\n");
				SrvDlg->m_Edt_Log.SetSel(-1, -1);
				SrvDlg->m_Edt_Log.ReplaceSel(strData);*/
				return;
			}
			else
			{
				pRes->MoveNext();//如果没有查询到，就移动这个记录指针到下一行
			}

		}
		//各种关闭，并发送内容
		pRes->Close();
		db.closeDB();
		this->Send(&bRes, sizeof(bRes));
		/*strData += _T("客户端登录失败！\r\n");
		SrvDlg->m_Edt_Log.SetSel(-1, -1);
		SrvDlg->m_Edt_Log.ReplaceSel(strData);*/
		return;
	}
	catch (_com_error e)
	{
		//或者将其的操作日志写入文件 CFile类
		this->Send(&bRes, sizeof(bRes));
		db.closeDB();
		strData += _T("客户端登录失败！\r\n");
		SrvDlg->m_Edt_Log.SetSel(-1, -1);
		SrvDlg->m_Edt_Log.ReplaceSel(strData);
	}
}

/*********************************
函数名：Register
函数描述：检验注册并发送注册是否成功的内容给客户端
参数：无
返回值：无
注意事项:无
**********************************/
void CSocketServer::Register()
{
	//和Login函数类似的处理
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
	/*_bstr_t strSQL = _T("insert into user(username,password，remain) values('");
	strSQL = strSQL + strUserName + _T("','");
	strSQL = strSQL + strPassWord + _T("','");
	strSQL = strSQL + strRemain + _T("')");*/

	_bstr_t strSQL = _T("insert into user(username,password,remain) values('");
	strSQL = strSQL + strUserName + _T("','");
	strSQL = strSQL + strPassWord + _T("','");
	strSQL = strSQL + strRemain + _T("')");
	//写入日志文件
	CFile file;
	if (!file.Open(_T("log"), CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite))
	{
		AfxMessageBox(_T("打开失败！"));
	}
	file.SeekToEnd(); //移动到文件的末尾
	char aLog[1024] = { '\0' };

	db.initDB();
	if (!db.ExecuteSQL(strSQL))
	{
		db.closeDB();
		this->Send(&bRes, sizeof(bRes));
		strcpy_s(aLog, "客户端发送注册消息，注册失败！\n");
		file.Write(aLog, strlen(aLog));
		file.Close();
		return;
	}
	else
	{
		db.closeDB();
		bRes = true;
		this->Send(&bRes, sizeof(bRes));
		strcpy_s(aLog, "客户端发送注册消息，注册成功！\n");
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

	//调用GetRecordSet函数，得到记录集
	_RecordsetPtr & pRes = db.GetRecordSet(bstrSQL);
	try
	{
		//判断记录集如果为空，发送false内容，并返回
		if (pRes == NULL)
		{
			this->Send(&bRes, sizeof(bRes));
			return;
		}
		//否则，使用adoEOF对记录集进行遍历
		while (!pRes->adoEOF)
		{
			vUserName = pRes->GetCollect(_T("username"));//参数为数据库的列名
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
				_bstr_t strSQL = _T("insert into db_user(username,password，remain) values('");
				strSQL = strSQL + strUserName + _T("','");
				strSQL = strSQL + strPassWord + _T("','");
				strSQL = strSQL + strRemain + _T("')");*/

				//pRes->Close();//如果相匹配，关闭这个记录指针，需要手动的去释放
				bRes = true; //将内容置为true并发送
				db.closeDB(); //关闭数据库连接
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
				pRes->MoveNext();//如果没有查询到，就移动这个记录指针到下一行
			}
		}
		pRes->Close();
		db.closeDB();
		this->Send(&bRes, sizeof(bRes));
		return;
	}
	catch (_com_error e)
	{
		//或者将其的操作日志写入文件 CFile类
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
	//调用GetRecordSet函数，得到记录集
	_RecordsetPtr & pRes = db.GetRecordSet(bstrSQL);
	try
	{
		//判断记录集如果为空，发送false内容，并返回
		if (pRes == NULL)
		{
			this->Send(&bRes, sizeof(bRes));
			return;
		}
		//否则，使用adoEOF对记录集进行遍历
		while (!pRes->adoEOF)
		{
			vUserName = pRes->GetCollect(_T("username"));//参数为数据库的列名
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
				bRes = true; //将内容置为true并发送
				db.closeDB(); //关闭数据库连接
				this->Send(&bRes, sizeof(bRes));
				this->Send(&sum, sizeof(sum));
				return;
			}
			else
			{
				pRes->MoveNext();//如果没有查询到，就移动这个记录指针到下一行
			}
		}
		pRes->Close();
		db.closeDB();
		this->Send(&bRes, sizeof(bRes));
		return;
	}
	catch (_com_error e)
	{
		//或者将其的操作日志写入文件 CFile类
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
	//调用GetRecordSet函数，得到记录集
	_RecordsetPtr & pRes = db.GetRecordSet(bstrSQL);
	try
	{
		//判断记录集如果为空，发送false内容，并返回
		if (pRes == NULL)
		{
			this->Send(&bRes, sizeof(bRes));
			return;
		}
		//否则，使用adoEOF对记录集进行遍历
		while (!pRes->adoEOF)
		{
			vUserName = pRes->GetCollect(_T("username"));//参数为数据库的列名
			vPassword = pRes->GetCollect(_T("password"));
			vRemain = pRes->GetCollect(_T("remain"));
			if (!::wcscmp(strUserName.GetString(), (LPCWSTR)(_bstr_t)vUserName) && !::wcscmp(strPassWord.GetString(), (LPCWSTR)(_bstr_t)vPassword.bstrVal))
			{
				strRemain.Format(_T("%d"), sum);
				CString strsql;
				strsql.Format(_T("update user set remain = %s where username=%s"), strRemain, strUserName);
				pRes = db.m_pConnection->Execute(_bstr_t(strsql), NULL, adCmdText);
				bRes = true; //将内容置为true并发送
				db.closeDB(); //关闭数据库连接
				this->Send(&bRes, sizeof(bRes));
				return;
			}
			else
			{
				pRes->MoveNext();//如果没有查询到，就移动这个记录指针到下一行
			}
		}
		pRes->Close();
		db.closeDB();
		this->Send(&bRes, sizeof(bRes));
		return;
	}
	catch (_com_error e)
	{
		//或者将其的操作日志写入文件 CFile类
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
	//调用GetRecordSet函数，得到记录集
	_RecordsetPtr & pRes = db.GetRecordSet(bstrSQL);
	try
	{
		//判断记录集如果为空，发送false内容，并返回
		if (pRes == NULL)
		{
			this->Send(&bRes, sizeof(bRes));
			return;
		}
		//否则，使用adoEOF对记录集进行遍历
		while (!pRes->adoEOF)
		{
			vUserName = pRes->GetCollect(_T("username"));//参数为数据库的列名
			vPassword = pRes->GetCollect(_T("password"));
			vRemain = pRes->GetCollect(_T("remain"));
			if (!::wcscmp(strUserName.GetString(), (LPCWSTR)(_bstr_t)vUserName) && !::wcscmp(strPassWord.GetString(), (LPCWSTR)(_bstr_t)vPassword.bstrVal))
			{
				bRes = true; //将内容置为true并发送
				db.closeDB(); //关闭数据库连接
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
				pRes->MoveNext();//如果没有查询到，就移动这个记录指针到下一行
			}
		}
		pRes->Close();
		db.closeDB();
		this->Send(&bRes, sizeof(bRes));
		return;
	}
	catch (_com_error e)
	{
		//或者将其的操作日志写入文件 CFile类
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
	// TODO: 在此添加控件通知处理程序代码
	/*CUserDataBase db;
	db.initDB(); //初始化数据库
	_bstr_t bstrSQL = _T("select * from user");//构建sql语句，选择表
	_variant_t vUserName, vPassword, vCardNum, vCardType, vFeeLeft;
	_RecordsetPtr & pRes = db.GetRecordSet(bstrSQL);	//调用GetRecordSet函数，得到记录集
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
	while (!pRes->adoEOF)//如果指针未指向表末
	{
		vUserName = pRes->GetCollect(_T("username"));
		vPassword = pRes->GetCollect(_T("password"));
		vCardType = pRes->GetCollect(_T("remain"));
		bool bRes = true;


		if (!::wcscmp(strUserName, (LPCWSTR)(_bstr_t)vUserName))//字符编码
		{

			CString str;
			str.Format(_T("UPDATE user SET remain = %d WHERE username = %s"), strRemain, strUserName);
			_bstr_t updateSQL = str;
			db.initDB();
			db.ExecuteSQL(updateSQL);

			//CELMSServerDlg *p = (CELMSServerDlg*)AfxGetMainWnd();
			CUserInfo* p = (CUserInfo*)FindWindow(_T("CUserInfo"),_T("管理页面"));
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
			pRes->MoveNext();//移动记录指针到下一行
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