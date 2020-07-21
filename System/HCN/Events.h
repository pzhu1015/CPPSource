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
		class TcpConnectEventArgs;

		class IOProcessStartEventArgs;
		class IOProcessStopEventArgs;

		typedef std::function<void(const IOProcessStartEventArgs&)> IOProcessStartEventHandler;
		typedef std::function<void(const IOProcessStopEventArgs&)> IOProcessStopEventHandler;

		typedef std::function<void(const TcpConnectEventArgs&)> TcpConnectEventHandler;
		typedef std::function<void(const TcpOnLineEventArgs&)> TcpOnLineEventHandler;
		typedef std::function<void(const TcpOffLineEventArgs&)> TcpOffLineEventHandler;
		typedef std::function<void(const TcpStartEventArgs&)> TcpStartEventHandler;
		typedef std::function<void(const TcpStopEventArgs&)> TcpSTopEventHandler;
		typedef std::function<void(const TcpAcceptEventArgs&)> TcpAccetpEventHandler;
		typedef std::function<void(const TcpReceiveEventArgs&)> TcpReceiveEventHandler;
		typedef std::function<void(const TcpSendEventArgs&)> TcpSendEventHandler;
		typedef std::function<void(const TcpSelectErrorEventArgs&)> TcpSelectErrorEventHandler;
	}
}

#endif // !SYSTEM_HCN_EVENTS_H
