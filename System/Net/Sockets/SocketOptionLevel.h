///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_NET_SOCKETOPTIONLEVEL_H
#define SYSTEM_NET_SOCKETOPTIONLEVEL_H

#include "System/Net/Sockets/SocketInclude.h"

namespace System
{
	namespace Net
	{
		namespace Sockets
		{
			enum class SocketOptionLevel
			{
				IP,
				Tcp,
				Udp,
				IPv6,
				Socket = SOL_SOCKET
			};
		}
	}
}

#endif // !SYSTEM_NET_SOCKETOPTIONLEVEL_H
