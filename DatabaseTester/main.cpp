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
#include "System/Base/Object.h"
#include "System/Base/Ptrs.h"
#include <iostream>
using namespace System;
using namespace System::Data;
using namespace System::Exceptions;
#define MYSQL_CONNECTION_STRING "Provider = MSDASQL.1; Persist Security Info = True; Extended Properties = 'Driver=MySQL ODBC 8.0 Unicode Driver;SERVER=192.168.1.10;UID=root;PWD=12345;DATABASE=bigdata;PORT=3306'"
#define SQLSERVER_CONNECTION_STRING "Provider = SQLOLEDB.1;Persist Security Info = true; User ID = sa; Password = 12345;initial Catalog = sqlserver_test;Data Source = 192.168.1.4"

void TestSQLServer()
{
	DbTransactionPtr trans = nullptr;
	try
	{
		
		DbConnectionPtr connection = std::make_shared<SqlConnection>(SQLSERVER_CONNECTION_STRING);
		connection->Open();
		std::string connection_string = connection->GetConnectionString();
		std::cout << "connection string: " << connection_string << std::endl;
		std::string database = connection->GetDatabase();
		std::cout << "current database : " << database << std::endl;
		int connection_timeout = connection->GetConnectionTimeout();
		std::cout << "connect timeout: " << connection_timeout << std::endl;


		int rows = 0;
		DbCommandPtr command = connection->CreateCommand();
		command->SetCommandText("select * from tb_test");
		std::string command_text = command->GetCommandText();
		std::cout << "command text: " << command_text << std::endl;
		CommandTypeEnum command_type = command->GetCommandType();
		int command_timeout = command->GetTimeout();
		std::cout << "command timeout: " << command_timeout << std::endl;

		DbDataReaderPtr reader = command->ExecuteReader();
		bool has = reader->HasRows();
		int fields = reader->FieldCount();
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
			f1 = reader->GetString(0);
			f2 = reader->GetString(1);
			f3 = reader->GetString(2);
			std::cout << f1 << "\t" << f2 << "\t" << f3 << std::endl;
			reader->NextResult();
		}
		command = connection->CreateCommand();
		command->SetCommandText("select count(*) from tb_test");
		std::cout << "command text: " << command->GetCommandText();
		auto obj = command->ExecuteScalar();
		std::cout << "account total: " << obj.intVal << std::endl;

		command = connection->CreateCommand();
		command->SetCommandText("select * from tb_test where f3=?");
		command->GetParameters().push_back(std::make_shared<SqlParameter>("f3", DataTypeEnum::adWChar, "ccc"));
		//command->SetCommandText("select * from tb_test where f3='ccc'");
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
		command = connection->CreateCommand();
		command->SetCommandText("insert into tb_primary_key(f1,f2,f3,f4) values(?,?,?,?)");
		command->GetParameters().push_back(std::make_shared<SqlParameter>("@f1", DataTypeEnum::adVarChar, "b111"));
		command->GetParameters().push_back(std::make_shared<SqlParameter>("@f2", DataTypeEnum::adVarChar, "b222"));
		command->GetParameters().push_back(std::make_shared<SqlParameter>("@f3", DataTypeEnum::adVarChar, "b333"));
		command->GetParameters().push_back(std::make_shared<SqlParameter>("@f4", DataTypeEnum::adVarChar, "b444"));
		rows = command->ExecuteNoQuery();
		trans = connection->BeginTransaction();
		command = connection->CreateCommand();
		command->SetCommandText("insert into tb_primary_key(f1,f2,f3,f4) values(?,?,?,?)");
		command->GetParameters().push_back(std::make_shared<SqlParameter>("@f1", DataTypeEnum::adVarChar, "1111"));
		command->GetParameters().push_back(std::make_shared<SqlParameter>("@f2", DataTypeEnum::adVarChar, "2222"));
		command->GetParameters().push_back(std::make_shared<SqlParameter>("@f3", DataTypeEnum::adVarChar, "3333"));
		command->GetParameters().push_back(std::make_shared<SqlParameter>("@f4", DataTypeEnum::adVarChar, "4444"));
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
	DbTransactionPtr trans = nullptr;
	try
	{	
		//通过ODBC数据源形式的连接字符串
		//SqlConnectionPtr connection = std::make_shared<SqlConnection>("DSN=test");	
		//通过源始连接配置
		DbConnectionPtr connection = std::make_shared<SqlConnection>(MYSQL_CONNECTION_STRING);
		connection->Open();
		std::string connection_string = connection->GetConnectionString();
		std::cout << "connection string: " << connection_string << std::endl;
		std::string database = connection->GetDatabase();
		std::cout << "current database : " << database << std::endl;
		int connection_timeout = connection->GetConnectionTimeout();
		std::cout << "connect timeout: " << connection_timeout << std::endl;


		int rows = 0;
		DbCommandPtr command = connection->CreateCommand();

		command->SetCommandText("select * from account");
		std::string command_text = command->GetCommandText();
		std::cout << "command text: " << command_text << std::endl;
		CommandTypeEnum command_type = command->GetCommandType();
		int command_timeout = command->GetTimeout();
		std::cout << "command timeout: " << command_timeout << std::endl;

		DbDataReaderPtr reader = command->ExecuteReader();
		bool has = reader->HasRows();
		int fields = reader->FieldCount();
		while (reader->Read())
		{
			std::string username = reader->GetString("username");
			int balance = reader->GetInt("balance");
			std::cout << username << "\t" << balance << std::endl;
			username = reader->GetString(0);
			balance = reader->GetInt(1);
			std::cout << username << "\t" << balance << std::endl;
			reader->NextResult();
		}

		command = connection->CreateCommand();
		command->SetCommandText("update account set balance=2000 where username='james'");
		command_text = command->GetCommandText();
		std::cout << "command text: " << command_text << std::endl;
		rows = command->ExecuteNoQuery();
		std::cout << "update success affect rows: " << rows << std::endl;
		command = connection->CreateCommand();
		command->SetCommandText("select * from account");
		command_text = command->GetCommandText();
		std::cout << "command text: " << command_text << std::endl;
		reader = command->ExecuteReader();
		has = reader->HasRows();
		fields = reader->FieldCount();
		while (reader->Read())
		{
			std::string username = reader->GetString("username");
			int balance = reader->GetInt("balance");
			std::cout << username << "\t" << balance << std::endl;
			username = reader->GetString(0);
			balance = reader->GetInt(1);
			std::cout << username << "\t" << balance << std::endl;
			reader->NextResult();
		}
		command = connection->CreateCommand();
		command->SetCommandText("select count(*) from account");
		std::cout << "command text: " << command->GetCommandText();
		auto obj = command->ExecuteScalar();
		std::cout << "account total: " << obj.intVal << std::endl;

		command->SetCommandText("select * from account where username=?");
		command->GetParameters().push_back(std::make_shared<SqlParameter>("@username", "Tom"));
		reader = command->ExecuteReader();
		while (reader->Read())
		{
			std::string username = reader->GetString("username");
			int balance = reader->GetInt("balance");
			std::cout << username << "\t" << balance << std::endl;
			username = reader->GetString(0);
			balance = reader->GetInt(1);
			std::cout << username << "\t" << balance << std::endl;
			reader->NextResult();
		}
		trans = connection->BeginTransaction();
		command = connection->CreateCommand();
		command->SetCommandText("insert into account(username, balance) values(?, ?)");
		command->GetParameters().push_back(std::make_shared<SqlParameter>("@username", "bbb"));
		command->GetParameters().push_back(std::make_shared<SqlParameter>("@balance", 2000));
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
int main(int argc, char** argv)
{
	//TestMySql();
	TestSQLServer();
	getchar();
	return 1;
}