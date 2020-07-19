///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_SOCKETEXCEPTION_H
#define SYSTEM_SOCKETEXCEPTION_H
#include "System/Exception.h"
namespace System
{
	class SYSTEM_API SocketException : public Exception
	{
	public:
		SocketException();
		SocketException(const std::string &msg);
		virtual ~SocketException();
	};
}
#endif // !SYSTEM_SOCKETEXCEPTION_H
