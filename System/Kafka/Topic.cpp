///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Kafka/Topic.h"
using std::move;
using std::string;
namespace System
{
	namespace Kafka
	{
		void dummy_deleter(rd_kafka_topic_t*) {

		}

		Topic Topic::make_non_owning(rd_kafka_topic_t* handle) {
			return Topic(handle, NonOwningTag{});
		}

		Topic::Topic()
			: handle_(nullptr, nullptr) {

		}

		Topic::Topic(rd_kafka_topic_t* handle)
			: handle_(handle, &rd_kafka_topic_destroy) {

		}

		Topic::Topic(rd_kafka_topic_t* handle, NonOwningTag)
			: handle_(handle, &dummy_deleter) {

		}

		string Topic::get_name() const {
			return rd_kafka_topic_name(handle_.get());
		}

		bool Topic::is_partition_available(int partition) const {
			return rd_kafka_topic_partition_available(handle_.get(), partition) == 1;
		}

		rd_kafka_topic_t* Topic::get_handle() const {
			return handle_.get();
		}

	}
}