///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "SYSTEM/Logger/CLogger.h"
#include "System/IO/Directory.h"
#include "System/DateTimes/DateTime.h"
#include "System/Application.h"
#include "System/Threading/Thread.h"

#ifdef _WIN32
#include <stdarg.h>
#else
#include <varargs.h>
#endif

using namespace System;
using namespace System::IO;
using namespace System::DateTimes;
using namespace System::Threading;

namespace System
{
	namespace Logger
	{
		CLogger CLogger::sm_loginfo_console;
		CLogger CLogger::sm_logdebug_console;
		CLogger CLogger::sm_logwarn_console;
		CLogger CLogger::sm_logerror_console;
		CLogger CLogger::sm_logfatal_console;

		CLogger CLogger::sm_loginfo_file;
		CLogger CLogger::sm_logdebug_file;
		CLogger CLogger::sm_logwarn_file;
		CLogger CLogger::sm_logerror_file;
		CLogger CLogger::sm_logfatal_file;

		CLogger::CLogger()
			:
			m_level(LogLevel::LogLevel_Info),
			m_appender(LogAppender::Appender_Console)
		{
		}

		CLogger::CLogger(LogLevel log_level, const std::string &path, const std::string &log_name)
		{
			InitFileAppender(log_level, path, log_name);
		}

		CLogger::CLogger(LogLevel log_level)
			:
			m_appender(LogAppender::Appender_Console),
			m_level(log_level)
		{
		}

		CLogger::~CLogger()
		{
			if (m_file != nullptr)
			{
				fclose(m_file);
				m_file = nullptr;
			}
		}

		void CLogger::InitFileAppender(LogLevel log_level, const std::string &path, const std::string &log_name)
		{
			m_appender = LogAppender::Appender_File;
			m_level = log_level;
			m_log_dir_path = path;
			m_log_name = log_name;
			if (m_log_dir_path.empty())
			{
				m_log_dir_path = Application::GetStartupPath();
			}

			if (m_log_dir_path[m_log_dir_path.length() - 1] != '\\')
			{
				m_log_dir_path.append("\\");
			}

			if (!Directory::Exists(m_log_dir_path))
			{
				Directory::CreateDirectory(m_log_dir_path);
			}

			if (m_log_name.empty())
			{
				m_log_name = DateTime::GetNow().ToString("%Y%m%d%H%M%S").append(".log");
			}

			m_log_file_path = m_log_dir_path.append(m_log_name);
			fopen_s(&m_file, m_log_file_path.c_str(), "a+");
		}

		void CLogger::Init()
		{
			sm_loginfo_file.InitFileAppender(LogLevel::LogLevel_Info, "", "info");
			sm_logdebug_file.InitFileAppender(LogLevel::LogLevel_Debug, "", "debug");
			sm_logwarn_file.InitFileAppender(LogLevel::LogLevel_Warn, "", "warn");
			sm_logerror_file.InitFileAppender(LogLevel::LogLevel_Error, "", "error");
			sm_logfatal_file.InitFileAppender(LogLevel::LogLevel_Fatal, "", "fatal");
		}

		void CLogger::Fatal(const char * file, const int line, const char * format, ...)
		{
			if (LogLevel::LogLevel_Fatal > m_level)
			{
				return;
			}

			std::string str;
			if (nullptr != format)
			{
				va_list marker = nullptr;
				va_start(marker, format);
				size_t length = _vscprintf(format, marker) + 1;
				std::vector<char> buffer(length, '\0');
				int write_length = _vsnprintf_s(&buffer[0], buffer.size(), length, format, marker);
				if (write_length > 0)
				{
					str = &buffer[0];
				}
				va_end(marker);
				if (str.empty())
				{
					return;
				}
				std::string log_str = GetLogEntry(file, line, FATALPREFIX, str);
				Trace(log_str);
			}
		}

