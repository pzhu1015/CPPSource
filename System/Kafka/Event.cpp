///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Kafka/Event.h"

using std::allocator;
using std::string;
using std::unique_ptr;
using std::vector;
namespace System
{
	namespace Kafka
	{

		Event::Event(rd_kafka_event_t* handle)
			: handle_(handle, &rd_kafka_event_destroy) {

		}

		string Event::get_name() const {
			return rd_kafka_event_name(handle_.get());
		}

		rd_kafka_event_type_t Event::get_type() const {
			return rd_kafka_event_type(handle_.get());
		}

		Message Event::get_next_message() const {
			// Note: the constness in rd_kafka_event_message_next's return value is not needed and it
			// breaks Message's interface. This is dirty but it looks like it should have no side effects.
			const auto message =
				const_cast<rd_kafka_message_t*>(rd_kafka_event_message_next(handle_.get()));
			return Message::make_non_owning(message);
		}

		vector<Message> Event::get_messages() {
			return get_messages(allocator<Message>());
		}

		size_t Event::get_message_count() const {
			return rd_kafka_event_message_count(handle_.get());
		}

		Error Event::get_error() const {
			return rd_kafka_event_error(handle_.get());
		}

		void* Event::get_opaque() const {
			return rd_kafka_event_opaque(handle_.get());
		}

		TopicPartition Event::get_topic_partition() const {
			using TopparHandle = unique_ptr<rd_kafka_topic_partition_t,
				decltype(&rd_kafka_topic_partition_destroy)>;
			TopparHandle toppar_handle{ rd_kafka_event_topic_partition(handle_.get()),
				&rd_kafka_topic_partition_destroy };
			return TopicPartition(toppar_handle->topic, toppar_handle->partition, toppar_handle->offset);
		}

		TopicPartitionList Event::get_topic_partition_list() const {
			auto toppars_handle = rd_kafka_event_topic_partition_list(handle_.get());
			return convert(toppars_handle);
		}

		Event::operator bool() const {
			return !!handle_;
		}

	}
}