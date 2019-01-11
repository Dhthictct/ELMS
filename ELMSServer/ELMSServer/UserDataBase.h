#pragma once

//导入msado15.dll文件，并将EOF重名为adEOF
#import  "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF","adoEOF")

//这个类只是一个简单的封装，可以去网上查找下载封装比较完全的ADO操作数据库类
//数据库类
class CUserDataBase
{
public:
	CUserDataBase();
	~CUserDataBase();

	//三种智能指针
	_ConnectionPtr m_pConnection; //连接
	_CommandPtr m_pCommand;
	_RecordsetPtr m_pRecordset;//记录集

	BOOL initDB(); //初始化数据库，主要是来进行数据库的连接
	void closeDB(); //关闭数据库，关闭连接
					// 获取查询的记录集，主要是用于查询语句,参数为sql查询语句，返回值为记录集引用
	_RecordsetPtr& GetRecordSet(_bstr_t strSQL);
	// 主要用于插入，更新等SQL语句操作，参数为sql查询语句，返回值为BOOL类型
	BOOL ExecuteSQL(_bstr_t strSQL);
	BOOL initDBp();
};

