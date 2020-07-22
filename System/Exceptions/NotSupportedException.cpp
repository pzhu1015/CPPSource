///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Exceptions/NotSupportedException.h"
namespace System
{
	namespace Exceptions
	{
		NotSupportedException::NotSupportedException()
			:
			Exception(ExceptionId::NotSupported)
		{
		}

		NotSupportedException::NotSupportedException(const std::string & msg)
			:
			Exception(msg, ExceptionId::NotSupported)
		{
		}

		NotSupportedException::~NotSupportedException()
		{
		}
	}
}