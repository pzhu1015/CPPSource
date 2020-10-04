///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Data/MySqlConnection.h"
#include "System/Data/MySqlTransaction.h"
#include "System/Data/MySqlCommand.h"
#include "System/Exceptions/MySqlException.h"
using namespace System::Exceptions;
namespace System
{
	namespace Data
	{
		MySqlConnection::MySqlConnection(const std::string & connection_str)
		{	
			HRESULT hr = ::CoInitialize(NULL);
			assert(!FAILED(hr));
			hr = m_connection.CreateInstance(__uuidof(Connection));
			assert(!FAILED(hr));
			m_connection->PutConnectionString(connection_str.data());
		}

		MySqlConnection::~MySqlConnection()
		{
			Close();
		}

		std::string MySqlConnection::GetConnectionString()
		{
			assert(m_connection);
			return (char*)m_connection->GetConnectionString();
		}

		void MySqlConnection::SetConnectionString(const std::string & str)
		{
			assert(m_connection);
			m_connection->PutConnectionString(str.data());
		}

		int MySqlConnection::GetConnectionTimeout()
		{
			assert(m_connection);
			return m_connection->GetConnectionTimeout();
		}

		std::string MySqlConnection::GetDatabase()
		{
			assert(m_connection);
			return (char*)m_connection->GetDefaultDatabase();
		}

		void MySqlConnection::ChangeDatabase(const std::string & database)
		{
			assert(m_connection);
			m_connection->PutDefaultDatabase(database.data());
		}

		ObjectStateEnum MySqlConnection::GetState()
		{
			assert(m_connection);
			return (ObjectStateEnum)m_connection->GetState();
		}

		bool MySqlConnection::Close()
		{
			try
			{
				if (m_connection)
				{
					assert(m_connection);
					HRESULT hr = m_connection->Close();
					if (FAILED(hr)) return false;
					::CoUninitialize();
					return true;
				}
			}
			catch (_com_error &e)
			{
				throw MySqlException(e);
			}
			return false;
		}

		bool MySqlConnection::Open()
		{
			try
			{
				assert(m_connection);
				HRESULT hr = m_connection->Open(GetConnectionString().data(), "", "", 0);
				if (FAILED(hr)) return false;

				return true;
			}
			catch (_com_error &e)
			{
				throw MySqlException(e);
			}
			return false;
		}

		DbTransactionPtr MySqlConnection::BeginTransaction()
		{
			return BeginTransaction(IsolationLevelEnum::adXactUnspecified);
		}

		DbTransactionPtr MySqlConnection::BeginTransaction(IsolationLevelEnum level)
		{
			try
			{
				assert(m_connection);
				assert(GetState() == ObjectStateEnum::adStateOpen);
				m_connection->PutIsolationLevel(level);
				DbTransactionPtr trans = std::make_shared<MySqlTransaction>(std::dynamic_pointer_cast<MySqlConnection>(shared_from_this()));
				HRESULT hr = m_connection->BeginTrans();
				if (FAILED(hr)) return nullptr;
				return trans;
			}
			catch (_com_error &e)
			{
				throw MySqlException(e);
			}
			return nullptr;
		}

		DbCommandPtr MySqlConnection::CreateCommand()
		{
			return std::make_shared<MySqlCommand>(std::dynamic_pointer_cast<MySqlConnection>(shared_from_this()));
		}

		const _ConnectionPtr & MySqlConnection::GetConnection() const
		{
			return m_connection;
		}
	}
}