#include "TcpStartEventArgs.h"

TcpStartEventArgs::TcpStartEventArgs(int port, int threads)
{
	m_port = port;
	m_threads = threads;
}

TcpStartEventArgs::~TcpStartEventArgs()
{
}

int TcpStartEventArgs::GetPort() const
{
	return m_port;
}

int TcpStartEventArgs::GetThreads() const
{
	return m_threads;
}
