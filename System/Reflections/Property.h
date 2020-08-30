///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef System_Reflections_Property_h
#define System_Reflections_Property_h

namespace System
{
	namespace Reflections
	{
		#define PROPERTY(value)\
		inline void set_##value(const decltype(value) &value)\
		{\
			this->##value = value;\
		}\
		inline decltype(value)& get_##value()\
		{\
			return this->##value;\
		}
	}
}

#endif // !System_Reflections_Property_h
