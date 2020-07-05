///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "SimpleTcpListener/OffLineEventArgs.h"
#include "System/Net/TcpClient.h"

using namespace System::Net;

OffLineEventArgs::OffLineEventArgs(System::Net::TcpClient * client)
{
	m_client = client;
}

OffLineEventArgs::~OffLineEventArgs()
{
}

System::Net::TcpClient * OffLineEventArgs::GetClient() const
{
	return m_client;
}
