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
		virtual ~Object() = default;
		virtual bool Equals(const Object* object);
		virtual int CompareTo(const Object* object);
		virtual std::string ToString();
	};

}


#endif // !SYSTEM_OBJECT_H
