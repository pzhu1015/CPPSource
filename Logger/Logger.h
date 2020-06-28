///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef LOGGER_LOGGER_H
#define LOGGER_LOGGER_H

#include "Logger/DllExport.h"
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/configurator.h>
#include <string>
#include <stdio.h>

using namespace log4cplus;

namespace System
{
	namespace Logger
	{
		#define MAX_LOG_MSG_LEN 4096
		class LOGGER_API Logger
		{
		public:
			static bool Init(const std::string &path);

			static void Debug(const char* format, ...);
			static void Info(const char* format, ...);
			static void Warn(const char* format, ...);
			static void Error(const char* format, ...);
			static void Fatal(const char* format, ...);
		public:
			static log4cplus::Logger sm_debug;
			static log4cplus::Logger sm_info;
			static log4cplus::Logger sm_warn;
			static log4cplus::Logger sm_error;
			static log4cplus::Logger sm_fatal;
		};

#define LOGDEBUG(fmt,...){					\
	char logmsg[MAX_LOG_MSG_LEN] = {0};		\
	snprintf(logmsg, sizeof(logmsg), fmt, ##__VA_ARGS__);		\
	LOG4CPLUS_DEBUG(System::Logger::Logger::sm_debug, logmsg);	\
}

#define LOGINFO(fmt,...){					\
	char logmsg[MAX_LOG_MSG_LEN] = {0};		\
	snprintf(logmsg, sizeof(logmsg), fmt, ##__VA_ARGS__);		\
	LOG4CPLUS_INFO(System::Logger::Logger::sm_info, logmsg);	\
}

#define LOGWARN(fmt,...){					\
	char logmsg[MAX_LOG_MSG_LEN] = {0};		\
	snprintf(logmsg, sizeof(logmsg), fmt, ##__VA_ARGS__);		\
	LOG4CPLUS_WARN(System::Logger::Logger::sm_warn, logmsg);	\
}

#define LOGERROR(fmt,...){					\
	char logmsg[MAX_LOG_MSG_LEN] = {0};		\
	snprintf(logmsg, sizeof(logmsg), fmt, ##__VA_ARGS__);		\
	LOG4CPLUS_ERROR(System::Logger::Logger::sm_error, logmsg);	\
}

#define LOGFATAL(fmt,...){					\
	char logmsg[MAX_LOG_MSG_LEN] = {0};		\
	snprintf(logmsg, sizeof(logmsg), fmt, ##__VA_ARGS__);		\
	LOG4CPLUS_FATAL(System::Logger::Logger::sm_fatal, logmsg);	\
}
	}
}
#endif
