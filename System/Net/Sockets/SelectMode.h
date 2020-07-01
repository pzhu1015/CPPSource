///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_NET_SELECTMODE_H
#define SYSTEM_NET_SELECTMODE_H

#include "System/Net/Sockets/SocketInclude.h"

namespace System
{
	namespace Net
	{
		namespace Sockets
		{
			enum SelectMode
			{
				SelectRead,
				SelectWrite,
				SelectError
			};
		}
	}
}
#endif // !SYSTEM_NET_SELECTMODE_H
