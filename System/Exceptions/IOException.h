///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_IOEXCEPTION_H
#define SYSTEM_IOEXCEPTION_H
#include "System/Exceptions/Exception.h"
namespace System
{
	namespace Exceptions
	{
		class SYSTEM_API IOException final : public Exception
		{
		public:
			IOException(const std::string & msg)
				:
				Exception(msg, TYPE_NAME)
			{
			}
		};
	}
}

#endif // !SYSTEM_IOEXCEPTION_H
