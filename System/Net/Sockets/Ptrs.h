///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_NET_SOCKETS_PTRS_H
#define SYSTEM_NET_SOCKETS_PTRS_H
#include <memory>
namespace System
{
	namespace Net
	{
		namespace Sockets
		{
			class Socket;
			class NetworkStream;
			class SocketAsyncEventArgs;
			typedef std::shared_ptr<Socket> SocketPtr;
			typedef std::shared_ptr<NetworkStream> NetworkStreamPtr;
			typedef std::shared_ptr<SocketAsyncEventArgs> SocketAsyncEventArgsPtr;
		}
	}
}


#endif // !SYSTEM_NET_SOCKETS_PTRS_H
