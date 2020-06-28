///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "Kafka/CKafkaConsumer.h"

namespace System
{
	namespace Kafka
	{
		CKafkaConsumer::CKafkaConsumer()
			:
			m_kafka_handle(nullptr),
			m_kafka_topic(nullptr),
			m_kafka_conf(nullptr),
			m_kafka_topic_conf(nullptr),
			m_kafka_topic_partition_list(nullptr),
			m_kafka_queue(nullptr),
			m_consumer_callback(nullptr),
			m_consumer_callback_param(nullptr)
		{
		}

		CKafkaConsumer::~CKafkaConsumer()
		{
			rd_kafka_flush(m_kafka_handle, 10 * 1000); //wait for max 10 seconds

			rd_kafka_queue_destroy(m_kafka_queue);
			rd_kafka_topic_destroy(m_kafka_topic);
			rd_kafka_destroy(m_kafka_handle);
			rd_kafka_topic_partition_list_destroy(m_kafka_topic_partition_list);
		}
		int CKafkaConsumer::Init(char * topic, char * brokers, char * partitions, char * groupid, consumer_callback consumer_cb, void * param_cb)
		{
			int ret = 0;
			rd_kafka_conf_res_t ret_conf = RD_KAFKA_CONF_OK;
			char errstr[512] = { 0 };

			if (topic == NULL) { return -1; }
			if (brokers == NULL) { return -1; }
			if (groupid == NULL) { return -1; }

			m_consumer_callback = consumer_cb;
			m_consumer_callback_param = param_cb;

			m_kafka_conf = rd_kafka_conf_new();

			rd_kafka_conf_set_error_cb(m_kafka_conf, ErrorCb);
			rd_kafka_conf_set_throttle_cb(m_kafka_conf, ThrottleCb);
			rd_kafka_conf_set_offset_commit_cb(m_kafka_conf, OffsetCommitCb);
			rd_kafka_conf_set_stats_cb(m_kafka_conf, StatsCb);
			rd_kafka_conf_set_log_cb(m_kafka_conf, Logger);

			ret_conf = rd_kafka_conf_set(m_kafka_conf, "queued.min.messages", "1000000", errstr, sizeof(errstr));
			if (ret_conf != RD_KAFKA_CONF_OK) { printf("Error: rd_kafka_conf_set() failed 1; ret_conf=%d; errstr:%s\n", ret_conf, errstr); return -1; }

			ret_conf = rd_kafka_conf_set(m_kafka_conf, "session.timeout.ms", "6000", errstr, sizeof(errstr));
			if (ret_conf != RD_KAFKA_CONF_OK) { printf("Error: rd_kafka_conf_set() failed 2; ret_conf=%d; errstr:%s\n", ret_conf, errstr); return -1; }
			m_kafka_topic_conf = rd_kafka_topic_conf_new();

			ret_conf = rd_kafka_topic_conf_set(m_kafka_topic_conf, "auto.offset.reset", "earliest", errstr, sizeof(errstr));
			if (ret_conf != RD_KAFKA_CONF_OK) { printf("Error: rd_kafka_topic_conf_set() failed 4; ret_conf=%d; errstr:%s\n", ret_conf, errstr); return -1; }

			m_kafka_topic_partition_list = rd_kafka_topic_partition_list_new(1);
			int cnt = 0;
			int len = (int)strlen(partitions);
			char * pTemp = new char[len + 1];
			char * pTemp2 = pTemp;
			sprintf(pTemp, "%s", partitions);

			while (*pTemp != '\0')
			{
				char * s = strstr(pTemp, ",");
				if (s != NULL)
				{
					*s = '\0';
				}

				int partition = atoi(pTemp);
				rd_kafka_topic_partition_list_add(m_kafka_topic_partition_list, topic, partition);

				if (s != NULL)
				{
					pTemp = s + 1;
				}
				else
				{
					break;
				}
			}

			if (pTemp2) { delete[] pTemp2; pTemp2 = NULL; }

			m_kafka_handle = rd_kafka_new(RD_KAFKA_CONSUMER, m_kafka_conf, errstr, sizeof(errstr));

			if (m_kafka_handle == NULL)
			{
				printf("Error: Failed to create Kafka producer: %s\n", errstr);
				return -1;
			}

			rd_kafka_poll_set_consumer(m_kafka_handle);

			if (brokers && rd_kafka_brokers_add(m_kafka_handle, brokers) < 1)
			{
				printf("Error: No valid brokers specified\n");
				return -2;
			}

			int partition = m_kafka_topic_partition_list->elems[0].partition;
			int partition_cnt = m_kafka_topic_partition_list->cnt;

			m_kafka_topic = rd_kafka_topic_new(m_kafka_handle, topic, m_kafka_topic_conf);
			m_kafka_queue = rd_kafka_queue_new(m_kafka_handle);

			return ret;
		}
		int CKafkaConsumer::Read()
		{
			int ret = 0;

			char * topic = m_kafka_topic_partition_list->elems[0].topic;
			int partition = m_kafka_topic_partition_list->elems[0].partition;
			int partition_cnt = m_kafka_topic_partition_list->cnt;

			int64_t start_offset = RD_KAFKA_OFFSET_END;
			for (int i = 0; i < partition_cnt; i++)
			{
				int partition = m_kafka_topic_partition_list->elems[i].partition;

				int r = rd_kafka_consume_start_queue(m_kafka_topic, partition, start_offset, m_kafka_queue);

				if (r == -1)
				{
					printf("Error: creating queue: %s\n", rd_kafka_err2str(rd_kafka_last_error()));
					return -1;
				}
			}

			while (1)
			{
				int r = rd_kafka_consume_callback_queue(m_kafka_queue, 1000, MsgConsume, this); 
				if (r <= 0) { rd_kafka_poll(m_kafka_handle, 1000); continue; }

				rd_kafka_poll(m_kafka_handle, 0);
			}


			for (int i = 0; i < partition_cnt; i++)
			{
				int r = rd_kafka_consume_stop(m_kafka_topic, (int32_t)i);
				if (r == -1)
				{
					printf("Error: in consume_stop: %s\n", rd_kafka_err2str(rd_kafka_last_error()));
				}
			}

			return ret;
		}

