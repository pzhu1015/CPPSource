///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/HCN/TcpOffLineEventArgs.h"
#include "System/Net/TcpClient.h"

namespace System
{
	namespace HCN
	{
		TcpOffLineEventArgs::TcpOffLineEventArgs(const TcpClientPtr& client, size_t total_clients)
		{
			m_client = client;
			m_total_clients = total_clients;
		}

		TcpOffLineEventArgs::~TcpOffLineEventArgs()
		{
		}

		TcpClientPtr TcpOffLineEventArgs::GetClient() const
		{
			return m_client;
		}
		size_t TcpOffLineEventArgs::GetTotalClient() const
		{
			return m_total_clients;
		}
	}
}
