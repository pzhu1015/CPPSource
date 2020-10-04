///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Data/MySqlCommand.h"
#include "System/Data/DbConnection.h"
#include "System/Data/DbTransaction.h"
#include "System/Data/MySqlConnection.h"
#include "System/Data/MySqlTransaction.h"
#include "System/Data/MySqlDataReader.h"
#include "System/Data/MySqlParameter.h"
#include "System/Exceptions/MySqlException.h"
#include "System/Base/Object.h"
using namespace System::Exceptions;
namespace System
{
	namespace Data
	{
		MySqlCommand::MySqlCommand()
		{
			m_command.CreateInstance(__uuidof(Command));
			assert(m_command);
			m_command->PutCommandType(CommandTypeEnum::adCmdUnspecified);
		}

		MySqlCommand::MySqlCommand(const MySqlConnectionPtr & connection)
		{
			m_command.CreateInstance(__uuidof(Command));
			assert(m_command);
			m_command->ActiveConnection = connection->GetConnection();
			m_command->PutCommandType(CommandTypeEnum::adCmdText);
			m_connection = connection;
		}

		MySqlCommand::MySqlCommand(const std::string & command_text, const MySqlConnectionPtr & connection)
		{
			m_command.CreateInstance(__uuidof(Command));
			assert(m_command);
			m_command->ActiveConnection = connection->GetConnection();
			m_command->PutCommandType(CommandTypeEnum::adCmdText);
			m_command->PutCommandText(command_text.data());
			m_connection = connection;
		}

		MySqlCommand::~MySqlCommand()
		{
			m_connection = nullptr;
			m_transaction = nullptr;
		}

		DbConnectionPtr MySqlCommand::GetConnection()
		{
			return m_connection;
		}

		void MySqlCommand::SetConnection(const DbConnectionPtr & connection)
		{
			m_connection = std::dynamic_pointer_cast<MySqlConnection>(connection);
			assert(m_command);
			m_command->ActiveConnection = m_connection->GetConnection();
		}

		DbTransactionPtr MySqlCommand::GetTransaction()
		{
			return m_transaction;
		}

		void MySqlCommand::SetTransaction(const DbTransactionPtr & transaction)
		{
			m_transaction = std::dynamic_pointer_cast<MySqlTransaction>(transaction);
		}

		std::string MySqlCommand::GetCommandText()
		{
			assert(m_command);
			return (char*)m_command->GetCommandText();
		}

		void MySqlCommand::SetCommandText(const std::string & command)
		{
			assert(m_command);
			m_command->PutCommandText(command.data());
		}

		int MySqlCommand::GetTimeout()
		{
			assert(m_command);
			return m_command->GetCommandTimeout();
		}

		void MySqlCommand::SetTimeout(int timeout)
		{
			assert(m_command);
			m_command->PutCommandTimeout(timeout);
		}

		CommandTypeEnum MySqlCommand::GetCommandType()
		{
			assert(m_command);
			return m_command->GetCommandType();
		}

		void MySqlCommand::SetCommandType(CommandTypeEnum type)
		{
			assert(m_command);
			m_command->PutCommandType(type);
		}

		bool MySqlCommand::Prepare()
		{
			try
			{
				//TODO: Prepare()
				return true;
			}
			catch (_com_error &e)
			{
				throw MySqlException(e);
			}
			return false;
		}

		bool MySqlCommand::Cancel()
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
				throw MySqlException(e);
			}
			return false;
		}

		int MySqlCommand::ExecuteNoQuery()
		{
			try
			{
				assert(m_connection->GetState() == ObjectStateEnum::adStateOpen);
				assert(m_command);
				_variant_t rows;
				m_command->Execute(&rows, nullptr, GetCommandType());
				return rows.intVal;
			}
			catch (_com_error &e)
			{
				throw MySqlException(e);
			}
			return -1;
		}

		_variant_t MySqlCommand::ExecuteScalar()
		{
			try
			{
				_variant_t var;
				var.vt = VARENUM::VT_EMPTY;
				assert(m_connection->GetState() == ObjectStateEnum::adStateOpen);
				assert(m_command);
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
				throw MySqlException(e);
			}
			return _variant_t();
		}

		DbDataReaderPtr MySqlCommand::ExecuteReader()
		{
			try
			{
				assert(m_connection->GetState() == ObjectStateEnum::adStateOpen);
				assert(m_command);
				for (auto &item : m_parameters)
				{
					auto mysql_param = std::dynamic_pointer_cast<MySqlParameter>(item);
					m_command->Parameters->Append(mysql_param->GetParameter());
				}
				_variant_t rows;
				_RecordsetPtr record = m_command->Execute(&rows, nullptr, GetCommandType());
				if (!record) return nullptr;
				return std::make_shared<MySqlDataReader>(record);
			}
			catch (_com_error &e)
			{
				throw MySqlException(e);
			}
			return nullptr;
		}

		DbDataParameterPtr MySqlCommand::CreateParameter()
		{
			_ParameterPtr param = MySqlParameter::CreateParameter("");
			return std::make_shared<MySqlParameter>(param);
		}

		std::vector<DbDataParameterPtr>& MySqlCommand::GetParameters()
		{
			return m_parameters;
		}

		void MySqlCommand::SetParameters(const std::vector<DbDataParameterPtr>& params)
		{
			m_parameters = params;
			
		}
	}
}