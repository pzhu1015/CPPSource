///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_DATA_SQLTRANSACTION_H
#define SYSTEM_DATA_SQLTRANSACTION_H
#include "System/Data/DbTransaction.h"

namespace System
{
	namespace Data
	{
		class SYSTEM_API SqlTransaction : public DbTransaction
		{
		public:
			SqlTransaction();
			SqlTransaction(const SqlConnectionPtr &connection);
			virtual ~SqlTransaction();
			virtual DbConnectionPtr GetConnection() override;
			virtual IsolationLevelEnum GetIsolationLevel() override;
			virtual bool Commit() override;
			virtual bool Rollback() override;
		private:
			SqlConnectionPtr m_connection;
		};
	}
}
#endif // !SYSTEM_DATA_SQLDBTRANSACTION_H
