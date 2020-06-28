///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef KAFKA_KAFKACONSUMER_H
#define KAFKA_KAFKACONSUMER_H

#include "Kafka/DllExport.h"
#include <librdkafka/rdkafkacpp.h>
#include <string>
#include <atomic>

namespace System
{
	namespace Kafka
	{
		class KAFKA_API KafkaConsumer
		{
		public:
			KafkaConsumer(const std::string &brokers, const std::string &topics, const std::string &groupid, int64_t offset = -1);
			~KafkaConsumer();

			bool Init();
			bool Consume(int timeout_ms);
			void Finalize();
		private:
			void Consumer(RdKafka::Message *message, void *opt);

			std::string m_brokers;
			std::string m_topics;
			std::string m_groupid;

			int64_t m_lastoffset = 0;
			RdKafka::Consumer* m_consumer = nullptr;
			RdKafka::Topic* m_topic = nullptr;
			int64_t m_offset = RdKafka::Topic::OFFSET_BEGINNING;
			int32_t m_partitions = 0;
			std::atomic<bool> m_run = true;
		};
	}
}


#endif // !KAFKA_KAFKACONSUMER_H
