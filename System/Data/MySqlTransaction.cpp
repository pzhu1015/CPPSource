///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Data/MySqlTransaction.h"
#include "System/Data/DbConnection.h"
#include "System/Data/MySqlConnection.h"
#include "System/Exceptions/MySqlException.h"
using namespace System::Exceptions;
namespace System
{
	namespace Data
	{
		MySqlTransaction::MySqlTransaction()
		{
		}

		MySqlTransaction::MySqlTransaction(const MySqlConnectionPtr & connection)
		{
			m_connection = connection;
		}

		MySqlTransaction::~MySqlTransaction()
		{
			m_connection = nullptr;
		}

		DbConnectionPtr MySqlTransaction::GetConnection()
		{
			return m_connection;
		}

		IsolationLevelEnum MySqlTransaction::GetIsolationLevel()
		{
			assert(m_connection);
			return m_connection->GetConnection()->GetIsolationLevel();
		}

		bool MySqlTransaction::Commit()
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
				throw MySqlException(e);
			}
			return false;
		}

		bool MySqlTransaction::Rollback()
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
				throw MySqlException(e);
			}
			return false;
		}
	}
}