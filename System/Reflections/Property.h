///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_REFLECTIONS_PROPERTY_H
#define SYSTEM_REFLECTIONS_PROPERTY_H

namespace System
{
	namespace Reflections
	{
		#define PROPERTY(value)\
		inline void set_##value(const decltype(value) &value)\
		{\
			this->##value = value;\
		}\
		inline const decltype(value)& get_##value() const\
		{\
			return this->##value;\
		}
	}
}

#endif // !SYSTEM_REFLECTIONS_PROPERTY_H
