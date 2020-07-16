///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/InvalidOperationException.h"
namespace System
{
	InvalidOperationException::InvalidOperationException()
		:
		Exception(ExceptionId::InvalidOperation)
	{
	}
	InvalidOperationException::InvalidOperationException(const std::string & msg)
		:
		Exception(msg, ExceptionId::InvalidOperation)
	{
	}
	InvalidOperationException::~InvalidOperationException()
	{
	}
}