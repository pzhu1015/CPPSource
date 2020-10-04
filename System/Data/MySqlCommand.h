///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_DATA_MYSQLCOMMAND_H
#define SYSTEM_DATA_MYSQLCOMMAND_H
#include "System/Data/DbCommand.h"
#include "System/Data/Ptrs.h"

namespace System
{
	namespace Data
	{
		class SYSTEM_API MySqlCommand : public DbCommand, public std::enable_shared_from_this<MySqlCommand>
		{
		public:
			MySqlCommand();
			MySqlCommand(const MySqlConnectionPtr &connection);
			MySqlCommand(const std::string &command_text, const MySqlConnectionPtr &connection);
			virtual ~MySqlCommand();

			virtual DbConnectionPtr GetConnection() override;
			virtual void SetConnection(const DbConnectionPtr &connection) override;
			virtual DbTransactionPtr GetTransaction() override;
			virtual void SetTransaction(const DbTransactionPtr &transaction) override;
			virtual std::string GetCommandText() override;
			virtual void SetCommandText(const std::string &command) override;
			virtual int GetTimeout() override;
			virtual void SetTimeout(int timeout) override;
			virtual CommandTypeEnum GetCommandType() override;
			virtual void SetCommandType(CommandTypeEnum type) override;
			virtual bool Prepare() override;
			virtual bool Cancel() override;
			virtual int ExecuteNoQuery() override;
			virtual _variant_t ExecuteScalar() override;
			virtual DbDataReaderPtr ExecuteReader() override;
			virtual DbDataParameterPtr CreateParameter() override;
			virtual std::vector<DbDataParameterPtr>& GetParameters();
			virtual void SetParameters(const std::vector<DbDataParameterPtr> &params);
		private:
			MySqlConnectionPtr m_connection;
			MySqlTransactionPtr m_transaction;
			std::vector<DbDataParameterPtr> m_parameters;
			_CommandPtr m_command;
		};
	}
}
#endif // !SYSTEM_DATA_MYSQLCOMMAND_H
