///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_EXCEPTIONS_EXCEPTION_H
#define SYSTEM_EXCEPTIONS_EXCEPTION_H
#include "System/DllExport.h"
#include "System/ExceptionId.h"
#include <string>

namespace System
{
	class SYSTEM_API Exception
	{
	public:
		Exception(ExceptionId id = ExceptionId::Exception);
		Exception(const std::string &msg, ExceptionId id = ExceptionId::Exception);
		virtual ~Exception();
		virtual std::string what() const;
	protected:
		std::string m_msg;
		std::string m_name;
		ExceptionId m_id;
	};
}

#endif // !SYSTEM_EXCEPTIONS_EXCEPTION_H
