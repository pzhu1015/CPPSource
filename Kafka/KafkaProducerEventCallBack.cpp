///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "Kafka/KafkaProducerEventCallBack.h"
#include <iostream>

namespace System
{
	namespace Kafka
	{
		void KafkaProducerEventCallBack::event_cb(RdKafka::Event & event)
		{
			switch (event.type())
			{
			case RdKafka::Event::EVENT_ERROR:
				std::cerr << "ERROR (" << RdKafka::err2str(event.err()) << "): " << event.str() << std::endl;
				if (event.err() == RdKafka::ERR__ALL_BROKERS_DOWN)
				{
					break;
				}
			case RdKafka::Event::EVENT_STATS:
				std::cerr << "STATS: " << event.str() << std::endl;
				break;
			case RdKafka::Event::EVENT_LOG:
				fprintf(stderr, "LOG-%i-%s: %s\n", event.severity(), event.fac().c_str(), event.str().c_str());
				break;
			default:
				std::cerr << "Event " << event.type() << " (" << RdKafka::err2str(event.err()) << "): " << event.str() << std::endl;
				break;
			}
		}
	}
}

