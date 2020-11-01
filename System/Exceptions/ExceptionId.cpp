///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Exceptions/ExceptionId.h"

namespace System
{
	namespace Exceptions
	{
		ExceptionId GetExceptionId(const std::string & str)
		{
			return ExceptionId::Exception;
		}

		std::string GetExceptionName(ExceptionId id)
		{
			switch (id)
			{
			case ExceptionId::ArrayTypeMismatch:
				return "ArrayTypeMismatchException";
			case ExceptionId::IO:
				return "IOException";
			case ExceptionId::NotSupported:
				return "NotSupportedException";
			case ExceptionId::Argument:
				return "ArgumentException";
			case ExceptionId::ArgumentOutOfRange:
				return "ArgumentOutOfRangeException";
			case ExceptionId::IndexOutOfRange:
				return "IndexOutOfRangeException";
			case ExceptionId::ArgumentNull:
				return "ArgumentNullException";
			case ExceptionId::InvalidOperation:
				return "InvalidOperationException";
			case ExceptionId::NullReference:
				return "NullReferenceException";
			case ExceptionId::Socket:
				return "SocketException";
			case ExceptionId::Overflow:
				return "OverflowException";
			case ExceptionId::Sql:
				return "SqlException";
			case ExceptionId::Redis:
				return "RedisException";
			default:
				return "Exception";
			}
		}
	}
}
