///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_NET_ENDPOINT_H
#define SYSTEM_NET_ENDPOINT_H

#include "System/Object.h"
#include "System/Net/Sockets/AddressFamily.h"

using namespace System::Net::Sockets;
namespace System
{
	namespace Net
	{
		class SYSTEM_API EndPoint : public Object
		{
		public:
			EndPoint() = default;
			~EndPoint() = default;
			virtual AddressFamily GetAddressFamily() = 0;
		private:
			AddressFamily m_address_family;
		};
	}
}

#endif // !SYSTEM_NET_ENDPOINT_H
