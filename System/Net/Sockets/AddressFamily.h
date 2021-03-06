///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_NET_ADDRESSFAMILY_H
#define SYSTEM_NET_ADDRESSFAMILY_H

#include "System/Net/Sockets/SocketInclude.h"

namespace System
{
	namespace Net
	{
		namespace Sockets
		{
			enum class AddressFamily
			{
				Unknown = -1,
				InterNetwork = AF_INET
			};
		}
	}
}

#endif // !SYSTEM_NET_ADDRESSFAMILY_H
