///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Exceptions/ArrayTypeMismatchException.h"
namespace System
{
	namespace Exceptions
	{
		ArrayTypeMismatchException::ArrayTypeMismatchException()
			:
			Exception(ExceptionId::ArrayTypeMismatch)
		{
		}
		ArrayTypeMismatchException::ArrayTypeMismatchException(const std::string & msg)
			:
			Exception(msg, ExceptionId::ArrayTypeMismatch)
		{
		}
		ArrayTypeMismatchException::~ArrayTypeMismatchException()
		{
		}
	}
}