///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Data/SqlCommand.h"
#include "System/Data/DbConnection.h"
#include "System/Data/DbTransaction.h"
#include "System/Data/SqlConnection.h"
#include "System/Data/SqlTransaction.h"
#include "System/Data/SqlDataReader.h"
#include "System/Data/SqlParameter.h"
#include "System/Exceptions/SqlException.h"
#include "System/Base/Object.h"
using namespace System::Exceptions;
namespace System
{
	namespace Data
	{
		SqlCommand::SqlCommand()
		{
			m_command.CreateInstance(__uuidof(Command));
			assert(m_command);
			m_command->PutCommandType(CommandTypeEnum::adCmdUnspecified);
		}

		SqlCommand::SqlCommand(const SqlConnectionPtr & connection)
		{
			m_command.CreateInstance(__uuidof(Command));
			assert(m_command);
			m_command->ActiveConnection = connection->GetConnection();
			m_command->PutCommandType(CommandTypeEnum::adCmdText);
			m_connection = connection;
		}

		SqlCommand::SqlCommand(const std::string & command_text, const SqlConnectionPtr & connection)
		{
			m_command.CreateInstance(__uuidof(Command));
			assert(m_command);
			m_command->ActiveConnection = connection->GetConnection();
			m_command->PutCommandType(CommandTypeEnum::adCmdText);
			m_command->PutCommandText(command_text.data());
			m_connection = connection;
		}

		SqlCommand::~SqlCommand()
		{
			m_connection = nullptr;
			m_transaction = nullptr;
		}

		DbConnectionPtr SqlCommand::GetConnection()
		{
			return m_connection;
		}

		void SqlCommand::SetConnection(const DbConnectionPtr & connection)
		{
			m_connection = std::dynamic_pointer_cast<SqlConnection>(connection);
			assert(m_command);
			m_command->ActiveConnection = m_connection->GetConnection();
		}

		DbTransactionPtr SqlCommand::GetTransaction()
		{
			return m_transaction;
		}

		void SqlCommand::SetTransaction(const DbTransactionPtr & transaction)
		{
			m_transaction = std::dynamic_pointer_cast<SqlTransaction>(transaction);
		}

		std::string SqlCommand::GetCommandText()
		{
			assert(m_command);
			return (char*)m_command->GetCommandText();
		}

		void SqlCommand::SetCommandText(const std::string & command)
		{
			assert(m_command);
			m_command->PutCommandText(command.data());
		}

		int SqlCommand::GetTimeout()
		{
			assert(m_command);
			return m_command->GetCommandTimeout();
		}

		void SqlCommand::SetTimeout(int timeout)
		{
			assert(m_command);
			m_command->PutCommandTimeout(timeout);
		}

		CommandTypeEnum SqlCommand::GetCommandType()
		{
			assert(m_command);
			return m_command->GetCommandType();
		}

		void SqlCommand::SetCommandType(CommandTypeEnum type)
		{
			assert(m_command);
			m_command->PutCommandType(type);
		}

		bool SqlCommand::Prepare()
		{
			try
			{
				//TODO: Prepare()
				return true;
			}
			catch (_com_error &e)
			{
				throw SqlException(e);
			}
			return false;
		}

		bool SqlCommand::Cancel()
		{
			try
			{
				assert(m_command);
				HRESULT hr = m_command->Cancel();
				if (FAILED(hr)) return false;
				return true;
			}
			catch (_com_error &e)
			{
				throw SqlException(e);
			}
			return false;
		}

		int SqlCommand::ExecuteNoQuery()
		{
			try
			{
				assert(m_connection->GetState() == ObjectStateEnum::adStateOpen);
				assert(m_command);
				AppendParameters();
				_variant_t rows;
				m_command->Execute(&rows, nullptr, GetCommandType());
				return rows.intVal;
			}
			catch (_com_error &e)
			{
				throw SqlException(e);
			}
			return -1;
		}

		_variant_t SqlCommand::ExecuteScalar()
		{
			try
			{
				_variant_t var;
				var.vt = VARENUM::VT_EMPTY;
				assert(m_connection->GetState() == ObjectStateEnum::adStateOpen);
				assert(m_command);
				AppendParameters();
				_variant_t rows;
				_RecordsetPtr record = m_command->Execute(&rows, nullptr, GetCommandType());
				if (!record) return var;
				if (!record->GetadoEOF())
				{
					var = record->GetCollect(long(0));
				}
				return var;
			}
			catch (_com_error &e)
			{
				throw SqlException(e);
			}
			return _variant_t();
		}

		DbDataReaderPtr SqlCommand::ExecuteReader()
		{
			try
			{
				assert(m_connection->GetState() == ObjectStateEnum::adStateOpen);
				assert(m_command);
				AppendParameters();
				_variant_t rows;
				_RecordsetPtr record = m_command->Execute(&rows, nullptr, GetCommandType());
				if (!record) return nullptr;
				return std::make_shared<SqlDataReader>(record);
			}
			catch (_com_error &e)
			{
				throw SqlException(e);
			}
			return nullptr;
		}

		DbDataParameterPtr SqlCommand::CreateParameter()
		{
			_ParameterPtr param = SqlParameter::CreateParameter("", _variant_t(), ParameterDirectionEnum::adParamInput);
			return std::make_shared<SqlParameter>(param);
		}

		DbDataParameterPtr SqlCommand::CreateParameter(const std::string & name, DataTypeEnum type, const _variant_t & value, ParameterDirectionEnum direction)
		{
			_ParameterPtr param = SqlParameter::CreateParameter(name, type, value, direction);
			return std::make_shared<SqlParameter>(param);
		}

		std::vector<DbDataParameterPtr>& SqlCommand::GetParameters()
		{
			return m_parameters;
		}

		void SqlCommand::SetParameters(const std::vector<DbDataParameterPtr>& params)
		{
			m_parameters = params;	
		}
		void SqlCommand::AppendParameters()
		{
			for (auto &item : m_parameters)
			{
				auto param = std::dynamic_pointer_cast<SqlParameter>(item);
				m_command->Parameters->Append(param->GetParameter());
			}
		}
	}
}