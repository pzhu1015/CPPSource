///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "Logger/Logger.h"
#include <log4cplus/log4cplus.h>

namespace System
{
	namespace Logger
	{
		log4cplus::Logger Logger::sm_debug;
		log4cplus::Logger Logger::sm_info;
		log4cplus::Logger Logger::sm_warn;
		log4cplus::Logger Logger::sm_error;
		log4cplus::Logger Logger::sm_fatal;

		bool Logger::Init(const std::string & path)
		{
			PropertyConfigurator::doConfigure(LOG4CPLUS_STRING_TO_TSTRING(path));
			sm_debug = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("DEBUG_MSGS"));
			sm_info = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("INFO_MSGS"));
			sm_warn = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("WARN_MSGS"));
			sm_error = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("ERROR_MSGS"));
			sm_fatal = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("FATAL_MSGS"));
			return true;
		}

		void Logger::Debug(const char * format, ...)
		{
		}

		void Logger::Info(const char * format, ...)
		{
		}

		void Logger::Warn(const char * format, ...)
		{
		}

		void Logger::Error(const char * format, ...)
		{
		}

		void Logger::Fatal(const char * format, ...)
		{
		}

	}
}