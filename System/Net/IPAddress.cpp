#include "System/Net/IPAddress.h"

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

		AddressFamily IPAddress::GetAddressFamily() const
		{
			return m_family;
		}

		IPAddressPtr IPAddress::Parse(const std::string & str)
		{
			return std::make_shared<IPAddress>(str);
		}

		bool IPAddress::IsLoopback(const IPAddress & ipaddress)
		{
			return false;
		}
	}
}
