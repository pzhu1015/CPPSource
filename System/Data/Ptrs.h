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
		class SqlConnection;
		class SqlTransaction;
		class SqlCommand;
		class SqlDataReader;
		typedef std::shared_ptr<DbConnection> DbConnectionPtr;
		typedef std::shared_ptr<DbCommand> DbCommandPtr;
		typedef std::shared_ptr<DbTransaction> DbTransactionPtr;
		typedef std::shared_ptr<DbDataReader> DbDataReaderPtr;
		typedef std::shared_ptr<DbDataParameter> DbDataParameterPtr;
		typedef std::shared_ptr<SqlConnection> SqlConnectionPtr;
		typedef std::shared_ptr<SqlTransaction> SqlTransactionPtr;
		typedef std::shared_ptr<SqlCommand> SqlCommandPtr;
		typedef std::shared_ptr<SqlDataReader> SqlDataReaderPtr;
	}
}
#endif // !SYSTEM_DATA_PTRS_H
