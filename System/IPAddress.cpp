#include "System/IPAddress.h"

namespace System
{
	namespace Net
	{
		IPAddress::IPAddress()
		{
		}

		IPAddress::IPAddress(const std::string & str)
			:
			m_ip(str)
		{
		}

		std::string IPAddress::GetIPAddress() const
		{
			return m_ip;
		}

		std::string IPAddress::ToString() const
		{
			return m_ip;
		}

		IPAddress IPAddress::Parse(const std::string & str)
		{
			return std::move(IPAddress(str));
		}
		bool IPAddress::IsLoopback(const IPAddress & ipaddress)
		{
			return false;
		}
	}
}
