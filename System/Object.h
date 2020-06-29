///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_OBJECT_H
#define SYSTEM_OBJECT_H

#include "System/DllExport.h"
#include <string>

namespace System
{
	class SYSTEM_API Object
	{
	public:
		Object() = default;
		~Object() = default;
		virtual std::string ToString() = 0;
	};

}


#endif // !SYSTEM_OBJECT_H
