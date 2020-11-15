///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_KAFKA_PTRS_H
#define SYSTEM_KAFKA_PTRS_H
#include "System/Kafka/BufferedProducer.h"
#include <memory>
namespace System
{
	namespace Kafka
	{
		class Consumer;
		class Producer;
		class MessageBuilder;
		typedef std::shared_ptr<Consumer> ConsumerPtr;
		typedef std::shared_ptr<Producer> ProducerPtr;
		typedef std::shared_ptr<MessageBuilder> MessageBuilderPtr;
		typedef std::shared_ptr <BufferedProducer<std::string>> BufferedProducerPtr;
	}
}
#endif // !SYSTEM_KAFKA_PTRS_H
