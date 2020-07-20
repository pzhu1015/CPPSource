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
		TcpOffLineEventArgs::TcpOffLineEventArgs(const TcpClientPtr& client)
		{
			m_client = client;
		}

		TcpOffLineEventArgs::~TcpOffLineEventArgs()
		{
		}

		TcpClientPtr TcpOffLineEventArgs::GetClient() const
		{
			return m_client;
		}
	}
}
