///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Net/IPEndPoint.h"
#include "System/Net/IPAddress.h"

namespace System
{
	namespace Net
	{
		IPEndPoint::IPEndPoint()
		{
		}
		IPEndPoint::~IPEndPoint()
		{
		}
		IPEndPoint::IPEndPoint(const IPEndPoint & endpoint)
			:
			m_ip(endpoint.GetIPAddress()),
			m_port(endpoint.GetPort())
		{
		}
		IPEndPoint::IPEndPoint(const IPAddressPtr &ip, int port)
			:
			m_ip(ip),
			m_port(port)
		{
		}
		int IPEndPoint::GetPort() const
		{
			return m_port;
		}
		IPAddressPtr IPEndPoint::GetIPAddress() const
		{
			return m_ip;
		}
		std::string IPEndPoint::ToString()
		{
			return m_ip->ToString() + ":" + std::to_string(m_port);
		}
		IPEndPoint & IPEndPoint::operator=(const IPEndPoint & endpoint)
		{
			m_ip = endpoint.GetIPAddress();
			m_port = endpoint.GetPort();
			return *this;
		}
		AddressFamily IPEndPoint::GetAddressFamily()
		{
			return m_ip->GetAddressFamily();
		}
	}
}
