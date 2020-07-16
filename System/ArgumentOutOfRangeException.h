///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_ARGUMENTOUTOFRANGEEXCEPTION_H
#define SYSTEM_ARGUMENTOUTOFRANGEEXCEPTION_H
#include "System/Exception.h"
namespace System
{
	class SYSTEM_API ArgumentOutOfRangeException: public Exception
	{
	public:
		ArgumentOutOfRangeException();
		ArgumentOutOfRangeException(const std::string &msg);
		virtual ~ArgumentOutOfRangeException();
	};
}
#endif // !SYSTEM_ARGUMENTOUTOFRANGEEXCEPTION_H
