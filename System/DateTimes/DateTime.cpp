///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/DateTimes/DateTime.h"
#include <chrono>

namespace System
{
	namespace DateTimes
	{
		DateTime::~DateTime()
		{
		}

		DateTime::DateTime(const DateTime & datetime)
			:
			m_seconds(datetime.m_seconds),
			m_date(datetime.m_date)
		{
		}

		DateTime::DateTime(const time_t & seconds)
		{
			m_seconds = seconds;
			m_date = *localtime(&m_seconds);
		}

		DateTime::DateTime(int year, int month, int day, int hour, int minute, int second)
		{
			tm t;
			t.tm_year = year - 1900;
			t.tm_mon = month - 1;
			t.tm_mday = day;
			t.tm_hour = hour;
			t.tm_min = minute;
			t.tm_sec = second;
			m_seconds = mktime(&t);
			m_date = *localtime(&m_seconds);
		}

		DateTime::DateTime(const std::string & str)
		{
			ParseStr(str, "%d-%d-%d %d:%d:%d");
		}

		DateTime::DateTime(const std::string & str, const std::string & format)
		{
			ParseStr(str, format);
		}

		void DateTime::AddYears(const time_t & years)
		{
			m_date.tm_year = m_date.tm_year + (int)years;
			m_seconds = mktime(&m_date);

		}

		void DateTime::AddMonths(const time_t & months)
		{
			int y = (int)((m_date.tm_mon + months) / 12);
			m_date.tm_year = m_date.tm_year + y;
			m_date.tm_mon = m_date.tm_mon + (int)((m_date.tm_mon + months) % 12) - 1;
		}

		void DateTime::AddDays(const time_t & days)
		{
			AddHours(days * 24);
		}

		void DateTime::AddHours(const time_t & hours)
		{
			AddMinutes(hours * 60);
		}

		void DateTime::AddMinutes(const time_t & minutes)
		{
			AddSeconds(minutes * 60);
		}

		void DateTime::AddSeconds(const time_t & seconds)
		{
			m_seconds = m_seconds + seconds;
			m_date = *localtime(&m_seconds);
		}

		void DateTime::AddWeeks(const time_t & weeks)
		{
			AddDays(weeks * 7);
		}
		
		int DateTime::CompareTo(const DateTime * datetime) const
		{
			if (m_seconds == datetime->m_seconds)
			{
				return 0;
			}
			if (m_seconds < datetime->m_seconds)
			{
				return -1;
			}
			return 1;
		}

		bool DateTime::Equals(const DateTime * datetime)  const
		{
			if (m_seconds == datetime->m_seconds)
			{
				return true;
			}
			return false;
		}

		DateTime DateTime::Parse(const std::string & str)
		{
			return DateTime(str);
		}

		DateTime DateTime::Parse(const std::string & str, const std::string & format)
		{
			return DateTime(str, format);
		}

		void DateTime::ParseStr(const std::string & str, const std::string & format)
		{
			int year, month, day, hour, minutes, seconds;
			sscanf(str.c_str(), format.c_str(), &year, &month, &day, &hour, &minutes, &seconds);
			if (year < 1900) year = 1970;
			if (month < 0) month = 1;
			if (day < 0) day = 1;
			if (hour < 0) hour = 0;
			if (minutes < 0) minutes = 0;
			if (seconds < 0) seconds = 0;
			tm t;
			t.tm_year = year - 1900;
			t.tm_mon = month - 1;
			t.tm_mday = day;
			t.tm_hour = hour;
			t.tm_min = minutes;
			t.tm_sec = seconds;
			m_seconds = mktime(&t);
			m_date = *localtime(&m_seconds);
		}

		std::string DateTime::ToString(const std::string & format) const
		{
			char str[256];
			strftime(str, sizeof(str), format.c_str(), &m_date);
			return std::string(str);
		}

		std::string DateTime::ToString() const
		{
			return ToString("%Y-%m-%d %H:%M:%S");
		}

		int DateTime::GetYear() const
		{
			return m_date.tm_year + 1900;
		}

		int DateTime::GetMonth() const
		{
			return m_date.tm_mon;
		}

		int DateTime::GetDay() const
		{
			return m_date.tm_mday;
		}

		int DateTime::GetHour() const
		{
			return m_date.tm_hour;
		}

		int DateTime::GetMinute() const
		{
			return m_date.tm_min;
		}

		int DateTime::GetSecond() const
		{
			return m_date.tm_sec;
		}

		int DateTime::DayOfWeek() const
		{
			return m_date.tm_wday;
		}

		int DateTime::DayOfYear() const
		{
			return m_date.tm_yday;
		}

		bool DateTime::operator==(const DateTime & datetime) const
		{
			return Equals(&datetime);
		}

		bool DateTime::operator>(const DateTime & datetime) const
		{
			if (m_seconds > datetime.m_seconds)
			{
				return true;
			}
			return false;
		}

		bool DateTime::operator<(const DateTime & datetime) const
		{
			if (m_seconds < datetime.m_seconds)
			{
				return true;
			}
			return false;
		}

		bool DateTime::operator>=(const DateTime & datetime) const
		{
			if (m_seconds >= datetime.m_seconds)
			{
				return true;
			}
			return false;
		}

		bool DateTime::operator<=(const DateTime & datetime) const
		{
			if (m_seconds <= datetime.m_seconds)
			{
				return true;
			}
			return false;
		}

		bool DateTime::operator!=(const DateTime & datetime) const
		{
			if (m_seconds != datetime.m_seconds)
			{
				return true;
			}
			return false;
		}

		DateTime DateTime::GetNow()
		{
			return DateTime(time(0));
		}

		int DateTime::Comare(const DateTime& value1, const DateTime& value2)
		{
			if (value1.m_seconds == value2.m_seconds)
			{
				return 0;
			}
			if (value1.m_seconds < value2.m_seconds)
			{
				return -1;
			}
			return 1;
		}

		bool DateTime::Equals(const DateTime& value1, const DateTime & value2)
		{
			if (value1.m_seconds == value2.m_seconds)
			{
				return true;
			}
			return false;
		}

		__int64 SYSTEM_API GetTimestamp()
		{
			std::chrono::system_clock::duration d = std::chrono::system_clock::now().time_since_epoch();
			std::chrono::microseconds mic = std::chrono::duration_cast<std::chrono::microseconds>(d);
			return mic.count();
		}
		__int64 SYSTEM_API GetSeconds()
		{
			std::chrono::system_clock::duration d = std::chrono::system_clock::now().time_since_epoch();
			std::chrono::seconds sec = std::chrono::duration_cast<std::chrono::seconds>(d);
			return sec.count();
		}
}
}
