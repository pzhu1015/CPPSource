///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_HCN_SELECTIOPROCESS_H
#define SYSTEM_HCN_SELECTIOPROCESS_H
#include "System/DllExport.h"
#include "System/HCN/IOProcess.h"
#include <atomic>
namespace System
{
	namespace HCN
	{
		class SYSTEM_API SelectIOProcess : public IOProcess
		{
		public:
			SelectIOProcess();
			virtual ~SelectIOProcess();
			virtual void AddClient(const TcpClientChannelPtr& client);
		protected:
			virtual void IOReadHandle();
			virtual void IOWriteHandle();
		private:
			std::atomic<bool> m_change = false;
			fd_set m_check_read_back;
			fd_set m_check_write_back;
		};
	}
}
#endif // !SYSTEM_HCN_SELECTIOPROCESS_H
