///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef KAFKA_KAFKAPRODUCERDELIVERYREPORTCALLBACK_H
#define KAFKA_KAFKAPRODUCERDELIVERYREPORTCALLBACK_H

#include "Kafka/DllExport.h"

#include <librdkafka/rdkafkacpp.h>

namespace System
{
	namespace Kafka
	{
		class KAFKA_API KafkaProducerDeliveryReportCallBack : public RdKafka::DeliveryReportCb
		{
		public:
			void dr_cb(RdKafka::Message &message);
		};
	}
}

#endif
