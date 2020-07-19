///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/HCN/OffLineEventArgs.h"
#include "System/Net/TcpClient.h"

using namespace System::Net;
namespace System
{
	namespace HCN
	{
		OffLineEventArgs::OffLineEventArgs(TcpClient * client)
		{
			m_client = client;
		}

		OffLineEventArgs::~OffLineEventArgs()
		{
		}

		TcpClient * OffLineEventArgs::GetClient() const
		{
			return m_client;
		}
	}
}
