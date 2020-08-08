///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_HCN_PTRS_H
#define SYSTEM_HCN_PTRS_H
#include <memory>
namespace System
{
	namespace HCN
	{
		class IOProcess;
		class TcpClientChannel;
		class TcpListenerChannel;
		typedef std::shared_ptr<TcpClientChannel> TcpClientChannelPtr;
		typedef std::shared_ptr<TcpListenerChannel> TcpListenerChannelPtr;
		typedef std::shared_ptr<IOProcess> IOProcessPtr;
	}
}
#endif // !SYSTEM_HCN_PTRS_H
