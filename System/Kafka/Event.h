///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_KAFKA_EVENT_H
#define SYSTEM_KAFKA_EVENT_H
#include "System/Kafka/Error.h"
#include "System/Kafka/TopicPartition.h"
#include "System/Kafka/TopicPartitionList.h"
#include "System/Kafka/Message.h"
#include <memory>
#include <string>
#include <vector>
namespace System
{
	namespace Kafka
	{
		class Event {
		public:
			/**
			* Construct an Event from a rdkafka event handle and take ownership of it
			*
			* /param handle The handle to construct this event from
			*/
			Event(rd_kafka_event_t* handle);

			/**
			* Returns the name of this event
			*/
			std::string get_name() const;

			/**
			* Returns the type of this event
			*/
			rd_kafka_event_type_t get_type() const;

			/**
			* \brief Gets the next message contained in this event.
			*
			* This call is only valid if the event type is one of:
			* * RD_KAFKA_EVENT_FETCH
			* * RD_KAFKA_EVENT_DR
			*
			* \note The returned message's lifetime *is tied to this Event*. That is, if the event
			* is free'd so will the contents of the message.
			*/
			Message get_next_message() const;

			/**
			* \brief Gets all messages in this event (if any)
			*
			* This call is only valid if the event type is one of:
			* * RD_KAFKA_EVENT_FETCH
			* * RD_KAFKA_EVENT_DR
			*
			* \note The returned messages' lifetime *is tied to this Event*. That is, if the event
			* is free'd so will the contents of the messages.
			*
			* \return A vector containing 0 or more messages
			*/
			std::vector<Message> get_messages();

			/**
			* \brief Gets all messages in this event (if any)
			*
			* This call is only valid if the event type is one of:
			* * RD_KAFKA_EVENT_FETCH
			* * RD_KAFKA_EVENT_DR
			*
			* \param allocator The allocator to use on the output vector
			*
			* \note The returned messages' lifetime *is tied to this Event*. That is, if the event
			* is free'd so will the contents of the messages.
			*
			* \return A vector containing 0 or more messages
			*/
			template <typename Allocator>
			std::vector<Message, Allocator> get_messages(const Allocator allocator);

			/**
			* \brief Gets the number of messages contained in this event
			*
			* This call is only valid if the event type is one of:
			* * RD_KAFKA_EVENT_FETCH
			* * RD_KAFKA_EVENT_DR
			*/
			size_t get_message_count() const;

			/**
			* \brief Returns the error in this event
			*/
			Error get_error() const;

			/**
			* Gets the opaque pointer in this event
			*/
			void* get_opaque() const;

#if RD_KAFKA_VERSION >= RD_KAFKA_EVENT_STATS_SUPPORT_VERSION
			/**
			* \brief Gets the stats in this event
			*
			* This call is only valid if the event type is RD_KAFKA_EVENT_STATS
			*/
			std::string get_stats() const {
				return rd_kafka_event_stats(handle_.get());
			}
#endif

			/**
			* \brief Gets the topic/partition for this event
			*
			* This call is only valid if the event type is RD_KAFKA_EVENT_ERROR
			*/
			TopicPartition get_topic_partition() const;

			/**
			* \brief Gets the list of topic/partitions in this event
			*
			* This call is only valid if the event type is one of:
			* * RD_KAFKA_EVENT_REBALANCE
			* * RD_KAFKA_EVENT_OFFSET_COMMIT
			*/
			TopicPartitionList get_topic_partition_list() const;

			/**
			* Check whether this event is valid
			*
			* /return true iff this event has a valid (non-null) handle inside
			*/
			operator bool() const;
		private:
			using HandlePtr = std::unique_ptr<rd_kafka_event_t, decltype(&rd_kafka_event_destroy)>;

			HandlePtr handle_;
		};

		template <typename Allocator>
		std::vector<Message, Allocator> Event::get_messages(const Allocator allocator) {
			const size_t total_messages = get_message_count();
			std::vector<const rd_kafka_message_t*> raw_messages(total_messages);
			const auto messages_read = rd_kafka_event_message_array(handle_.get(),
				raw_messages.data(),
				total_messages);
			std::vector<Message, Allocator> output(allocator);
			output.reserve(messages_read);
			for (auto message : raw_messages) {
				output.emplace_back(Message::make_non_owning(const_cast<rd_kafka_message_t*>(message)));
			}
			return output;
		}
	}
}
#endif // !SYSTEM_KAFKA_EVENT_H
