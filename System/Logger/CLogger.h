///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_LOGGER_CLOGGER_H
#define SYSTEM_LOGGER_CLOGGER_H

#include "System/DllExport.h"
#include <string>
#include <mutex>

namespace System
{
	namespace Logger
	{
		static const std::string FATALPREFIX = "FATAL";
		static const std::string ERRORPREFIX = "ERROR";
		static const std::string WARNPREFIX = "WARN";
		static const std::string DEBUGPREFIX = "DEBUG";
		static const std::string INFOPREFIX = "INFO";



		enum class LogLevel
		{
			LogLevel_Stop = 0,
			LogLevel_Fatal,
			LogLevel_Error,
			LogLevel_Warn,
			LogLevel_Debug,
			LogLevel_Info
		};

		enum class LogAppender
		{
			Appender_File = 0,
			Appender_Console
		};

		class SYSTEM_API CLogger final
		{
		public:
			CLogger();
			CLogger(LogLevel log_level, const std::string &path, const std::string &log_name);
			CLogger(LogLevel log_level);
			~CLogger();

			void Fatal(const char* file, const int line, const char* format, ...);
			void Error(const char* file, const int line, const char* format, ...);
			void Warn(const char* file, const int line, const char* format, ...);
			void Debug(const char* file, const int line, const char* format, ...);
			void Info(const char* file, const int line, const char* format, ...);
			void InitFileAppender(LogLevel log_level, const std::string &path, const std::string &log_name);
			static void Init();
		private:
			void Trace(const std::string &str);
			void TraceFile(const std::string &str);
			void TraceConsole(const std::string &str);
			std::string GetLogEntry(const char* file, const int line, const std::string &pre_fix, const std::string &str);
		private:
			FILE* m_file = nullptr;
			LogAppender m_appender;
			LogLevel m_level;
			std::string m_log_dir_path;
			std::string m_log_name;
			std::string m_log_file_path;
			std::mutex m_mutex;
		public:
			static CLogger sm_loginfo_console;
			static CLogger sm_logdebug_console;
			static CLogger sm_logwarn_console;
			static CLogger sm_logerror_console;
			static CLogger sm_logfatal_console;

			static CLogger sm_loginfo_file;
			static CLogger sm_logdebug_file;
			static CLogger sm_logwarn_file;
			static CLogger sm_logerror_file;
			static CLogger sm_logfatal_file;
		};

#define CLOG_CONSOLE_INFO(fmt, ...) {CLogger::sm_loginfo_console.Info(__FILE__, __LINE__, fmt, ##__VA_ARGS__);}
#define CLOG_CONSOLE_DEBUG(fmt, ...) {CLogger::sm_logdebug_console.Debug(__FILE__, __LINE__, fmt, ##__VA_ARGS__);}
#define CLOG_CONSOLE_ERROR(fmt, ...) {CLogger::sm_logerror_console.Error(__FILE__, __LINE__, fmt, ##__VA_ARGS__);}
#define CLOG_CONSOLE_FATAL(fmt, ...) {CLogger::sm_logfatal_console.Fatal(__FILE__, __LINE__, fmt, ##__VA_ARGS__);}
#define CLOG_CONSOLE_WARN(fmt, ...) {CLogger::sm_logwarn_console.Warn(__FILE__, __LINE__, fmt, ##__VA_ARGS__);}

#define CLOG_INFO(fmt, ...) {CLogger::sm_loginfo_file.Info(__FILE__, __LINE__, fmt, ##__VA_ARGS__);}
#define CLOG_DEBUG(fmt, ...) {CLogger::sm_logdebug_file.Debug(__FILE__, __LINE__, fmt, ##__VA_ARGS__);}
#define CLOG_ERROR(fmt, ...) {CLogger::sm_logerror_file.Error(__FILE__, __LINE__, fmt, ##__VA_ARGS__);}
#define CLOG_FATAL(fmt, ...) {CLogger::sm_logfatal_file.Fatal(__FILE__, __LINE__, fmt, ##__VA_ARGS__);}
#define CLOG_WARN(fmt, ...) {CLogger::sm_logwarn_file.Warn(__FILE__, __LINE__, fmt, ##__VA_ARGS__);}
	}
}

#endif // !SYSTEM_LOGGER_CLOGGER_H
