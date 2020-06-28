///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "Kafka/KafkaConsumer.h"

#include <iostream>

namespace System
{
	namespace Kafka
	{
		KafkaConsumer::KafkaConsumer(const std::string & brokers, const std::string & topics, const std::string & groupid, int64_t offset)
			:
			m_brokers(brokers),
			m_topics(topics),
			m_groupid(groupid),
			m_offset(offset)
		{
		}

		KafkaConsumer::~KafkaConsumer()
		{
		}

		bool KafkaConsumer::Init()
		{
			RdKafka::Conf *conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
			if (!conf)
			{
				fprintf(stderr, "RdKafka create global conf failed\n");
				return false;
			}

			std::string errstr;
			if (conf->set("bootstrap.servers", m_brokers, errstr) != RdKafka::Conf::CONF_OK)
			{
				fprintf(stderr, "RdKafka conf set brokerlist failed: %s\n", errstr.c_str());
			}

			if (conf->set("group.id", m_groupid, errstr) != RdKafka::Conf::CONF_OK)
			{
				fprintf(stderr, "RdKafka conf set group.id failed: %s\n", errstr.c_str());
			}

			std::string strfetch_num = "10240000";
			if (conf->set("max.partition.fetch.bytes", strfetch_num, errstr) != RdKafka::Conf::CONF_OK) {
				fprintf(stderr, "RdKafka conf set max.partition failed : %s\n", errstr.c_str());
			}

			m_consumer = RdKafka::Consumer::create(conf, errstr);
			if (!m_consumer)
			{
				fprintf(stderr, "failed to create consumer\n");
			}
			delete conf;
			RdKafka::Conf* tconf = nullptr;

			tconf = RdKafka::Conf::create(RdKafka::Conf::CONF_TOPIC);
			if (!tconf)
			{
				fprintf(stderr, "RdKafka create topic conf failed\n");
				return false;
			}

			if (tconf->set("auto.offset.reset", "smallest", errstr) != RdKafka::Conf::CONF_OK) {
				fprintf(stderr, "RdKafka conf set auto.offset.reset failed : %s\n", errstr.c_str());
			}

			m_topic = RdKafka::Topic::create(m_consumer, m_topics, tconf, errstr);
			if (!m_topic) {
				fprintf(stderr, "RdKafka create topic failed : %s\n", errstr.c_str());
			}
			delete tconf;

			RdKafka::ErrorCode resp = m_consumer->start(m_topic, m_partitions, m_offset);
			if (resp != RdKafka::ERR_NO_ERROR) {
				fprintf(stderr, "failed to start consumer : %s\n", RdKafka::err2str(resp).c_str());
			}

			return true;
		}

		bool KafkaConsumer::Consume(int timeout_ms)
		{
			RdKafka::Message *msg = nullptr;

			while (m_run) {
				msg = m_consumer->consume(m_topic, m_partitions, timeout_ms);
				Consumer(msg, nullptr);
				m_consumer->poll(0);
				delete msg;
			}

			m_consumer->stop(m_topic, m_partitions);
			if (m_topic) {
				delete m_topic;
				m_topic = nullptr;
			}
			if (m_consumer) {
				delete m_consumer;
				m_consumer = nullptr;
			}

			RdKafka::wait_destroyed(5000);
			return true;
		}

		void KafkaConsumer::Finalize()
		{
		}

		void KafkaConsumer::Consumer(RdKafka::Message * message, void * opt)
		{
			switch (message->err()) {
			case RdKafka::ERR__TIMED_OUT:
				break;
			case RdKafka::ERR_NO_ERROR:
				printf("%.*s\n",
					static_cast<int>(message->len()),
					static_cast <const char*>(message->payload()));
				m_lastoffset = message->offset();

				break;
			case RdKafka::ERR__PARTITION_EOF:
				std::cerr << "%% Reached the end of the queue, offset: " << m_lastoffset << std::endl;
				break;
			case RdKafka::ERR__UNKNOWN_TOPIC:
			case RdKafka::ERR__UNKNOWN_PARTITION:
				std::cerr << "Consume failed: " << message->errstr() << std::endl;
				m_run = false;
				break;
			default:
				std::cerr << "Consume failed: " << message->errstr() << std::endl;
				m_run = false;
				break;
			}
		}
	}
}