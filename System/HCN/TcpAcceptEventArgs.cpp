///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/HCN/TcpAcceptEventArgs.h"
#include "System/Net/TcpClient.h"

namespace System
{
	namespace HCN
	{
		TcpAcceptEventArgs::TcpAcceptEventArgs(const TcpClientPtr &client)
		{
			m_client = client;
		}

		TcpAcceptEventArgs::~TcpAcceptEventArgs()
		{
		}

		TcpClientPtr TcpAcceptEventArgs::GetClient() const
		{
			return m_client;
		}
	}
}
