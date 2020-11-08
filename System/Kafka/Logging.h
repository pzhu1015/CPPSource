///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_KAFKA_LOGGING_H
#define SYSTEM_KAFKA_LOGGING_H
namespace System
{
	namespace Kafka
	{
		// Based on syslog.h levels
		enum class LogLevel : int {
			LogEmerg = 0,    /* system is unusable */
			LogAlert = 1,    /* action must be taken immediately */
			LogCrit = 2,    /* critical conditions */
			LogErr = 3,    /* error conditions */
			LogWarning = 4,    /* warning conditions */
			LogNotice = 5,    /* normal but significant condition */
			LogInfo = 6,    /* informational */
			LogDebug = 7     /* debug-level messages */
		};
	}
}
#endif // !SYSTEM_KAFKA_LOGGING_H
