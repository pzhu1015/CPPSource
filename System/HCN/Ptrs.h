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
		class Process;
		class ClientWrapper;
		typedef std::shared_ptr<ClientWrapper> ClientWrapperPtr;
		typedef std::shared_ptr<Process> ProcessPtr;
	}
}
#endif // !SYSTEM_HCN_PTRS_H
