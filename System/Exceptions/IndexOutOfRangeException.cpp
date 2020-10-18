///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Exceptions/IndexOutOfRangeException.h"
namespace System
{
	namespace Exceptions
	{
		IndexOutOfRangeException::IndexOutOfRangeException()
			:
			Exception(ExceptionId::IndexOutOfRange)
		{
		}

		IndexOutOfRangeException::IndexOutOfRangeException(const std::string & msg)
			:
			Exception(msg, ExceptionId::IndexOutOfRange)
		{
		}

		IndexOutOfRangeException::~IndexOutOfRangeException()
		{
		}
	}
}