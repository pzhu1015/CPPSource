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
		class SYSTEM_API DbConnection
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
			virtual DbTransactionPtr BeginDbTransaction(IsolationLevelEnum level) = 0;
			virtual DbCommandPtr CreateDbCommand() = 0;
			DbTransactionPtr BeginTransaction()
			{
				return BeginDbTransaction(IsolationLevelEnum::adXactReadCommitted);
			}
			DbTransactionPtr BeginTransaction(IsolationLevelEnum level)
			{
				return BeginDbTransaction(level);
			}
			DbCommandPtr CreateCommand()
			{
				return CreateDbCommand();
			}
		public:
			StateChangeEventHandler StateChange;
		protected:
			virtual void OnStateChange(StateChangeEventArgs e)
			{
				if (StateChange != nullptr)
				{
					this->StateChange(e);
				}
			}
		};
	}
}
#endif // !SYSTEM_DATA_DBCONNECTION_H
