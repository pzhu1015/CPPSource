///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_EXCEPTIONS_MYSQLEXCEPTION_H
#define SYSTEM_EXCEPTIONS_MYSQLEXCEPTION_H
#include "System/Data/ADO.h"
#include "System/Exceptions/Exception.h"

namespace System
{
	namespace Exceptions
	{
		class SYSTEM_API MySqlException : public Exception
		{
		public:
			MySqlException();
			MySqlException(const _com_error &e);
			MySqlException(const std::string &msg);
			virtual ~MySqlException();
		};
	}
}
#endif // !SYSTEM_EXCEPTIONS_MYSQLEXCEPTION_H
