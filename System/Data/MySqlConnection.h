///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_DATA_MYSQLCONNECTION_H
#define SYSTEM_DATA_MYSQLCONNECTION_H
//#include "System/stdafx.h"
#include "System/Base/DllExport.h"
#include "System/Data/DbConnection.h"

#include <Windows.h>
namespace System
{
	namespace Data
	{
		class SYSTEM_API MySqlConnection : public DbConnection
		{
		public:
			MySqlConnection(const std::string &connection_str);
			virtual ~MySqlConnection();
			virtual std::string GetConnectionString() override;
			virtual void SetConnectionString(const std::string &str) override;
			virtual int GetConnectionTimeout() override;
			virtual std::string GetDatabase() override;
			virtual void ChangeDatabase(const std::string &database) override;
			virtual ObjectStateEnum GetState() override;
			virtual bool Close() override;
			virtual bool Open() override;
			virtual DbTransactionPtr BeginTransaction() override;
			virtual DbTransactionPtr BeginTransaction(IsolationLevelEnum level) override;
			virtual DbCommandPtr CreateCommand() override;

			template <class T>
			typename std::enable_if<std::is_same<T, MySqlCommandPtr>::value, T>::type CreateCommand()
			{
				return std::make_shared<MySqlCommand>(std::dynamic_pointer_cast<MySqlConnection>(shared_from_this()));
			}

			const _ConnectionPtr& GetConnection() const;
		private:
			_ConnectionPtr m_connection;
		};
	}
}
#endif // !SYSTEM_DATA_MYSQLCONNECTION_H
