///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_NOTSUPPORTEDEXCEPTION_H
#define SYSTEM_NOTSUPPORTEDEXCEPTION_H
#include "System/Exceptions/Exception.h"
namespace System
{
	namespace Exceptions
	{
		class SYSTEM_API NotSupportedException final : public Exception
		{
		public:
			NotSupportedException(const std::string & msg)
				:
				Exception(msg, TYPE_NAME)
			{
			}
		};
	}
}

#endif // !SYSTEM_NOTSUPPORTEDEXCEPTION_H
