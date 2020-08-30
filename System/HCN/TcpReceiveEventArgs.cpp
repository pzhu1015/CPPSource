///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/HCN/TcpReceiveEventArgs.h"
#include "System/HCN/TcpClientChannel.h"
namespace System
{
	namespace HCN
	{
		TcpReceiveEventArgs::TcpReceiveEventArgs()
		{
		}
		TcpReceiveEventArgs::TcpReceiveEventArgs(const TcpClientChannelPtr & channel, Msg * msg)
		{
			m_channel = channel;
			m_msg = msg;
		}
		TcpReceiveEventArgs::~TcpReceiveEventArgs()
		{
		}
		TcpClientChannelPtr& TcpReceiveEventArgs::GetChannel()
		{
			return m_channel;
		}
		Msg * TcpReceiveEventArgs::GetMsg() const
		{
			return m_msg;
		}
		void TcpReceiveEventArgs::SetChannel(const TcpClientChannelPtr & channel)
		{
			m_channel = channel;
		}
		void TcpReceiveEventArgs::SetMsg(Msg * msg)
		{
			msg = msg;
		}
	}
}