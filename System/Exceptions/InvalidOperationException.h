///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_INVALIDOPERATIONEXCEPTION_H
#define SYSTEM_INVALIDOPERATIONEXCEPTION_H
#include "System/Exceptions/Exception.h"
namespace System
{
	namespace Exceptions
	{
		class SYSTEM_API InvalidOperationException final : public Exception
		{
		public:
			InvalidOperationException();
			InvalidOperationException(const std::string &msg);
			virtual ~InvalidOperationException();
		};
	}
}

#endif // !SYSTEM_INVALIDOPERATIONEXCEPTION_H
