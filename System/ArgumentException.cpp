///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/ArgumentException.h"
namespace System
{
	ArgumentException::ArgumentException()
		:
		Exception(ExceptionId::Argument)
	{
	}

	ArgumentException::ArgumentException(const std::string & msg)
		:
		Exception(msg, ExceptionId::Argument)
	{
	}

	ArgumentException::~ArgumentException()
	{
	}
}