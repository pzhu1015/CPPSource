///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_THREADING_RUNNABLE_H
#define SYSTEM_THREADING_RUNNABLE_H

#include "System/DllExport.h"

namespace System
{
	namespace Threading
	{
		class SYSTEM_API Runnable
		{
		public:
			Runnable() = default;
			virtual ~Runnable() = default;
			virtual void Run() = 0;
		};
	}
}
#endif // !SYSTEM_THREADING_RUNNABLE_H
