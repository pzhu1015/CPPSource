#include "System/DateTime/Date.h"

namespace System
{
	namespace DateTime
	{
		Date::Date(int year, int month, int day)
		{
			SetDate(year, month, day);
		}

		Date::Date(const std::string & str)
		{
		}

		Date::Date(const std::string & str, const std::string & format)
		{
		}

		Date::Date(const Date &date)
		{
			SetDate(date.GetYear(), date.GetMonth(), date.GetDay());
		}

		void Date::SetDate(int year, int month, int day)
		{
			m_year = year;
			m_month = month;
			m_day = day;
		}

		int Date::GetYear() const
		{
			return m_year;
		}

		int Date::GetMonth() const
		{
			return m_month;
		}

		int Date::GetDay() const
		{
			return m_day;
		}
		std::string Date::ToString()
		{
			return std::string();
		}
		std::string Date::ToString(const std::string & format)
		{
			return std::string();
		}
		bool Date::operator==(const Date & datetime) const
		{
			return false;
		}
		bool Date::operator>(const Date & datetime) const
		{
			return false;
		}
		bool Date::operator<(const Date & datetime) const
		{
			return false;
		}
		bool Date::operator>=(const Date & datetime) const
		{
			return false;
		}
		bool Date::operator<=(const Date & datetime) const
		{
			return false;
		}
		bool Date::operator!=(const Date & datetime) const
		{
			return false;
		}
	}
}
