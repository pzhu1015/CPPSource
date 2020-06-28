///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/DllExport.h"
#include "Object.h"

namespace System
{
	bool Object::Equals(const Object * object)
	{
		return false;
	}
	int Object::CompareTo(const Object * object)
	{
		return 0;
	}
	std::string Object::ToString()
	{
		return std::string();
	}
}
