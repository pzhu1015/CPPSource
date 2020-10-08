///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Data/SqlConnection.h"
#include "System/Data/SqlCommand.h"
#include "System/Data/SqlDataReader.h"
#include "System/Data/SqlParameter.h"
#include "System/Data/SqlTransaction.h"
#include "System/Exceptions/SqlException.h"
#include <ATLComTime.h>
#include <iostream>
using namespace System;
using namespace System::Data;
using namespace System::Exceptions;
#define MYSQL_CONNECTION_STRING "Provider = MSDASQL.1; Persist Security Info = True; Extended Properties = 'Driver=MySQL ODBC 8.0 Unicode Driver;SERVER=192.168.1.10;UID=root;PWD=12345;DATABASE=bigdata;PORT=3306'"
#define SQLSERVER_CONNECTION_STRING "Provider = SQLOLEDB.1;Persist Security Info = true; User ID = sa; Password = 12345;initial Catalog = sqlserver_test;Data Source = 192.168.1.4"
#define ORACLE_CONNECTION_STRING "Provider=MSDAORA.1;User ID=root;Password=123456;Data Source=192.168.1.5;Persist Security Info = False"

//CString convert to string: CT2A()
//string convert to CString: CA2T()
void TestSQLServer()
{
	DbConnectionPtr connection = nullptr;
	DbCommandPtr command = nullptr;
	DbDataReaderPtr reader = nullptr;
	DbTransactionPtr trans = nullptr;
	try
	{
		
		connection = std::make_shared<SqlConnection>(SQLSERVER_CONNECTION_STRING);
		connection->Open();
		std::string connection_string = connection->GetConnectionString();
		std::cout << "connection string: " << connection_string << std::endl;
		std::string database = connection->GetDatabase();
		std::cout << "current database : " << database << std::endl;
		int connection_timeout = connection->GetConnectionTimeout();
		std::cout << "connect timeout: " << connection_timeout << std::endl;


		int rows = 0;
		command = connection->CreateCommand();
		command->SetCommandText("select * from tb_test");
		std::string command_text = command->GetCommandText();
		std::cout << "command text: " << command_text << std::endl;
		CommandTypeEnum command_type = command->GetCommandType();
		int command_timeout = command->GetTimeout();
		std::cout << "command timeout: " << command_timeout << std::endl;

		reader = command->ExecuteReader();
		bool has = reader->HasRows();
		int fields = reader->FieldCount();
		while (reader->Read())
		{
			std::string f1 = reader->GetString("f1");
			std::string f2 = reader->GetString("f2");
			std::string f3 = reader->GetString("f3");
			std::cout << f1 << "\t" << f2 << "\t" << f3 << std::endl;
			f1 = reader->GetString((size_t)0);
			f2 = reader->GetString((int)1);
			f3 = reader->GetString((char)2);
			std::cout << f1 << "\t" << f2 << "\t" << f3 << std::endl;
			reader->NextResult();
		}

		command = connection->CreateCommand();
		command->SetCommandText("update tb_test set f1='eee' where f3='ccc'");
		command_text = command->GetCommandText();
		std::cout << "command text: " << command_text << std::endl;
		rows = command->ExecuteNoQuery();
		std::cout << "update success affect rows: " << rows << std::endl;
		command = connection->CreateCommand();
		command->SetCommandText("select * from tb_test");
		command_text = command->GetCommandText();
		std::cout << "command text: " << command_text << std::endl;
		reader = command->ExecuteReader();
		has = reader->HasRows();
		fields = reader->FieldCount();
		while (reader->Read())
		{
			std::string f1 = reader->GetString("f1");
			std::string f2 = reader->GetString("f2");
			std::string f3 = reader->GetString("f3");
			std::cout << f1 << "\t" << f2 << "\t" << f3 << std::endl;
			f1 = reader->GetString((short)0);
			f2 = reader->GetString((long long)1);
			f3 = reader->GetString(2);
			std::cout << f1 << "\t" << f2 << "\t" << f3 << std::endl;
			reader->NextResult();
		}
		reader->Close();
		command = connection->CreateCommand();
		command->SetCommandText("select count(*) from tb_test");
		std::cout << "command text: " << command->GetCommandText() << std::endl;
		auto obj = command->ExecuteScalar();
		std::cout << "account total: " << obj.intVal << std::endl;

		command = connection->CreateCommand();
		command->SetCommandText("select * from tb_test where f3=?");
		command->GetParameters().push_back(std::make_shared<SqlParameter>("f3", DataTypeEnum::adWChar, "ccc"));
		reader = command->ExecuteReader();
		while (reader->Read())
		{
			std::string f1 = reader->GetString("f1");
			std::string f2 = reader->GetString("f2");
			std::string f3 = reader->GetString("f3");
			std::cout << f1 << "\t" << f2 << "\t" << f3 << std::endl;
			f1 = reader->GetString(0);
			f2 = reader->GetString(1);
			f3 = reader->GetString(2);
			std::cout << f1 << "\t" << f2 << "\t" << f3 << std::endl;
			reader->NextResult();
		}
		reader->Close();
		command = connection->CreateCommand();
		command->SetCommandText("select * from tb_primary_key");
		reader = command->ExecuteReader();
		while (reader->Read())
		{
			std::string f1 = reader->GetString("f1");
			std::string f2 = reader->GetString("f2");
			std::string f3 = reader->GetString("f3");
			std::string f4 = reader->GetString("f4");
			std::cout << f1 << "\t" << f2 << "\t" << f3 << "\t" << f4 << std::endl;
			f1 = reader->GetString(0);
			f2 = reader->GetString(1);
			f3 = reader->GetString(2);
			f4 = reader->GetString(3);
			std::cout << f1 << "\t" << f2 << "\t" << f3 << "\t" << f4 << std::endl;
			reader->NextResult();
		}
		reader->Close();
		command = connection->CreateCommand();
		command->SetCommandText("insert into tb_primary_key(f1,f2,f3,f4) values(?,?,?,?)");
		command->GetParameters().push_back(std::make_shared<SqlParameter>("@f1", DataTypeEnum::adVarChar, "c111"));
		command->GetParameters().push_back(std::make_shared<SqlParameter>("@f2", DataTypeEnum::adVarChar, "c222"));
		command->GetParameters().push_back(std::make_shared<SqlParameter>("@f3", DataTypeEnum::adVarChar, "c333"));
		command->GetParameters().push_back(std::make_shared<SqlParameter>("@f4", DataTypeEnum::adVarChar, "c444"));
		rows = command->ExecuteNoQuery();
		trans = connection->BeginTransaction();
		command = connection->CreateCommand();
		command->SetCommandText("insert into tb_primary_key(f1,f2,f3,f4) values(?,?,?,?)");
		command->GetParameters().push_back(std::make_shared<SqlParameter>("@f1", DataTypeEnum::adVarChar, "c1111"));
		command->GetParameters().push_back(std::make_shared<SqlParameter>("@f2", DataTypeEnum::adVarChar, "c2222"));
		command->GetParameters().push_back(std::make_shared<SqlParameter>("@f3", DataTypeEnum::adVarChar, "c3333"));
		command->GetParameters().push_back(std::make_shared<SqlParameter>("@f4", DataTypeEnum::adVarChar, "c4444"));
		rows = command->ExecuteNoQuery();
		rows = command->ExecuteNoQuery();
		trans->Commit();

		
	}
	catch (SqlException &ex)
	{
		std::cout << ex.what() << std::endl;
		if (trans)
		{
			trans->Rollback();
		}
	}
}

