///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_DISPOSABLE_H
#define SYSTEM_DISPOSABLE_H
#include "System/DllExport.h"
namespace System
{
	class SYSTEM_API IDisposable
	{
	public:
		IDisposable() = default;
		virtual void Dispose() = 0;
	};
}
#endif // !SYSTEM_DISPOSABLE_H
