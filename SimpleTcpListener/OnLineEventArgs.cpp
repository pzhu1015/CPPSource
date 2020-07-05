///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "SimpleTcpListener/OnLineEventArgs.h"
#include "System/Net/TcpClient.h"

using namespace System::Net;

OnLineEventArgs::OnLineEventArgs(System::Net::TcpClient * client)
{
	m_client = client;
}

OnLineEventArgs::~OnLineEventArgs()
{
}

System::Net::TcpClient * OnLineEventArgs::GetClient() const
{
	return m_client;
}
