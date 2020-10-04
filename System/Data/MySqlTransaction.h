///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_DATA_MYSQLTRANSACTION_H
#define SYSTEM_DATA_MYSQLTRANSACTION_H
#include "System/Data/DbTransaction.h"

namespace System
{
	namespace Data
	{
		class SYSTEM_API MySqlTransaction : public DbTransaction
		{
		public:
			MySqlTransaction();
			MySqlTransaction(const MySqlConnectionPtr &connection);
			virtual ~MySqlTransaction();
			virtual DbConnectionPtr GetConnection() override;
			virtual IsolationLevelEnum GetIsolationLevel() override;
			virtual bool Commit() override;
			virtual bool Rollback() override;
		private:
			MySqlConnectionPtr m_connection;
		};
	}
}
#endif // !SYSTEM_DATA_MYSQLDBTRANSACTION_H
