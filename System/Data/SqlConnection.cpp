///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Data/SqlConnection.h"
#include "System/Data/SqlTransaction.h"
#include "System/Data/SqlCommand.h"
#include "System/Exceptions/SqlException.h"
#include "System/Exceptions/NullReferenceException.h"
#include "System/Exceptions/InvalidOperationException.h"
using namespace System::Exceptions;
namespace System
{
	namespace Data
	{
		SqlConnection::SqlConnection(const std::string & connection_str)
		{	
			HRESULT hr = ::CoInitialize(NULL);
			if (FAILED(hr))
			{
				throw InvalidOperationException("CoInitialize failed");
			}
			hr = m_connection.CreateInstance(__uuidof(Connection));
			if (FAILED(hr))
			{
				throw InvalidOperationException("m_connection.CreateInstance() failed");
			}
			if (m_connection == nullptr)
			{
				throw NullReferenceException("m_connection is nullptr");
			}
			m_connection->PutConnectionString(connection_str.data());
			m_connection->PutCursorLocation(CursorLocationEnum::adUseClient);
		}

		SqlConnection::~SqlConnection()
		{
			Close();
		}

		std::string SqlConnection::GetConnectionString()
		{
			if (m_connection == nullptr)
			{
				throw NullReferenceException("m_connection is nullptr");
			}
			return (char*)m_connection->GetConnectionString();
		}

		void SqlConnection::SetConnectionString(const std::string & str)
		{
			if (m_connection == nullptr)
			{
				throw NullReferenceException("m_connection is nullptr");
			}
			m_connection->PutConnectionString(str.data());
		}

		int SqlConnection::GetConnectionTimeout()
		{
			if (m_connection == nullptr)
			{
				throw NullReferenceException("m_connection is nullptr");
			}
			return m_connection->GetConnectionTimeout();
		}

		std::string SqlConnection::GetDatabase()
		{
			if (m_connection == nullptr)
			{
				throw NullReferenceException("m_connection is nullptr");
			}
			return (char*)m_connection->GetDefaultDatabase();
		}

		void SqlConnection::ChangeDatabase(const std::string & database)
		{
			if (m_connection == nullptr)
			{
				throw NullReferenceException("m_connection is nullptr");
			}
			m_connection->PutDefaultDatabase(database.data());
		}

		ObjectStateEnum SqlConnection::GetState()
		{
			if (m_connection == nullptr)
			{
				throw NullReferenceException("m_connection is nullptr");
			}
			return (ObjectStateEnum)m_connection->GetState();
		}

		bool SqlConnection::Close()
		{
			try
			{
				if (m_connection)
				{
					if (GetState() == ObjectStateEnum::adStateOpen)
					{
						HRESULT hr = m_connection->Close();
						if (FAILED(hr)) return false;
						::CoUninitialize();
						return true;
					}
				}
			}
			catch (_com_error &e)
			{
				throw SqlException(e);
			}
			return false;
		}

		bool SqlConnection::Open()
		{
			try
			{
				if (m_connection == nullptr)
				{
					throw NullReferenceException("m_connection is nullptr");
				}
				HRESULT hr = m_connection->Open(GetConnectionString().data(), "", "", 0);
				return !FAILED(hr);
			}
			catch (_com_error &e)
			{
				throw SqlException(e);
			}
			return false;
		}

		DbTransactionPtr SqlConnection::BeginTransaction()
		{
			return BeginTransaction(IsolationLevelEnum::adXactReadCommitted);
		}

		DbTransactionPtr SqlConnection::BeginTransaction(IsolationLevelEnum level)
		{
			try
			{
				if (m_connection == nullptr)
				{
					throw NullReferenceException("m_connection is nullptr");
				}
				if (GetState() == ObjectStateEnum::adStateOpen)
				{
					throw InvalidOperationException("m_connection is not open");
				}
				m_connection->PutIsolationLevel(level);
				DbTransactionPtr trans = std::make_shared<SqlTransaction>(std::dynamic_pointer_cast<SqlConnection>(shared_from_this()));
				HRESULT hr = m_connection->BeginTrans();
				if (FAILED(hr)) return nullptr;
				return trans;
			}
			catch (_com_error &e)
			{
				throw SqlException(e);
			}
			return nullptr;
		}

		DbCommandPtr SqlConnection::CreateCommand()
		{
			return std::make_shared<SqlCommand>(std::dynamic_pointer_cast<SqlConnection>(shared_from_this()));
		}

		const _ConnectionPtr & SqlConnection::GetConnection() const
		{
			return m_connection;
		}
	}
}