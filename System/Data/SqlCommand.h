///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_DATA_SQLCOMMAND_H
#define SYSTEM_DATA_SQLCOMMAND_H
#include "System/Data/DbCommand.h"
#include "System/Data/Ptrs.h"

namespace System
{
	namespace Data
	{
		class SYSTEM_API SqlCommand : public DbCommand, public std::enable_shared_from_this<SqlCommand>
		{
		public:
			SqlCommand();
			SqlCommand(const SqlConnectionPtr &connection);
			SqlCommand(const std::string &command_text, const SqlConnectionPtr &connection);
			virtual ~SqlCommand();

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
			virtual DbDataReaderPtr ExecuteDbDataReader() override;
			virtual DbParameterPtr CreateParameter() override;
			virtual DbParameterCollectionPtr GetDbParameterCollection() override;
			SqlDataReaderPtr ExecuteReader();
			SqlParameterCollectionPtr& GetParameters();
		private:
			void AppendParameters();
		private:
			SqlConnectionPtr m_connection;
			SqlTransactionPtr m_transaction;
			SqlParameterCollectionPtr m_parameters;
			_CommandPtr m_command;
		};
	}
}
#endif // !SYSTEM_DATA_SQLCOMMAND_H
