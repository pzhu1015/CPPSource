///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef KAFKA_CKAFKAPRODUCER_H
#define KAFKA_CKAFKAPRODUCER_H

#include "Kafka/DllExport.h"
#include <librdkafka/rdkafka.h>

namespace System
{
	namespace Kafka
	{
		class KAFKA_API CKafkaProducer
		{
		public:
			CKafkaProducer();
			~CKafkaProducer();
			int Init(char* topic, char* brokers, int partitions);
			int Send(char* str, int len);
			static void ErrorCb(rd_kafka_t* rk, int err, const char* reason, void *opaque);
			static void ThrottleCb(rd_kafka_t* rk, const char* broker_name, int32_t broker_id, int throttle_time_ms, void *opaque);
			static void OffsetCommitCb(rd_kafka_t* rk, rd_kafka_resp_err_t err, rd_kafka_topic_partition_list_t *offsets, void *opaque);
			static int StatsCb(rd_kafka_t* rk, char* json, size_t json_len, void *opaque);

		private:
			rd_kafka_t* m_kafka_handle = nullptr;
			rd_kafka_topic_t* m_kafka_topic = nullptr;
			rd_kafka_conf_t* m_kafka_conf = nullptr;
			rd_kafka_topic_conf_t* m_kafka_topic_conf = nullptr;
			rd_kafka_topic_partition_list_t* m_kafka_topic_partition_list = nullptr;
			int m_partitions;
		};
	}
}

#endif // !KAFKA_CKAFKAPRODUCER_H
