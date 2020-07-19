///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_NET_PROTOCOLTYPE_H
#define SYSTEM_NET_PROTOCOLTYPE_H

#include "System/Net/Sockets/SocketInclude.h"

namespace System
{
	namespace Net
	{
		namespace Sockets
		{
			enum class ProtocolType
			{
				Unknown = -1,
				Tcp = IPPROTO_TCP,
				Udp = IPPROTO_UDP
			};
		}
	}
}
#endif // !SYSTEM_NET_PROTOCOLTYPE_H
