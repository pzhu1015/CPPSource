///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_DATETIMES_TIME_H
#define SYSTEM_DATETIMES_TIME_H
#include "System/DllExport.h"
#include <string>

namespace System
{
	namespace DateTimes
	{
		class SYSTEM_API Time
		{
		public:
			Time(const Time &time);
			explicit Time(int hour = 0, int minute = 0, int second = 0);
			explicit Time(const std::string &str);
			explicit Time(const std::string &str, const std::string &format);
			~Time();

			Time& operator=(const Time &time);
			void SetTime(int hour, int minute, int second);
			void AddSecond();
			void AddMinute();
			void AddHour();
			void AddSeconds();
			void AddMinutes();
			void AddHours();
			void Tick();
			bool IsTime();
			std::string ToString();
			std::string ToString(const std::string &format);

			bool operator>(const Time &time) const;
			bool operator<(const Time &time) const;
			bool operator>=(const Time &time) const;
			bool operator<=(const Time &time) const;
			bool operator==(const Time &time) const;
			bool operator!=(const Time &time) const;

		private:
			unsigned short m_hour;
			unsigned short m_minute;
			unsigned short m_second;
		};
	}
}

#endif // !SYSTEM_DATETIME_TIME_H
