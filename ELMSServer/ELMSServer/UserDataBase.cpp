#include "stdafx.h"
#include "UserDataBase.h"


CUserDataBase::CUserDataBase()
{
}


CUserDataBase::~CUserDataBase()
{
}


//函数注释的例子
/*********************************
函数名：initDB
函数描述：初始化数据库连接
参数：无
返回值：BOOL类型，TRUE成功，否则FALSE
注意事项:无
**********************************/
BOOL CUserDataBase::initDB()
{

	try
	{
		//构建的连接字符串
		_bstr_t strConn = _T("Driver=MySQL ODBC 5.3 Unicode Driver;SERVER=127.0.0.1;UID=root;DATABASE=userdatabase;PORT=3306");
		//初始化
		m_pConnection.CreateInstance(_T("ADODB.Connection"));
		//调用open函数
		m_pConnection->Open(strConn, _T("root"), _T("ai2727262396"), adModeUnknown);

	}
	catch (_com_error e)
	{
		//显示错误信息
		AfxMessageBox(e.Description());
		return FALSE;
	}

	return TRUE;
}

/*********************************
函数名：closeDB
函数描述：关闭数据库连接
参数：无
返回值：无
注意事项:这样只是关闭了数据库的连接
**********************************/
void CUserDataBase::closeDB()
{
	//判断是否为空，如果不为空，就关闭这个连接的智能指针
	if (m_pConnection != NULL)
	{
		m_pConnection->Close();
	}
}


// 获取查询的记录集，主要是用于查询语句
/*********************************
函数名：GetRecordSet
函数描述：获取查询的记录集，主要是用于查询语句
参数：strSQL  _bstr_t类型，构建的sql语句
返回值：记录集引用 _RecordsetPtr&，如果为NULL，表示未查询到，或查询错误
注意事项:需要自己手动的去关闭这个记录集
**********************************/
_RecordsetPtr& CUserDataBase::GetRecordSet(_bstr_t strSQL)
{
	//TODO: insert return statement here
	try
	{
		//先判断，是否连接上了数据库
		if (m_pConnection == NULL)
		{
			//否则，就连接数据库
			initDB();
		}
		//初始化
		m_pRecordset.CreateInstance(_T("ADODB.Recordset"));
		//调用open函数， 得到查询的记录集
		m_pRecordset->Open(strSQL, (IDispatch*)m_pConnection, adOpenStatic, adLockReadOnly, adCmdText);
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.Description());
		m_pRecordset = NULL; //如果有异常，就置为NULL
	}

	return m_pRecordset; //如果成功，返回得到的记录集
}


// 主要用于插入，更新等SQL语句操作
/*********************************
函数名：ExecuteSQL
函数描述：获取查询的记录的结果，主要是用于插入，更新等sql语句
参数：strSQL  _bstr_t类型，构建的sql语句
返回值：成功为TRUE，否则为FALSE
注意事项:无
**********************************/
BOOL CUserDataBase::ExecuteSQL(_bstr_t strSQL)
{
	try
	{
		//和上面的代码一样，先判断
		if (m_pConnection == NULL)
		{
			initDB();
		}
		//初始化，并构建
		m_pCommand.CreateInstance(_T("ADODB.Command"));
		m_pCommand->CommandText = strSQL;
		m_pCommand->ActiveConnection = m_pConnection;
		//操作数据库
		m_pCommand->Execute(NULL, NULL, adCmdText);
	}
	catch (_com_error e)
	{
		AfxMessageBox(_T("添加或更新失败！"));
		return FALSE; //失败为FALSE
	}
	return TRUE; //成功为TRUE
}


BOOL CUserDataBase::initDBp()

{
	try
	{
		//构建的连接字符串
		_bstr_t strConn = _T("Driver=MySQL ODBC 5.3 Unicode Driver;SERVER=127.0.0.1;UID=root;DATABASE=userdatabase;PORT=3306");
		//初始化
		m_pConnection.CreateInstance(_T("ADODB.Connection"));
		//调用open函数
		m_pConnection->Open(strConn, _T("root"), _T("ai2727262396"), adModeUnknown);

	}
	catch (_com_error e)
	{
		//显示错误信息
		AfxMessageBox(e.Description());
		return FALSE;
	}
	return TRUE;
	return 0;
}
