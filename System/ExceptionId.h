///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_EXCEPTIONID_H
#define SYSTEM_EXCEPTIONID_H
#include "System/DllExport.h"
#include <string>
namespace System
{
	enum class ExceptionId
	{
		Exception,
		NotSupported,
		Argument
	};

	SYSTEM_API ExceptionId GetExceptionId(const std::string& str);
	SYSTEM_API std::string GetExceptionName(ExceptionId id);
}
#endif // !SYSTEM_EXCEPTIONID_H