		void CLogger::Error(const char * file, const int line, const char * format, ...)
		{
			if (LogLevel::LogLevel_Error > m_level)
			{
				return;
			}

			std::string str;
			if (nullptr != format)
			{
				va_list marker = nullptr;
				va_start(marker, format);
				size_t length = _vscprintf(format, marker) + 1;
				std::vector<char> buffer(length, '\0');
				int write_length = _vsnprintf_s(&buffer[0], buffer.size(), length, format, marker);
				if (write_length > 0)
				{
					str = &buffer[0];
				}
				va_end(marker);
				if (str.empty())
				{
					return;
				}
				std::string log_str = GetLogEntry(file, line, ERRORPREFIX, str);
				Trace(log_str);
			}
		}

		void CLogger::Warn(const char * file, const int line, const char * format, ...)
		{
			if (LogLevel::LogLevel_Warn > m_level)
			{
				return;
			}

			std::string str;
			if (nullptr != format)
			{
				va_list marker = nullptr;
				va_start(marker, format);
				size_t length = _vscprintf(format, marker) + 1;
				std::vector<char> buffer(length, '\0');
				int write_length = _vsnprintf_s(&buffer[0], buffer.size(), length, format, marker);
				if (write_length > 0)
				{
					str = &buffer[0];
				}
				va_end(marker);
				if (str.empty())
				{
					return;
				}
				std::string log_str = GetLogEntry(file, line, WARNPREFIX, str);
				Trace(log_str);
			}
		}

		void CLogger::Debug(const char * file, const int line, const char * format, ...)
		{
			if (LogLevel::LogLevel_Debug > m_level)
			{
				return;
			}

			std::string str;
			if (nullptr != format)
			{
				va_list marker = nullptr;
				va_start(marker, format);
				size_t length = _vscprintf(format, marker) + 1;
				std::vector<char> buffer(length, '\0');
				int write_length = _vsnprintf_s(&buffer[0], buffer.size(), length, format, marker);
				if (write_length > 0)
				{
					str = &buffer[0];
				}
				va_end(marker);
				if (str.empty())
				{
					return;
				}
				std::string log_str = GetLogEntry(file, line, DEBUGPREFIX, str);
				Trace(log_str);
			}
		}

		void CLogger::Info(const char * file, const int line, const char * format, ...)
		{
			if (LogLevel::LogLevel_Info > m_level)
			{
				return;
			}

			std::string str;
			if (nullptr != format)
			{
				va_list marker = nullptr;
				va_start(marker, format);
				size_t length = _vscprintf(format, marker) + 1;
				std::vector<char> buffer(length, '\0');
				int write_length = _vsnprintf_s(&buffer[0], buffer.size(), length, format, marker);
				if (write_length > 0)
				{
					str = &buffer[0];
				}
				va_end(marker);
				if (str.empty())
				{
					return;
				}
				std::string log_str = GetLogEntry(file, line, INFOPREFIX, str);
				Trace(log_str);
			}
		}

		void CLogger::Trace(const std::string & str)
		{
			if (m_appender == LogAppender::Appender_Console)
			{
				TraceConsole(str);
			}
			else if (m_appender == LogAppender::Appender_File)
			{
				TraceFile(str);
			}
			else
			{
				//do nothing or error
			}
		}

		void CLogger::TraceFile(const std::string & str)
		{
			try
			{
				std::lock_guard<std::mutex> lock(m_mutex);
				if (nullptr == m_file)
				{
					fopen_s(&m_file, m_log_file_path.c_str(), "a+");
					if (!m_file)
					{
						return;
					}
				}
				fprintf(m_file, "%s\n", str.c_str());
				fflush(m_file);
			}
			catch (...)
			{

			}
		}

		void CLogger::TraceConsole(const std::string & str)
		{
			printf("%s\n", str.c_str());
		}

		std::string CLogger::GetLogEntry(const char* file, const int line, const std::string & pre_fix, const std::string & str)
		{
			std::string log_str = "";
			log_str.append("[")
				.append(DateTime::GetNow().ToString("%Y-%m-%d %H:%M:%S"))
				.append(" ")
				.append(file)
				.append(":")
				.append(std::to_string(line))
				.append(" ")
				.append(Thread::CurrentThreadStrId())
				.append(" ")
				.append(pre_fix)
				.append("] ")
				.append(str);
			return std::move(log_str);
		}
	}
}