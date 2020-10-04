///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_NET_IPADDRESS_H
#define SYSTEM_NET_IPADDRESS_H

#include "System/Base/DllExport.h"
#include "System/Net/Sockets/AddressFamily.h"
#include "System/Net/Ptrs.h"
#include <string>
#include <memory>

using namespace System::Net::Sockets;
namespace System
{
	namespace Net
	{
		class SYSTEM_API IPAddress final
		{
		public:
			IPAddress();
			IPAddress(const std::string &str);

			std::string GetIPAddress() const;
			std::string ToString() const;
			AddressFamily GetAddressFamily() const;

			static IPAddressPtr Parse(const std::string &str);
			static bool IsLoopback(const IPAddress &ipaddress);
		private:
			std::string m_ip;
			AddressFamily m_family = AddressFamily::InterNetwork;
		};
	}
}

#endif // !SYSTEM_NET_IPADDRESS_H
