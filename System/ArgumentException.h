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
#include "System/Exception.h"
namespace System
{
	class SYSTEM_API ArgumentException : public Exception
	{
	public:
		ArgumentException();
		ArgumentException(const std::string &msg);
		virtual ~ArgumentException();
	};
}

#endif // !SYSTEM_EXCEPTIONS_ARGUMENTEXCEPTION_H
