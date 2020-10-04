///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Data/MySqlConnection.h"
#include "System/Data/MySqlCommand.h"
#include "System/Data/MySqlDataReader.h"
#include "System/Exceptions/MySqlException.h"
#include "System/Data/MySqlParameter.h"
#include "System/Base/Object.h"
#include "System/Base/Ptrs.h"
#include <iostream>
using namespace System;
using namespace System::Data;
using namespace System::Exceptions;
int main(int argc, char** argv)
{
	try
	{
		//通过ODBC数据源形式的连接字符串
		//MySqlConnectionPtr connection = std::make_shared<MySqlConnection>("DSN=test");	
		//通过源始连接配置
		MySqlConnectionPtr connection = std::make_shared<MySqlConnection>("Provider = MSDASQL.1; Persist Security Info = True; Extended Properties = 'Driver=MySQL ODBC 8.0 Unicode Driver;SERVER=192.168.1.10;UID=root;PWD=12345;DATABASE=bigdata;PORT=3306'");
		connection->Open();
		std::string connection_string = connection->GetConnectionString();
		std::cout << "connection string: " << connection_string << std::endl;
		std::string database = connection->GetDatabase();
		std::cout << "current database : " << database << std::endl;
		int connection_timeout = connection->GetConnectionTimeout();
		std::cout << "connect timeout: " << connection_timeout << std::endl;

		
		int rows = 0;
		MySqlCommandPtr command = connection->CreateCommand<MySqlCommandPtr>();
		/*command->SetCommandText("insert into account(username, balance) values('ketty', 1000)");
		rows = command->ExecuteNoQuery();
		std::cout << "insert success affect rows: " << rows << std::endl;*/

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
			std::cout << "username: " << username << ", balance: " << balance << std::endl;
			std::string username_index = reader->GetString(0);
			int balance_index = reader->GetInt(1);
			std::cout << "username: " << username_index << ", balance: " << balance_index << std::endl;
			reader->NextResult();
		}

		command->SetCommandText("update account set balance=2000 where username='james'");
		command_text = command->GetCommandText();
		std::cout << "command text: " << command_text << std::endl;
		rows = command->ExecuteNoQuery();
		std::cout << "update success affect rows: " << rows << std::endl;
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
			std::cout << "username: " << username << ", balance: " << balance << std::endl;

			std::string username_index = reader->GetString(0);
			int balance_index = reader->GetInt(1);
			std::cout << "username: " << username_index << ", balance: " << balance_index << std::endl;
			reader->NextResult();
		}
		command->SetCommandText("select count(*) from account");
		std::cout << "command text: " << command->GetCommandText();
		auto obj = command->ExecuteScalar();
		std::cout << "account total: " << obj.intVal << std::endl;

		command->SetCommandText("select * from account where username=?");
		command->GetParameters().push_back(std::make_shared<MySqlParameter>("@username", "Tom"));
		reader = command->ExecuteReader();
		while (reader->Read())
		{
			std::string username = reader->GetString("username");
			int balance = reader->GetInt("balance");
			std::cout << "username: " << username << ", balance: " << balance << std::endl;

			std::string username_index = reader->GetString(0);
			int balance_index = reader->GetInt(1);
			std::cout << "username: " << username_index << ", balance: " << balance_index << std::endl;
			reader->NextResult();
		}
	}
	catch (MySqlException &ex)
	{
		std::cout << ex.what() << std::endl;
	}
	getchar();
	return 1;
}