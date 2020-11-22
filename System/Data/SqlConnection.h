///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_DATA_SQLCONNECTION_H
#define SYSTEM_DATA_SQLCONNECTION_H
//#include "System/stdafx.h"
#include "System/Base/DllExport.h"
#include "System/Data/DbConnection.h"

#include <Windows.h>
namespace System
{
	namespace Data
	{
		class SYSTEM_API SqlConnection : public DbConnection, public std::enable_shared_from_this<SqlConnection>
		{
		public:
			SqlConnection(const std::string &connection_str);
			virtual ~SqlConnection();
			virtual std::string GetConnectionString() override;
			virtual void SetConnectionString(const std::string &str) override;
			virtual int GetConnectionTimeout() override;
			virtual std::string GetDatabase() override;
			virtual void ChangeDatabase(const std::string &database) override;
			virtual ObjectStateEnum GetState() override;
			virtual bool Close() override;
			virtual bool Open() override;
			virtual DbTransactionPtr BeginDbTransaction(IsolationLevelEnum level) override;
			virtual DbCommandPtr CreateDbCommand() override;
			SqlTransactionPtr BeginTransaction();
			SqlTransactionPtr BeginTransaction(IsolationLevelEnum level);
			SqlCommandPtr CreateCommand();
			const _ConnectionPtr& GetConnection() const;
		private:
			_ConnectionPtr m_connection;
		};
	}
}
#endif // !SYSTEM_DATA_SQLCONNECTION_H
