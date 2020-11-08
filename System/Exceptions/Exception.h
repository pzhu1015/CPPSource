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
#include "System/Base/DllExport.h"
#include <stdexcept>
#include <string>
#include <typeinfo>

#define TYPE_NAME (typeid(std::remove_reference<decltype(*this)>::type).name())
namespace System
{
	namespace Exceptions
	{
		class SYSTEM_API Exception : public std::exception
		{
		public:
			Exception()
			{
				m_msg.append("throw ").append(TYPE_NAME).append(": ").append(std::exception::what());
			}

			Exception(const char* message)
			{
				m_msg.append("throw ").append(TYPE_NAME).append(": ").append(message);
			}

			Exception(const std::string& message)
			{
				m_msg.append("throw ").append(TYPE_NAME).append(": ").append(message);
			}

			Exception(const std::string & msg, const char* class_name)
			{
				m_msg.append("throw ").append(class_name).append(": ").append(msg.data());
			}

			~Exception()
			{
			}

			const char* what() const noexcept
			{
				return m_msg.data();
			}
		protected:
			std::string m_msg;
		};
	}
}

#endif // !SYSTEM_EXCEPTIONS_EXCEPTION_H
