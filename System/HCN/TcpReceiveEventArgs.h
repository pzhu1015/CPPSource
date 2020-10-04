///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_HCN_TCPRECEIVEEVENTARGS_H
#define SYSTEM_HCN_TCPRECEIVEEVENTARGS_H
#include "System/Base/EventArgs.h"
#include "System/HCN/Ptrs.h"
#include "System/HCN/Msg.h"

namespace System
{
	namespace HCN
	{
		class SYSTEM_API TcpReceiveEventArgs final : public EventArgs
		{
		public:
			TcpReceiveEventArgs();
			TcpReceiveEventArgs(const TcpClientChannelPtr &client, Msg* msg);
			virtual ~TcpReceiveEventArgs();
			TcpClientChannelPtr& GetChannel();
			Msg* GetMsg() const;

			void SetChannel(const TcpClientChannelPtr &client);
			void SetMsg(Msg* msg);
		private:
			TcpClientChannelPtr m_channel = nullptr;
			Msg* m_msg = nullptr;
		};
	}
}
#endif // !SYSTEM_HCN_TCPRECEIVEEVENTARGS_H
