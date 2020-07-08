#include "ExceptionId.h"
///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/ExceptionId.h"

namespace System
{
	ExceptionId GetExceptionId(const std::string & str)
	{
		return ExceptionId();
	}

	std::string GetExceptionName(ExceptionId id)
	{
		switch (id)
		{
		case ExceptionId::Argument:
			return "ArgumentException";
		case ExceptionId::NotSupported:
			return "NotSupportedException";
		default:
			return "Exception";
		}
	}
}
