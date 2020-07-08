///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Exception.h"

namespace System
{

	Exception::Exception(ExceptionId id)
	{
		m_id = id;
	}

	Exception::Exception(const std::string & msg, ExceptionId id)
	{
		m_msg = msg;
		m_id = id;
	}

	Exception::~Exception()
	{
	}

	std::string Exception::what() const
	{
		return "throw " + System::GetExceptionName(m_id) + ": " + m_msg;
	}
}