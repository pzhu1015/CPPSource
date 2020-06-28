///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "Kafka/KafkaProducer.h"
#include <iostream>

namespace System
{
	namespace Kafka
	{
		KafkaProducer::KafkaProducer(const std::string & brokers, const std::string & topics, int partitions)
			:
			m_topics(topics),
			m_brokers(brokers),
			m_run(true),
			m_partitions(partitions)
		{
		}
		KafkaProducer::~KafkaProducer()
		{
			Stop();
		}
		bool KafkaProducer::Init()
		{
			std::string errstr = "";
			RdKafka::Conf *conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
			RdKafka::Conf *tconf = RdKafka::Conf::create(RdKafka::Conf::CONF_TOPIC);

			if (conf->set("metadata.broker.list", m_brokers, errstr) != RdKafka::Conf::CONF_OK)
			{
				std::cerr << "RdKafka conf set brokerlist failed : " << errstr.c_str() << std::endl;
			}
			
			conf->set("dr_cb", &m_producerDeliveryReportCallBack, errstr);
			conf->set("event_cb", &m_producerEventCallBack, errstr);

			m_producer = RdKafka::Producer::create(conf, errstr);
			if (!m_producer)
			{
				std::cerr << "Failed to create producer: " << errstr << std::endl;
				return false;
			}
			std::cout << "Created producer " << m_producer->name() << std::endl;

			m_topic = RdKafka::Topic::create(m_producer, m_topics, tconf, errstr);
			if (!m_topic)
			{
				std::cerr << "Failed to create topic: " << errstr << std::endl;
				return false;
			}
			return true;
		}
		void KafkaProducer::Send(const std::string & msg)
		{
			if (!m_run)
			{
				return;
			}
			RdKafka::ErrorCode resp = m_producer->produce(
				m_topic,
				m_partitions,
				RdKafka::Producer::RK_MSG_COPY,
				const_cast<char*> (msg.c_str()),
				msg.size(),
				NULL,
				NULL);
			if (resp != RdKafka::ERR_NO_ERROR)
			{
				std::cerr << "Producer failed: " << RdKafka::err2str(resp) << std::endl;
			}
			else
			{
				std::cerr << "Produced message (" << msg.size() << " bytes)" << std::endl;
			}

			m_producer->poll(0);

			while (m_run && m_producer->outq_len() > 0)
			{
				std::cerr << "Waiting for " << m_producer->outq_len() << std::endl;
				m_producer->poll(1000);
			}
		}
		void KafkaProducer::Stop()
		{
			if (m_topic)
			{
				delete m_topic;
			}
			if (m_producer)
			{
				delete m_producer;
			}
		}
	}
}