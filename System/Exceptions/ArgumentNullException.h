///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_ARGUMENTNULLEXCEPTION_H
#define SYSTEM_ARGUMENTNULLEXCEPTION_H
#include "System/Exceptions/Exception.h"
namespace System
{
	namespace Exceptions
	{
		class SYSTEM_API ArgumentNullException : public Exception
		{
		public:
			ArgumentNullException();
			ArgumentNullException(const std::string &msg);
			~ArgumentNullException();
		};
	}
}
#endif // !SYSTEM_ARGUMENTNULLEXCEPTION_H
