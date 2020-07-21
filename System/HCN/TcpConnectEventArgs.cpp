///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/HCN/TcpConnectEventArgs.h"
namespace System
{
	namespace HCN
	{
		TcpConnectEventArgs::TcpConnectEventArgs(const TcpClientPtr & client)
		{
			m_client = client;
		}
		TcpConnectEventArgs::~TcpConnectEventArgs()
		{
		}
		TcpClientPtr TcpConnectEventArgs::GetClient() const
		{
			return m_client;
		}
	}
}