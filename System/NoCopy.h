///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_NOCOPY_H
#define SYSTEM_NOCOPY_H
#include "System/DllExport.h"
namespace System
{
	class SYSTEM_API NoCopy
	{
	protected:
		NoCopy() = default;
		~NoCopy() = default;
	private:
		NoCopy(const NoCopy& that) {}
		const NoCopy& operator=(const NoCopy& that);
	};
}


#endif // !SYSTEM_NOCOPY_H
