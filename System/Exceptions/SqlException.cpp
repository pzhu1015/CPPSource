///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Exceptions/SqlException.h"
namespace System
{
	namespace Exceptions
	{
		SqlException::SqlException()
			:
			Exception(ExceptionId::Sql)
		{
		}
		SqlException::SqlException(const _com_error & e) 
			:
			Exception(ExceptionId::Sql)
		{
			CString str = e.ErrorMessage();
			this->m_msg = (char*)e.Description();
		}
		SqlException::SqlException(const std::string & msg)
			:
			Exception(msg, ExceptionId::Sql)
		{
		}
		SqlException::~SqlException()
		{
		}
	}
}