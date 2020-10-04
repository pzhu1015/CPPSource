///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_DATA_PTRS_H
#define SYSTEM_DATA_PTRS_H
#include <memory>
namespace System
{
	namespace Data
	{
		class DbConnection;
		class DbCommand;
		class DbTransaction;
		class DbDataReader;
		class DbDataParameter;
		class MySqlConnection;
		class MySqlTransaction;
		class MySqlCommand;
		typedef std::shared_ptr<DbConnection> DbConnectionPtr;
		typedef std::shared_ptr<DbCommand> DbCommandPtr;
		typedef std::shared_ptr<DbTransaction> DbTransactionPtr;
		typedef std::shared_ptr<DbDataReader> DbDataReaderPtr;
		typedef std::shared_ptr<DbDataParameter> DbDataParameterPtr;
		typedef std::shared_ptr<MySqlConnection> MySqlConnectionPtr;
		typedef std::shared_ptr<MySqlTransaction> MySqlTransactionPtr;
		typedef std::shared_ptr<MySqlCommand> MySqlCommandPtr;
	}
}
#endif // !SYSTEM_DATA_PTRS_H
