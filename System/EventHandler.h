///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_EVENTHANDLER_H
#define SYSTEM_EVENTHANDLER_H
#include <functional>
#include <list>

namespace System
{
	typedef std::function<void(const EventArgs&)> EventHandler;
}

#endif // !SYSTEM_EVENTHANDLER_H
