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
		class TcpReceiveEventArgs;
		class TcpSendEventArgs;
		class TcpSelectErrorEventArgs;
		class TcpConnectEventArgs;

		class IOProcessReadStartEventArgs;
		class IOProcessReadStopEventArgs;

		class IOProcessWriteStartEventArgs;
		class IOProcessWriteStopEventArgs;

		typedef std::function<void(const IOProcessReadStartEventArgs&)> IOProcessReadStartEventHandler;
		typedef std::function<void(const IOProcessReadStopEventArgs&)> IOProcessReadStopEventHandler;

		typedef std::function<void(const IOProcessWriteStartEventArgs&)> IOProcessWriteStartEventHandler;
		typedef std::function<void(const IOProcessWriteStopEventArgs&)> IOProcessWriteStopEventHandler;

		typedef std::function<void(const TcpConnectEventArgs&)> TcpConnectEventHandler;
		typedef std::function<void(const TcpOnLineEventArgs&)> TcpOnLineEventHandler;
		typedef std::function<void(const TcpOffLineEventArgs&)> TcpOffLineEventHandler;
		typedef std::function<void(const TcpStartEventArgs&)> TcpStartEventHandler;
		typedef std::function<void(const TcpStopEventArgs&)> TcpSTopEventHandler;
		typedef std::function<void(const TcpReceiveEventArgs&)> TcpReceiveEventHandler;
		typedef std::function<void(const TcpSendEventArgs&)> TcpSendEventHandler;
		typedef std::function<void(const TcpSelectErrorEventArgs&)> TcpSelectErrorEventHandler;
	}
}

#endif // !SYSTEM_HCN_EVENTS_H
