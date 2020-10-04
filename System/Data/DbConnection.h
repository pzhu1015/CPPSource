///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_DATA_DBCONNECTION_H
#define SYSTEM_DATA_DBCONNECTION_H
#include "System/Data/ADO.h"
#include "System/Base/DllExport.h"
#include "System/Data/Ptrs.h"
#include "System/Data/StateChangeEventArgs.h"

#define CONNECTION_TIMEOUT 60
namespace System
{
	namespace Data
	{
		class SYSTEM_API DbConnection : public std::enable_shared_from_this<DbConnection>
		{
		public:
			virtual std::string GetConnectionString() = 0;
			virtual void SetConnectionString(const std::string &str) = 0;
			virtual int GetConnectionTimeout() = 0;
			virtual std::string GetDatabase() = 0;
			virtual void ChangeDatabase(const std::string &database) = 0;
			virtual ObjectStateEnum GetState() = 0;
			virtual bool Close() = 0;
			virtual bool Open() = 0;
			virtual DbTransactionPtr BeginTransaction() = 0;
			virtual DbTransactionPtr BeginTransaction(IsolationLevelEnum level) = 0;
			virtual DbCommandPtr CreateCommand() = 0;
		public:
			StateChangeEventHandler StateChange;
		protected:
			virtual void OnStateChange(StateChangeEventArgs e);
		};
	}
}
#endif // !SYSTEM_DATA_DBCONNECTION_H