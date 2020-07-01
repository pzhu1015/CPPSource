///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/DateTimes/Time.h"

namespace System
{
	namespace DateTimes
	{
		Time::Time(int hour, int minute, int second)
			:
			m_hour(hour),
			m_minute(minute),
			m_second(second)
		{
		}

		Time::Time(const std::string & str)
		{
		}

		Time::Time(const Time & time)
			:
			m_hour(time.m_hour),
			m_minute(time.m_minute),
			m_second(time.m_second)
		{
		}

		Time::Time(const std::string & str, const std::string & format)
		{
		}

		Time::~Time()
		{
		}

		Time & Time::operator=(const Time & time)
		{
			m_hour = time.m_hour;
			m_minute = time.m_minute;
			m_second = time.m_second;
			return *this;
		}

		void Time::SetTime(int hour, int minute, int second)
		{
			minute += second / 60;
			hour += minute / 60;
			second %= 60;
			minute %= 60;
			hour %= 24;
			m_hour = hour;
			m_minute = minute;
			m_second = second;
		}

		void Time::AddSecond()
		{
		}

		void Time::AddMinute()
		{
		}

		void Time::AddHour()
		{
		}

		void Time::AddSeconds()
		{
		}

		void Time::AddMinutes()
		{
		}

		void Time::AddHours()
		{
		}

		void Time::Tick()
		{
			m_second++;
			m_minute += m_second / 60;
			m_second %= 60;
			m_hour += m_minute / 60;
			m_minute %= 60;
			m_hour %= 24;
		}

		bool Time::IsTime()
		{
			return false;
		}

		std::string Time::ToString()
		{
			return std::string();
		}

		std::string Time::ToString(const std::string & format)
		{
			return std::string();
		}
		bool Time::operator>(const Time & time) const
		{
			return false;
		}
		bool Time::operator<(const Time & time)  const
		{
			return false;
		}
		bool Time::operator>=(const Time & time) const
		{
			return false;
		}
		bool Time::operator<=(const Time & time)  const
		{
			return false;
		}
		bool Time::operator==(const Time & time)  const
		{
			return false;
		}
		bool Time::operator!=(const Time & time)  const
		{
			return false;
		}
	}
}
