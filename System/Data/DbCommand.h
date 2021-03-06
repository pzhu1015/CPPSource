///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_DATA_DBCOMMAND_H
#define SYSTEM_DATA_DBCOMMAND_H
#include "System/Data/ADO.h"
#include "System/Base/DllExport.h"
#include "System/Data/Ptrs.h"
#include <string>
#include <vector>
namespace System
{
	namespace Data
	{
		class SYSTEM_API DbCommand
		{
		public:
			virtual DbConnectionPtr GetConnection() = 0;
			virtual void SetConnection(const DbConnectionPtr &connection) = 0;
			virtual DbTransactionPtr GetTransaction() = 0;
			virtual void SetTransaction(const DbTransactionPtr &transaction) = 0;
			virtual std::string GetCommandText() = 0;
			virtual void SetCommandText(const std::string &command) = 0;
			virtual int GetTimeout() = 0;
			virtual void SetTimeout(int timeout) = 0;
			virtual CommandTypeEnum GetCommandType() = 0;
			virtual void SetCommandType(CommandTypeEnum type) = 0;
			virtual bool Prepare() = 0;
			virtual bool Cancel() = 0;
			virtual int ExecuteNoQuery() = 0;
			virtual _variant_t ExecuteScalar() = 0;
			virtual DbDataReaderPtr ExecuteDbDataReader() = 0;
			virtual DbParameterPtr CreateParameter() = 0;
			virtual DbParameterCollectionPtr GetDbParameterCollection() = 0;
			DbDataReaderPtr ExecuteReader()
			{
				return ExecuteDbDataReader();
			}
			DbParameterCollectionPtr GetParameters()
			{
				return GetDbParameterCollection();
			}
		};
	}
}
#endif // !SYSTEM_DATA_DBCOMMAND_H
