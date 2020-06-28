///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef KAFKA_CKAFKACONSUMER_H
#define KAFKA_CKAFKACONSUMER_H

#include "Kafka/DllExport.h"
#include <librdkafka/rdkafka.h>

namespace System
{
	namespace Kafka
	{
		typedef void(*consumer_callback)(rd_kafka_message_t* rkmessage, void *opaque);
		class KAFKA_API CKafkaConsumer
		{
		public:
			CKafkaConsumer();
			~CKafkaConsumer();
			int Init(char* topic, char* brokers, char* partitions, char* groupid, consumer_callback consumer_cb, void* param_cb);
			int Read();
			static void ErrorCb(rd_kafka_t* rk, int err, const char* reason, void *opaque);
			static void ThrottleCb(rd_kafka_t* rk, const char* broker_name, int32_t broker_id, int throttle_time_ms, void *opaque);
			static void OffsetCommitCb(rd_kafka_t *rk, rd_kafka_resp_err_t err, rd_kafka_topic_partition_list_t *offsets, void *opaque);
			static int StatsCb(rd_kafka_t *rk, char *json, size_t json_len, void *opaque);
			static void Logger(const rd_kafka_t *rk, int level, const char *fac, const char *buf);
			static void MsgConsume(rd_kafka_message_t *rkmessage, void *opaque);
		private:
			rd_kafka_t *                         m_kafka_handle;
			rd_kafka_topic_t *                   m_kafka_topic;
			rd_kafka_conf_t *                    m_kafka_conf;
			rd_kafka_topic_conf_t *              m_kafka_topic_conf;
			rd_kafka_topic_partition_list_t *    m_kafka_topic_partition_list;
			rd_kafka_queue_t *                   m_kafka_queue;
			consumer_callback                    m_consumer_callback;
			void *                               m_consumer_callback_param;
		};
	}
}
#endif // !KAFKA_CKAFKACONSUMER_H
