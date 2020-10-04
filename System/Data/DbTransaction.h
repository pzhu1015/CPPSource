///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_DATA_DBTRANSACTION_H
#define SYSTEM_DATA_DBTRANSACTION_H
#include "System/Data/ADO.h"
#include "System/Base/DllExport.h"
#include "System/Data/Ptrs.h"
namespace System
{
	namespace Data
	{
		class SYSTEM_API DbTransaction
		{
		public:
			virtual DbConnectionPtr GetConnection() = 0;
			virtual IsolationLevelEnum GetIsolationLevel() = 0;
			virtual bool Commit() = 0;
			virtual bool Rollback() = 0;
		};
	}
}
#endif // !SYSTEM_DATA_DBTRANSACTION_H
