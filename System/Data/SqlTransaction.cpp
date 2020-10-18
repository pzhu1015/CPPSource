///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Data/SqlTransaction.h"
#include "System/Data/DbConnection.h"
#include "System/Data/SqlConnection.h"
#include "System/Exceptions/SqlException.h"
#include "System/Exceptions/NullReferenceException.h"
#include "System/Exceptions/InvalidOperationException.h"
using namespace System::Exceptions;
namespace System
{
	namespace Data
	{
		SqlTransaction::SqlTransaction()
		{
		}

		SqlTransaction::SqlTransaction(const SqlConnectionPtr & connection)
		{
			m_connection = connection;
		}

		SqlTransaction::~SqlTransaction()
		{
			m_connection = nullptr;
		}

		DbConnectionPtr SqlTransaction::GetConnection()
		{
			return m_connection;
		}

		IsolationLevelEnum SqlTransaction::GetIsolationLevel()
		{
			if (m_connection == nullptr)
			{
				throw NullReferenceException("m_connection is nullptr");
			}
			return m_connection->GetConnection()->GetIsolationLevel();
		}

		bool SqlTransaction::Commit()
		{
			try
			{
				if (m_connection == nullptr)
				{
					throw NullReferenceException("m_connection is nullptr");
				}
				if (m_connection->GetState() != ObjectStateEnum::adStateOpen)
				{
					throw InvalidOperationException("connection not open");
				}
				HRESULT hr = m_connection->GetConnection()->CommitTrans();
				return !FAILED(hr);
			}
			catch (_com_error &e)
			{
				throw SqlException(e);
			}
			return false;
		}

		bool SqlTransaction::Rollback()
		{
			try
			{
				if (m_connection == nullptr)
				{
					throw NullReferenceException("m_connection is nullptr");
				}
				if (m_connection->GetState() != ObjectStateEnum::adStateOpen)
				{
					throw InvalidOperationException("connection not open");
				}
				HRESULT hr = m_connection->GetConnection()->RollbackTrans();
				return !FAILED(hr);
			}
			catch (_com_error &e)
			{
				throw SqlException(e);
			}
			return false;
		}
	}
}