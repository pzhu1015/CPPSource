///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Kafka/Producer.h"
#include "System/Kafka/Exceptions.h"
#include "System/Kafka/MessageInternal.h"
#include "System/Kafka/Message.h"
#include "System/nonstd/optional.hpp"
#include <errno.h>
#include <memory>

using std::move;
using std::string;
using std::chrono::milliseconds;
using std::unique_ptr;
using std::get;
namespace System
{
	namespace Kafka
	{
		Producer::Producer(Config config)
			: KafkaHandleBase(move(config)), message_payload_policy_(PayloadPolicy::COPY_PAYLOAD) {
			char error_buffer[512];
			auto config_handle = get_configuration().get_handle();
			rd_kafka_conf_set_opaque(config_handle, this);
			rd_kafka_t* ptr = rd_kafka_new(RD_KAFKA_PRODUCER,
				rd_kafka_conf_dup(config_handle),
				error_buffer, sizeof(error_buffer));
			if (!ptr) {
				throw Exception("Failed to create producer handle: " + string(error_buffer));
			}
			set_handle(ptr);
		}

		void Producer::set_payload_policy(PayloadPolicy policy) {
			message_payload_policy_ = policy;
		}

		Producer::PayloadPolicy Producer::get_payload_policy() const {
			return message_payload_policy_;
		}

#if (RD_KAFKA_VERSION >= RD_KAFKA_HEADERS_SUPPORT_VERSION)

		void Producer::produce(const MessageBuilder& builder) {
			do_produce(builder, MessageBuilder::HeaderListType(builder.header_list())); //copy headers
		}

		void Producer::produce(MessageBuilder&& builder) {
			do_produce(builder, std::move(builder.header_list())); //move headers
		}

		void Producer::produce(const Message& message) {
			do_produce(message, HeaderList<Message::HeaderType>(message.get_header_list())); //copy headers
		}

		void Producer::produce(Message&& message) {
			do_produce(message, message.detach_header_list<Message::HeaderType>()); //move headers
		}

#else

		void Producer::produce(const MessageBuilder& builder) {
			do_produce(builder);
		}

		void Producer::produce(MessageBuilder&& builder) {
			do_produce(builder);
		}

		void Producer::produce(const Message& message) {
			do_produce(message);
		}

		void Producer::produce(Message&& message) {
			do_produce(message);
		}

#endif

		int Producer::poll() {
			return poll(get_timeout());
		}

		int Producer::poll(milliseconds timeout) {
			return rd_kafka_poll(get_handle(), static_cast<int>(timeout.count()));
		}

		void Producer::flush() {
			flush(get_timeout());
		}

		void Producer::flush(milliseconds timeout) {
			auto result = rd_kafka_flush(get_handle(), static_cast<int>(timeout.count()));
			check_error(result);
		}

#if (RD_KAFKA_VERSION >= RD_KAFKA_HEADERS_SUPPORT_VERSION)

		void Producer::do_produce(const MessageBuilder& builder,
			MessageBuilder::HeaderListType&& headers) {
			const Buffer& payload = builder.payload();
			const Buffer& key = builder.key();
			const int policy = static_cast<int>(message_payload_policy_);
			auto result = rd_kafka_producev(get_handle(),
				RD_KAFKA_V_TOPIC(builder.topic().data()),
				RD_KAFKA_V_PARTITION(builder.partition()),
				RD_KAFKA_V_MSGFLAGS(policy),
				RD_KAFKA_V_TIMESTAMP(builder.timestamp().count()),
				RD_KAFKA_V_KEY((void*)key.get_data(), key.get_size()),
				RD_KAFKA_V_HEADERS(headers.release_handle()), //pass ownership to rdkafka
				RD_KAFKA_V_VALUE((void*)payload.get_data(), payload.get_size()),
				RD_KAFKA_V_OPAQUE(builder.user_data()),
				RD_KAFKA_V_END);
			check_error(result);
		}

		void Producer::do_produce(const Message& message,
			MessageBuilder::HeaderListType&& headers) {
			const Buffer& payload = message.get_payload();
			const Buffer& key = message.get_key();
			const int policy = static_cast<int>(message_payload_policy_);
			int64_t duration = message.get_timestamp() ? message.get_timestamp()->get_timestamp().count() : 0;
			auto result = rd_kafka_producev(get_handle(),
				RD_KAFKA_V_TOPIC(message.get_topic().data()),
				RD_KAFKA_V_PARTITION(message.get_partition()),
				RD_KAFKA_V_MSGFLAGS(policy),
				RD_KAFKA_V_TIMESTAMP(duration),
				RD_KAFKA_V_KEY((void*)key.get_data(), key.get_size()),
				RD_KAFKA_V_HEADERS(headers.release_handle()), //pass ownership to rdkafka
				RD_KAFKA_V_VALUE((void*)payload.get_data(), payload.get_size()),
				RD_KAFKA_V_OPAQUE(message.get_user_data()),
				RD_KAFKA_V_END);
			check_error(result);
		}

#else

		void Producer::do_produce(const MessageBuilder& builder) {
			const Buffer& payload = builder.payload();
			const Buffer& key = builder.key();
			const int policy = static_cast<int>(message_payload_policy_);
			auto result = rd_kafka_producev(get_handle(),
				RD_KAFKA_V_TOPIC(builder.topic().data()),
				RD_KAFKA_V_PARTITION(builder.partition()),
				RD_KAFKA_V_MSGFLAGS(policy),
				RD_KAFKA_V_TIMESTAMP(builder.timestamp().count()),
				RD_KAFKA_V_KEY((void*)key.get_data(), key.get_size()),
				RD_KAFKA_V_VALUE((void*)payload.get_data(), payload.get_size()),
				RD_KAFKA_V_OPAQUE(builder.user_data()),
				RD_KAFKA_V_END);
			check_error(result);
		}

		void Producer::do_produce(const Message& message) {
			const Buffer& payload = message.get_payload();
			const Buffer& key = message.get_key();
			const int policy = static_cast<int>(message_payload_policy_);
			int64_t duration = message.get_timestamp() ? message.get_timestamp().get().get_timestamp().count() : 0;
			auto result = rd_kafka_producev(get_handle(),
				RD_KAFKA_V_TOPIC(message.get_topic().data()),
				RD_KAFKA_V_PARTITION(message.get_partition()),
				RD_KAFKA_V_MSGFLAGS(policy),
				RD_KAFKA_V_TIMESTAMP(duration),
				RD_KAFKA_V_KEY((void*)key.get_data(), key.get_size()),
				RD_KAFKA_V_VALUE((void*)payload.get_data(), payload.get_size()),
				RD_KAFKA_V_OPAQUE(message.get_user_data()),
				RD_KAFKA_V_END);
			check_error(result);
		}

#endif //RD_KAFKA_HEADERS_SUPPORT_VERSION

	}
}