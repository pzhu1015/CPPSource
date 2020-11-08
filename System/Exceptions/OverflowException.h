///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_OVERFLOWEXCEPTION_H
#define SYSTEM_OVERFLOWEXCEPTION_H
#include "System/Exceptions/Exception.h"
namespace System
{
	namespace Exceptions
	{
		class SYSTEM_API OverflowException final : public Exception
		{
		public:
			OverflowException(const std::string & msg)
				:
				Exception(msg, TYPE_NAME)
			{
			}
		};
	}
}

#endif // !SYSTEM_OVERFLOWEXCEPTION_H
