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

#include "System/DllExport.h"
#include <string>

namespace System
{
	namespace Net
	{
		class SYSTEM_API IPAddress
		{
		public:
			IPAddress();
			IPAddress(const std::string &str);

			std::string GetIPAddress() const;
			std::string ToString() const;

			static IPAddress Parse(const std::string &str);
			static bool IsLoopback(const IPAddress &ipaddress);
		private:
			std::string m_ip;
		};
	}
}

#endif // !SYSTEM_NET_IPADDRESS_H
