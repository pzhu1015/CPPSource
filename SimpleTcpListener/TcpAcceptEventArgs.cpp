#include "SimpleTcpListener/TcpAcceptEventArgs.h"
#include "System/Net/TcpClient.h"

using namespace System::Net;

TcpAcceptEventArgs::TcpAcceptEventArgs(TcpClient * client)
{
	m_client = client;
}

TcpAcceptEventArgs::~TcpAcceptEventArgs()
{
}

System::Net::TcpClient * TcpAcceptEventArgs::GetClient() const
{
	return m_client;
}
