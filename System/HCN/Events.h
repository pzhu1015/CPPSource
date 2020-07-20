///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_HCN_EVENTS_H
#define SYSTEM_HCN_EVENTS_H
#include <functional>
namespace System
{
	namespace HCN
	{
		
		class TcpOnLineEventArgs;
		class TcpOffLineEventArgs;
		class TcpStartEventArgs;
		class TcpStopEventArgs;
		class TcpAcceptEventArgs;
		class TcpReceiveEventArgs;
		class TcpSendEventArgs;
		class TcpSelectErrorEventArgs;

		class ClientProcessStartEventArgs;
		class ClientProcessStopEventArgs;

		typedef std::function<void(ClientProcessStartEventArgs&)> ClientProcessStartEventHandler;
		typedef std::function<void(ClientProcessStopEventArgs&)> ClientProcessStopEventHandler;

		typedef std::function<void(TcpOnLineEventArgs&)> TcpOnLineEventHandler;
		typedef std::function<void(TcpOffLineEventArgs&)> TcpOffLineEventHandler;
		typedef std::function<void(TcpStartEventArgs&)> TcpStartEventHandler;
		typedef std::function<void(TcpStopEventArgs&)> TcpSTopEventHandler;
		typedef std::function<void(TcpAcceptEventArgs&)> TcpAccetpEventHandler;
		typedef std::function<void(TcpReceiveEventArgs&)> TcpReceiveEventHandler;
		typedef std::function<void(TcpSendEventArgs&)> TcpSendEventHandler;
		typedef std::function<void(TcpSelectErrorEventArgs&)> TcpSelectErrorEventHandler;
	}
}

#endif // !SYSTEM_HCN_EVENTS_H
