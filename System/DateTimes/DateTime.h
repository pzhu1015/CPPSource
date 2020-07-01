///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_DATETIMES_DATETIME_H
#define SYSTEM_DATETIMES_DATETIME_H

#include "System/DllExport.h"
#include "System/DateTimes/Date.h"
#include <time.h>
#include <string>

namespace System
{
	namespace DateTimes
	{
		class SYSTEM_API DateTime
		{
		public:
			~DateTime();
			DateTime(const DateTime &datetime);
			explicit DateTime(const time_t &seconds);
			explicit DateTime(int year, int month, int day, int hour = 0, int minute = 0, int second = 0);
			explicit DateTime(const std::string &str);
			explicit DateTime(const std::string &str, const std::string &format);

			void AddYears(const time_t &years);
			void AddMonths(const time_t &months);
			void AddDays(const time_t &days);
			void AddHours(const time_t &hours);
			void AddMinutes(const time_t &minutes);
			void AddSeconds(const time_t &seconds);
			void AddWeeks(const time_t &weeks);
		
			int CompareTo(const DateTime *datetime)  const;
			bool Equals(const DateTime* datetime)  const;

			std::string ToString(const std::string &format) const;
			std::string ToString() const;

			int GetYear() const;
			int GetMonth() const;
			int GetDay() const;
			int GetHour() const;
			int GetMinute() const;
			int GetSecond() const;
			int DayOfWeek() const;
			int DayOfYear() const;

			bool operator == (const DateTime &datetime) const;
			bool operator > (const DateTime &datetime) const;
			bool operator < (const DateTime &datetime) const;
			bool operator >= (const DateTime &datetime) const;
			bool operator <= (const DateTime &datetime) const;
			bool operator != (const DateTime &datetime) const;

			static DateTime GetNow();
			static int Comare(const DateTime* value1, const DateTime* value2);
			static bool Equals(const DateTime* value1, const DateTime* value2);
			static DateTime Parse(const std::string &str);
			static DateTime Parse(const std::string &str, const std::string &format);
		private:
			void ParseStr(const std::string &str, const std::string &format);
		private:
			time_t m_seconds;
			tm m_date;
		};

		int64_t SYSTEM_API GetTimestamp();

		int64_t SYSTEM_API GetSeconds();
	}
}

#endif // !SYSTEM_DATETIME_DATETIME_H