///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Exceptions/NullReferenceException.h"
namespace System
{
	namespace Exceptions
	{
		NullReferenceException::NullReferenceException()
			:
			Exception(ExceptionId::NullReference)
		{
		}

		NullReferenceException::NullReferenceException(const std::string & msg)
			:
			Exception(msg, ExceptionId::NullReference)
		{
		}

		NullReferenceException::~NullReferenceException()
		{
		}
	}
}