void TestMySql()
{
	DbConnectionPtr connection = nullptr;
	DbCommandPtr command = nullptr;
	DbDataReaderPtr reader = nullptr;
	DbTransactionPtr trans = nullptr;
	SqlDataReaderPtr sql_reader = nullptr;
	SqlCommandPtr sql_command = nullptr;
	SqlConnectionPtr sql_connection = nullptr;
	try
	{	
		//通过ODBC数据源形式的连接字符串
		//SqlConnectionPtr connection = std::make_shared<SqlConnection>("DSN=test");	
		//通过源始连接配置
		connection = std::make_shared<SqlConnection>(MYSQL_CONNECTION_STRING);
		connection->Open();
		std::string connection_string = connection->GetConnectionString();
		std::cout << "connection string: " << connection_string << std::endl;
		std::string database = connection->GetDatabase();
		std::cout << "current database : " << database << std::endl;
		int connection_timeout = connection->GetConnectionTimeout();
		std::cout << "connect timeout: " << connection_timeout << std::endl;

		int rows = 0;
		
		//insert
		command = connection->CreateCommand();
		command->SetCommandText("INSERT INTO `bigdata`.`tb_test` (`f0`, `f1`, `f2`, `f3`, `f4`, `f5`, `f6`, `f7`, `f8`, `f9`, `f10`) VALUES (2, 'f1', 2, 3, 1, 1800000000000, 6.0, 7.0, 8.0, NOW(), NOW());");
		int rwos = command->ExecuteNoQuery();
		//delete
		command = connection->CreateCommand();
		command->SetCommandText("delete from tb_test where f0=2");
		rwos = command->ExecuteNoQuery();
		//select
		command = connection->CreateCommand();
		command->SetCommandText("select * from tb_test");
		reader = command->ExecuteReader();
		bool has = reader->HasRows();
		int fields = reader->FieldCount();
		while (reader->Read())
		{
			int f0 = reader->GetInt32("f0");
			std::string f1 = reader->GetString("f1");
			char f2 = reader->GetInt8("f2");
			short f3 = reader->GetInt16("f3");
			bool f4 = reader->GetBool("f4");
			int64_t f5 = reader->GetInt64("f5");
			float f6 = reader->GetFloat("f6");
			double f7 = reader->GetDouble("f7");
			DECIMAL f8 = reader->GetDecimal("f8");
			COleDateTime f9 = reader->GetDateTime("f9");
			COleDateTime f10 = reader->GetDateTime("f10");
			COleDateTime f11 = reader->GetDateTime("f11");
			std::cout
				<< f0 << "\t"
				<< f1 << "\t"
				<< (int)f2 << "\t"
				<< f3 << "\t"
				<< f4 << "\t"
				<< f5 << "\t"
				<< f6 << "\t"
				<< f7 << "\t"
				<< f8.Lo32 << "\t"
				<< CT2A(f9.Format(_T("%Y-%m-%d %H:%M:%S")).GetString()) << "\t"
				<< CT2A(f10.Format(_T("%Y-%m-%d")).GetString()) << "\t"
				<< CT2A(f11.Format(_T("%Y-%m-%d %H:%M:%S")).GetString())
				<< std::endl;
			reader->NextResult();
		}
		reader->Close();

		//update
		command = connection->CreateCommand();
		command->SetCommandText("update tb_test set f2=?,f3=?,f4=?,f5=?,f6=?,f7=?,f8=?,f9=?,f10=? where f0=?");
		command->GetParameters().push_back(std::make_shared<SqlParameter>("f2", DataTypeEnum::adTinyInt, 125));
		command->GetParameters().push_back(std::make_shared<SqlParameter>("f3", DataTypeEnum::adSmallInt, 32767));
		command->GetParameters().push_back(std::make_shared<SqlParameter>("f4", DataTypeEnum::adBoolean, 0));
		command->GetParameters().push_back(std::make_shared<SqlParameter>("f5", DataTypeEnum::adBigInt, 28000000000));
		command->GetParameters().push_back(std::make_shared<SqlParameter>("f6", DataTypeEnum::adDouble, 125.0));
		command->GetParameters().push_back(std::make_shared<SqlParameter>("f7", DataTypeEnum::adDouble, 125.0));
		command->GetParameters().push_back(std::make_shared<SqlParameter>("f8", DataTypeEnum::adDouble, 125.0));
		command->GetParameters().push_back(std::make_shared<SqlParameter>("f9", DataTypeEnum::adVarChar, COleDateTime::GetCurrentTime().Format(_T("%Y-%m-%d %H:%M:%S"))));
		command->GetParameters().push_back(std::make_shared<SqlParameter>("f9", DataTypeEnum::adVarChar, "2020-10-01"));
		command->GetParameters().push_back(std::make_shared<SqlParameter>("f0", DataTypeEnum::adInteger, 11));
		rows = command->ExecuteNoQuery();

		//select
		sql_connection = std::dynamic_pointer_cast<SqlConnection>(connection);
		sql_command = sql_connection->CreateCommand<SqlCommandPtr>();
		sql_command->SetCommandText("select * from tb_test");
		sql_reader = sql_command->ExecuteReader<SqlDataReaderPtr>();
		while (sql_reader->Read())
		{
			auto f0 = sql_reader->GetValue<int>("f0");
			auto f1 = sql_reader->GetValue<std::string>("f1");
			auto f2 = sql_reader->GetValue<__int8>("f2");
			auto f3 = sql_reader->GetValue<short>("f3");
			auto f4 = sql_reader->GetValue<bool>("f4");
			auto f5 = sql_reader->GetValue<__int64>("f5");
			auto f6 = sql_reader->GetValue<float>("f6");
			auto f7 = sql_reader->GetValue<double>("f7");
			auto f8 = sql_reader->GetValue<DECIMAL>("f8");
			auto f9 = sql_reader->GetValue<COleDateTime>("f9");
			auto f10 = sql_reader->GetValue<COleDateTime>("f10");
			auto f11 = sql_reader->GetValue<COleDateTime>("f11");
			std::cout
				<< f0 << "\t"
				<< f1 << "\t"
				<< (int)f2 << "\t"
				<< f3 << "\t"
				<< f4 << "\t"
				<< f5 << "\t"
				<< f6 << "\t"
				<< f7 << "\t"
				<< f8.Lo64 << "\t"
				<< CT2A(f9.Format(_T("%Y-%m-%d %H:%M:%S")).GetString()) << "\t"
				<< CT2A(f10.Format(_T("%Y-%m-%d")).GetString()) << "\t"
				<< CT2A(f11.Format(_T("%Y-%m-%d %H:%M:%S")).GetString())
				<< std::endl;
			sql_reader->NextResult();
		}
		sql_reader->Close();
	}
	catch (SqlException &ex)
	{
		std::cout << ex.what() << std::endl;
		if (trans)
		{
			trans->Rollback();
		}
	}
}

void TestOracle()
{
}

int main(int argc, char** argv)
{
	TestMySql();
	TestSQLServer();
	//TestOracle();
	getchar();
	return 1;
}