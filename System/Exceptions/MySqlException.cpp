///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Exceptions/MySqlException.h"
namespace System
{
	namespace Exceptions
	{
		MySqlException::MySqlException()
			:
			Exception(ExceptionId::MySql)
		{
		}
		MySqlException::MySqlException(const _com_error & e) 
			:
			Exception(ExceptionId::MySql)
		{
			this->m_msg = (char*)e.Description();
		}
		MySqlException::MySqlException(const std::string & msg)
			:
			Exception(msg, ExceptionId::MySql)
		{
		}
		MySqlException::~MySqlException()
		{
		}
	}
}