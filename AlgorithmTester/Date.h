///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef ALGORITHMTESTER_DATE_H
#define ALGORITHMTESTER_DATE_H

int GetDay(int year, int month, int day)
{
	int month_days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
	{
		++month_days[2];
	}

	int days = 0;
	for (int i = 1; i < month; ++i)
	{
		days += month_days[i];
	}
	days += day;
	return days;
}

#endif // !ALGORITHMTESTER_DATE_H
