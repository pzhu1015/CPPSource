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
			assert(m_connection);
			return m_connection->GetConnection()->GetIsolationLevel();
		}

		bool SqlTransaction::Commit()
		{
			try
			{
				assert(m_connection);
				assert(m_connection->GetState() == ObjectStateEnum::adStateOpen);
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
				assert(m_connection);
				assert(m_connection->GetState() == ObjectStateEnum::adStateOpen);
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