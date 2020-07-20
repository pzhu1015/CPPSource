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
		TcpReceiveEventArgs::TcpReceiveEventArgs(const TcpClientPtr & client, Msg * msg)
		{
			m_client = client;
			m_msg = msg;
		}
		TcpReceiveEventArgs::~TcpReceiveEventArgs()
		{
		}
	}
}