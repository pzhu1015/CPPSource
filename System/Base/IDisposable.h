///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_BASE_DISPOSABLE_H
#define SYSTEM_BASE_DISPOSABLE_H
#include "System/Base/DllExport.h"
namespace System
{
	class SYSTEM_API IDisposable
	{
	public:
		IDisposable() = default;
		virtual void Dispose() = 0;
	};
}
#endif // !SYSTEM_BASE_DISPOSABLE_H
