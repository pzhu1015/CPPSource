#include "System/Net/IPEndPoint.h"

namespace System
{
	namespace Net
	{
		IPEndPoint::IPEndPoint()
		{
		}
		IPEndPoint::~IPEndPoint()
		{
			delete m_ip;
		}
		IPEndPoint::IPEndPoint(const IPEndPoint & endpoint)
			:
			m_ip(endpoint.GetIPAddress()),
			m_port(endpoint.GetPort())
		{
		}
		IPEndPoint::IPEndPoint(IPAddress* ip, int port)
			:
			m_ip(ip),
			m_port(port)
		{
		}
		int IPEndPoint::GetPort() const
		{
			return m_port;
		}
		IPAddress* IPEndPoint::GetIPAddress() const
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
			return AddressFamily();
		}
	}
}
