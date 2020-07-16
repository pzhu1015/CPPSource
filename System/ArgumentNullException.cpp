///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/ArgumentNullException.h"
namespace System
{
	ArgumentNullException::ArgumentNullException()
		:
		Exception(ExceptionId::ArgumentNull)
	{
	}

	ArgumentNullException::ArgumentNullException(const std::string & msg)
		:
		Exception(msg, ExceptionId::ArgumentNull)
	{
	}

	ArgumentNullException::~ArgumentNullException()
	{
	}
}