///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_NET_PTRS_H
#define SYSTEM_NET_PTRS_H
#include <memory>
namespace System
{
	namespace Net
	{
		class EndPoint;
		class IPEndPoint;
		class IPAddress;
		class TcpClient;
		class TcpListener;
		class SimpleTcpClient;
		class SimpleTcpListener;
		typedef std::shared_ptr<EndPoint> EndPointPtr;
		typedef std::shared_ptr<IPEndPoint> IPEndPointPtr;
		typedef std::shared_ptr<IPAddress> IPAddressPtr;
		typedef std::shared_ptr<TcpClient> TcpClientPtr;
		typedef std::shared_ptr<TcpListener> TcpListenerPtr;
		typedef std::shared_ptr<SimpleTcpClient> SimpleTcpClientPtr;
		typedef std::shared_ptr<SimpleTcpListener> SimpleTcpListenerPtr;
	}
}


#endif // !SYSTEM_NET_PTRS_H
