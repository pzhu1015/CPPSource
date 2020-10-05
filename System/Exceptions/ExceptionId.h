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
#include "System/Base/DllExport.h"
#include <string>
namespace System
{
	namespace Exceptions
	{
		enum class ExceptionId
		{
			Exception,
			IO,
			NotSupported,
			Argument,
			ArgumentOutOfRange,
			ArgumentNull,
			InvalidOperation,
			Socket,
			Sql,
			Redis
		};

		SYSTEM_API ExceptionId GetExceptionId(const std::string& str);
		SYSTEM_API std::string GetExceptionName(ExceptionId id);
	}
}
#endif // !SYSTEM_EXCEPTIONID_H
