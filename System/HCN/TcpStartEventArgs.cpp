///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/HCN/TcpStartEventArgs.h"

namespace System
{
	namespace HCN
	{

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
	}
}
