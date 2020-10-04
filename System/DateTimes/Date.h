///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_DATETIMES_DATE_H
#define SYSTEM_DATETIMES_DATE_H

#include "System/Base/DllExport.h"
#include <string>

namespace System
{
	namespace DateTimes
	{
		class SYSTEM_API Date final
		{
		public:
			Date(const Date &date);
			explicit Date(int year = 0, int month = 0, int day = 0);
			explicit Date(const std::string &str);
			explicit Date(const std::string &str, const std::string &format);
			void SetDate(int year, int month, int day);
			int GetYear() const;
			int GetMonth() const;
			int GetDay() const;

			std::string ToString();
			std::string ToString(const std::string &format);

			bool operator == (const Date &datetime) const;
			bool operator > (const Date &datetime) const;
			bool operator < (const Date &datetime) const;
			bool operator >= (const Date &datetime) const;
			bool operator <= (const Date &datetime) const;
			bool operator != (const Date &datetime) const;
		private:
			int m_year;
			int m_month;
			int m_day;
		};
	}
}

#endif // !SYSTEM_DATETIME_DATE_H
