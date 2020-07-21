///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Exceptions/SocketException.h"
namespace System
{
	namespace Exceptions
	{
		SocketException::SocketException()
			:
			Exception(ExceptionId::Socket)
		{
		}

		SocketException::SocketException(const std::string & msg)
			:
			Exception(msg, ExceptionId::Socket)
		{
		}

		SocketException::~SocketException()
		{
		}
	}
}