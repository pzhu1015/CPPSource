///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_DATETIME_DATETIME_H
#define SYSTEM_DATETIME_DATETIME_H

#include "System/DllExport.h"
#include "System/Date.h"
#include <time.h>
#include <string>

namespace System
{
	namespace DateTime
	{
		class SYSTEM_API SimpleDateTime
		{
		public:
			~SimpleDateTime();
			SimpleDateTime(const SimpleDateTime &datetime);
			explicit SimpleDateTime(const time_t &seconds);
			explicit SimpleDateTime(int year, int month, int day, int hour = 0, int minute = 0, int second = 0);
			explicit SimpleDateTime(const std::string &str);
			explicit SimpleDateTime(const std::string &str, const std::string &format);

			void AddYears(const time_t &years);
			void AddMonths(const time_t &months);
			void AddDays(const time_t &days);
			void AddHours(const time_t &hours);
			void AddMinutes(const time_t &minutes);
			void AddSeconds(const time_t &seconds);
			void AddWeeks(const time_t &weeks);
		
			int CompareTo(const SimpleDateTime *datetime)  const;
			bool Equals(const SimpleDateTime* datetime)  const;

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

			bool operator == (const SimpleDateTime &datetime) const;
			bool operator > (const SimpleDateTime &datetime) const;
			bool operator < (const SimpleDateTime &datetime) const;
			bool operator >= (const SimpleDateTime &datetime) const;
			bool operator <= (const SimpleDateTime &datetime) const;
			bool operator != (const SimpleDateTime &datetime) const;

			static SimpleDateTime GetNow();
			static int Comare(const SimpleDateTime* value1, const SimpleDateTime* value2);
			static bool Equals(const SimpleDateTime* value1, const SimpleDateTime* value2);
			static SimpleDateTime Parse(const std::string &str);
			static SimpleDateTime Parse(const std::string &str, const std::string &format);
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