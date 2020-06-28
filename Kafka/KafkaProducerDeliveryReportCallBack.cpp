///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "Kafka/KafkaProducerDeliveryReportCallBack.h"
#include <iostream>

namespace System
{
	namespace Kafka
	{
		void KafkaProducerDeliveryReportCallBack::dr_cb(RdKafka::Message & message)
		{
			std::cout << "Message delivery for ( " << message.len() << " bytes): " << message.errstr() << std::endl;
			if (message.key())
			{
				std::cout << "Key: " << *(message.key()) << ";" << std::endl;
			}
		}
	}
}
