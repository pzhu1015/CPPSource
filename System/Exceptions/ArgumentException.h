///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_EXCEPTIONS_ARGUMENTEXCEPTION_H
#define SYSTEM_EXCEPTIONS_ARGUMENTEXCEPTION_H
#include "System/Exceptions/Exception.h"
namespace System
{
	namespace Exceptions
	{
		class SYSTEM_API ArgumentException final : public Exception
		{
		public:
			ArgumentException(const std::string & msg)
				:
				Exception(msg, TYPE_NAME)
			{
			}
		};
	}
}

#endif // !SYSTEM_EXCEPTIONS_ARGUMENTEXCEPTION_H
