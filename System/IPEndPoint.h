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
#include "System/IPAddress.h"
namespace System
{
	namespace Net
	{
		class SYSTEM_API IPEndPoint
		{
		public:
			const int MAXPORT = 65535;
			const int MINPORT = 0;
		public:
			IPEndPoint();
			~IPEndPoint();
			IPEndPoint(const IPEndPoint &endpoint);
			IPEndPoint(IPAddress* ip, int port);
			int GetPort() const;
			IPAddress* GetIPAddress() const;
			std::string ToString() const;
			IPEndPoint& operator = (const IPEndPoint &endpoint);
		private:
			IPAddress* m_ip;
			int m_port;
		};
	}
}
#endif // !SYSTEM_NET_IPENDPOINT_H
