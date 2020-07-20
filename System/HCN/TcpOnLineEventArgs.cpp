///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/HCN/TcpOnLineEventArgs.h"
#include "System/Net/TcpClient.h"

using namespace System::Net;
namespace System
{
	namespace HCN
	{
		TcpOnLineEventArgs::TcpOnLineEventArgs(const TcpClientPtr &client)
		{
			m_client = client;
		}

		TcpOnLineEventArgs::~TcpOnLineEventArgs()
		{
		}

		TcpClientPtr TcpOnLineEventArgs::GetClient() const
		{
			return m_client;
		}
	}
}
