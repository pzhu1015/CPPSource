///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef Kafka_KafkaProducerEventCallBack_h
#define Kafka_KafkaProducerEventCallBack_h

#include "Kafka/DllExport.h"

#include <librdkafka/rdkafkacpp.h>

namespace System
{
	namespace Kafka
	{
		class KAFKA_API KafkaProducerEventCallBack : public RdKafka::EventCb
		{
		public:
			void event_cb(RdKafka::Event &event);
		};
	}
}

#endif