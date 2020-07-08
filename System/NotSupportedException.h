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
#include "System/Exception.h"
namespace System
{
	class SYSTEM_API NotSupportedException : public Exception
	{
	public:
		NotSupportedException();
		NotSupportedException(const std::string &msg);
		virtual ~NotSupportedException();
	};
}

#endif // !SYSTEM_NOTSUPPORTEDEXCEPTION_H
