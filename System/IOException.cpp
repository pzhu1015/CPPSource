///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/IOException.h"
namespace System
{
	IOException::IOException()
		:
		Exception(ExceptionId::IO)
	{
	}
	IOException::IOException(const std::string & msg)
		:
		Exception(msg, ExceptionId::IO)
	{
	}
	IOException::~IOException()
	{
	}
}