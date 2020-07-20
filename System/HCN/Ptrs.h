///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_HCN_PTRS_H
#define SYSTEM_HCN_PTRS_H
#include <memory>
namespace System
{
	namespace HCN
	{
		class ClientProcess;
		class SelectTcpClient;
		typedef std::shared_ptr<SelectTcpClient> SelectTcpClientPtr;
		typedef std::shared_ptr<ClientProcess> ClientProcessPtr;
	}
}
#endif // !SYSTEM_HCN_PTRS_H
