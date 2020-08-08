///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_NET_IPENDPOINT_H
#define SYSTEM_NET_IPENDPOINT_H
#include "System/DllExport.h"
#include "System/Net/EndPoint.h"
#include "System/Net/Ptrs.h"

namespace System
{
	namespace Net
	{
		class SYSTEM_API IPEndPoint final : public EndPoint
		{
		public:
			static const int MAXPORT = 65535;
			static const int MINPORT = 0;
		public:
			IPEndPoint();
			virtual ~IPEndPoint();
			IPEndPoint(const IPEndPoint &endpoint);
			IPEndPoint(const IPAddressPtr &ip, int port);
			int GetPort() const;
			IPAddressPtr GetIPAddress() const;	
			IPEndPoint& operator = (const IPEndPoint &endpoint);
			virtual AddressFamily GetAddressFamily() override;
			virtual std::string ToString() override;
		private:
			IPAddressPtr m_ip;
			int m_port;
		};
	}
}
#endif // !SYSTEM_NET_IPENDPOINT_H
