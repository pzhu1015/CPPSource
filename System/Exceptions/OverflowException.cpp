///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Exceptions/OverflowException.h"
namespace System
{
	namespace Exceptions
	{
		OverflowException::OverflowException()
			:
			Exception(ExceptionId::Overflow)
		{
		}

		OverflowException::OverflowException(const std::string & msg)
			:
			Exception(msg, ExceptionId::Overflow)
		{
		}

		OverflowException::~OverflowException()
		{
		}
	}
}