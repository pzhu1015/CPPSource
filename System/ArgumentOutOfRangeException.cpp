///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/ArgumentOutOfRangeException.h"
namespace System
{
	ArgumentOutOfRangeException::ArgumentOutOfRangeException()
		:
		Exception(ExceptionId::ArgumentOutOfRange)
	{
	}
	ArgumentOutOfRangeException::ArgumentOutOfRangeException(const std::string & msg)
		:
		Exception(msg, ExceptionId::ArgumentOutOfRange)
	{
	}
	ArgumentOutOfRangeException::~ArgumentOutOfRangeException()
	{
	}
}