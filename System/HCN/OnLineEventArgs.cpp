///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/HCN/OnLineEventArgs.h"
#include "System/Net/TcpClient.h"

using namespace System::Net;
namespace System
{
	namespace HCN
	{
		OnLineEventArgs::OnLineEventArgs(const TcpClientPtr &client)
		{
			m_client = client;
		}

		OnLineEventArgs::~OnLineEventArgs()
		{
		}

		TcpClientPtr OnLineEventArgs::GetClient() const
		{
			return m_client;
		}
	}
}
