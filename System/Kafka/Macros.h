///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_KAFKA_MACROS_H
#define SYSTEM_KAFKA_MACROS_H
namespace System
{
	namespace Kafka
	{
#define RD_KAFKA_QUEUE_REFCOUNT_BUG_VERSION 0x000b0500 //v0.11.5.00
#define RD_KAFKA_HEADERS_SUPPORT_VERSION 0x000b0402 //v0.11.4.02
#define RD_KAFKA_ADMIN_API_SUPPORT_VERSION 0x000b0500 //v0.11.5.00
#define RD_KAFKA_MESSAGE_LATENCY_SUPPORT_VERSION 0x000b0000 //v0.11.0.00
#define RD_KAFKA_EVENT_STATS_SUPPORT_VERSION 0x000b0000 //v0.11.0.00
#define RD_KAFKA_MESSAGE_STATUS_SUPPORT_VERSION 0x01000002 //v1.0.0.02
#define RD_KAFKA_STORE_OFFSETS_SUPPORT_VERSION 0x00090501 //v0.9.5.01
#define RD_KAFKA_DESTROY_FLAGS_SUPPORT_VERSION 0x000b0600 //v0.11.6
	}
}
#endif // !SYSTEM_KAFKA_MACROS_H
