///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Kafka/MessageTimestamp.h"
using std::chrono::milliseconds;
namespace System
{
	namespace Kafka
	{
		MessageTimestamp::MessageTimestamp(milliseconds timestamp, TimestampType type)
			: timestamp_(timestamp),
			type_(type) {

		}

		milliseconds MessageTimestamp::get_timestamp() const {
			return timestamp_;
		}

		MessageTimestamp::TimestampType MessageTimestamp::get_type() const {
			return type_;
		}

	}
}