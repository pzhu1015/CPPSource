///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef KAFKA_KAFKAPRODUCER_H
#define KAFKA_KAFKAPRODUCER_H

#include "Kafka/DllExport.h"
#include "Kafka/KafkaProducerEventCallBack.h"
#include "Kafka/KafkaProducerDeliveryReportCallBack.h"

#include <librdkafka/rdkafkacpp.h>
#include <string>
#include <atomic>

namespace System
{
	namespace Kafka
	{
		class KAFKA_API KafkaProducer
		{
		public:
			KafkaProducer(const std::string &brokers, const std::string &topics, int partitions = 0);
			~KafkaProducer();
			bool Init();
			void Send(const std::string &msg);
			void Stop();
		private:
			RdKafka::Producer* m_producer = nullptr;
			RdKafka::Topic* m_topic = nullptr;
			KafkaProducerDeliveryReportCallBack m_producerDeliveryReportCallBack;
			KafkaProducerEventCallBack m_producerEventCallBack;
			std::string m_topics;
			std::string m_brokers;
			std::atomic<bool> m_run = false;
			int m_partitions = 0;
		};
	}
}
#endif