		void CKafkaConsumer::ErrorCb(rd_kafka_t * rk, int err, const char * reason, void * opaque)
		{
			printf("%% ERROR CALLBACK: %s: %s: %s\n", rd_kafka_name(rk), rd_kafka_err2str((rd_kafka_resp_err_t)err), reason);

		}

		void CKafkaConsumer::ThrottleCb(rd_kafka_t * rk, const char * broker_name, int32_t broker_id, int throttle_time_ms, void * opaque)
		{
			printf("%% THROTTLED %dms by %s (%d)\n", throttle_time_ms, broker_name, broker_id);
		}

		void CKafkaConsumer::OffsetCommitCb(rd_kafka_t * rk, rd_kafka_resp_err_t err, rd_kafka_topic_partition_list_t * offsets, void * opaque)
		{
			int i;
			int verbosity = 1;

			if (err || verbosity >= 2)
			{
				printf("%% Offset commit of %d partition(s): %s\n", offsets->cnt, rd_kafka_err2str(err));
			}

			for (i = 0; i < offsets->cnt; i++)
			{
				rd_kafka_topic_partition_t * rktpar = &offsets->elems[i];

				if (rktpar->err || verbosity >= 2)
				{
					printf("%%  %s [%d] @ %lld: %s\n", rktpar->topic, rktpar->partition, rktpar->offset, rd_kafka_err2str(err));
				}
			}
		}

		int CKafkaConsumer::StatsCb(rd_kafka_t * rk, char * json, size_t json_len, void * opaque)
		{
			printf("%s\n", json);
			return 0;
		}

		void CKafkaConsumer::Logger(const rd_kafka_t * rk, int level, const char * fac, const char * buf)
		{
			fprintf(stdout, "RDKAFKA-%i-%s: %s: %s\n", level, fac, rd_kafka_name(rk), buf);
		}

		void CKafkaConsumer::MsgConsume(rd_kafka_message_t * rkmessage, void * opaque)
		{
			CKafkaConsumer * p = (CKafkaConsumer *)opaque;

			if (p && p->m_consumer_callback)
			{
				p->m_consumer_callback(rkmessage, p->m_consumer_callback_param);
				return;
			}

			if (rkmessage->err)
			{
				if (rkmessage->err == RD_KAFKA_RESP_ERR__PARTITION_EOF)
				{
					printf("[INFO] Consumer reached end of %s [%d] message queue at offset %lld\n", rd_kafka_topic_name(rkmessage->rkt), rkmessage->partition, rkmessage->offset);
					return;
				}

				printf("Error: Consume error for topic %s [%d] offset %lld: %s\n", rkmessage->rkt ? rd_kafka_topic_name(rkmessage->rkt) : "", rkmessage->partition, rkmessage->offset, rd_kafka_message_errstr(rkmessage));

				return;
			}

			if (rkmessage->key_len)
			{
				printf("Key: %d: %s\n", (int)rkmessage->key_len, (char *)rkmessage->key);
			}

			printf("%d: %s\n", (int)rkmessage->len, (char *)rkmessage->payload);
		}
	}
}