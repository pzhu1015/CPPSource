///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_DATETIMES_PTRS_H
#define SYSTEM_DATETIMES_PTRS_H
#include <memory>
namespace System
{
	namespace DateTimes
	{
		class DateTime;
		typedef std::shared_ptr<DateTime> DateTimePtr;
	}
}
#endif // !SYSTEM_DATETIMES_PTRS_H
