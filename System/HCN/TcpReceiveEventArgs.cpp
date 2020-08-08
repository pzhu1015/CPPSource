///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/HCN/TcpReceiveEventArgs.h"
namespace System
{
	namespace HCN
	{
		TcpReceiveEventArgs::TcpReceiveEventArgs()
		{
		}
		TcpReceiveEventArgs::TcpReceiveEventArgs(const TcpClientPtr & client, Msg * msg)
		{
			m_client = client;
			m_msg = msg;
		}
		TcpReceiveEventArgs::~TcpReceiveEventArgs()
		{
		}
		TcpClientPtr TcpReceiveEventArgs::GetClient() const
		{
			return m_client;
		}
		Msg * TcpReceiveEventArgs::GetMsg() const
		{
			return m_msg;
		}
		void TcpReceiveEventArgs::SetClient(const TcpClientPtr & client)
		{
			m_client = client;
		}
		void TcpReceiveEventArgs::SetMsg(Msg * msg)
		{
			msg = msg;
		}
	}
}