///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_EXCEPTIONS_SQLEXCEPTION_H
#define SYSTEM_EXCEPTIONS_SQLEXCEPTION_H
#include "System/Data/ADO.h"
#include "System/Exceptions/Exception.h"

namespace System
{
	namespace Exceptions
	{
		class SYSTEM_API SqlException : public Exception
		{
		public:
			SqlException();
			SqlException(const _com_error &e);
			SqlException(const std::string &msg);
			virtual ~SqlException();
		};
	}
}
#endif // !SYSTEM_EXCEPTIONS_SQLEXCEPTION_H
