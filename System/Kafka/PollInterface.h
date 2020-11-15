///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_KAFKA_POLLINTERFACE_H
#define SYSTEM_KAFKA_POLLINTERFACE_H
#include "System/Kafka/Consumer.h"
namespace System
{
	namespace Kafka
	{
		/**
		* \interface PollInterface
		*
		* \brief Interface defining polling methods for the Consumer class
		*/
		struct PollInterface {
			virtual ~PollInterface() = default;

			/**
			* \brief Get the underlying consumer controlled by this strategy
			*
			* \return A reference to the consumer instance
			*/
			virtual Consumer& get_consumer() = 0;

			/**
			* \brief Sets the timeout for polling functions
			*
			* This calls Consumer::set_timeout
			*
			* \param timeout The timeout to be set
			*/
			virtual void set_timeout(std::chrono::milliseconds timeout) = 0;

			/**
			* \brief Gets the timeout for polling functions
			*
			* This calls Consumer::get_timeout
			*
			* \return The timeout
			*/
			virtual std::chrono::milliseconds get_timeout() = 0;

			/**
			* \brief Polls all assigned partitions for new messages in round-robin fashion
			*
			* Each call to poll() will first consume from the global event queue and if there are
			* no pending events, will attempt to consume from all partitions until a valid message is found.
			* The timeout used on this call will be the one configured via PollInterface::set_timeout.
			*
			* \return A message. The returned message *might* be empty. It's necessary to check
			* that it's a valid one before using it (see example above).
			*
			* \remark You need to call poll() or poll_batch() periodically as a keep alive mechanism,
			* otherwise the broker will think this consumer is down and will trigger a rebalance
			* (if using dynamic subscription)
			*/
			virtual Message poll() = 0;

			/**
			* \brief Polls for new messages
			*
			* Same as the other overload of PollInterface::poll but the provided
			* timeout will be used instead of the one configured on this Consumer.
			*
			* \param timeout The timeout to be used on this call
			*/
			virtual Message poll(std::chrono::milliseconds timeout) = 0;

			/**
			* \brief Polls all assigned partitions for a batch of new messages in round-robin fashion
			*
			* Each call to poll_batch() will first attempt to consume from the global event queue
			* and if the maximum batch number has not yet been filled, will attempt to fill it by
			* reading the remaining messages from each partition.
			*
			* \param max_batch_size The maximum amount of messages expected
			*
			* \return A list of messages
			*
			* \remark You need to call poll() or poll_batch() periodically as a keep alive mechanism,
			* otherwise the broker will think this consumer is down and will trigger a rebalance
			* (if using dynamic subscription)
			*/
			virtual std::vector<Message> poll_batch(size_t max_batch_size) = 0;

			/**
			* \brief Polls all assigned partitions for a batch of new messages in round-robin fashion
			*
			* Same as the other overload of PollInterface::poll_batch but the provided
			* timeout will be used instead of the one configured on this Consumer.
			*
			* \param max_batch_size The maximum amount of messages expected
			*
			* \param timeout The timeout for this operation
			*
			* \return A list of messages
			*/
			virtual std::vector<Message> poll_batch(size_t max_batch_size, std::chrono::milliseconds timeout) = 0;
		};

	}
}
#endif // !SYSTEM_KAFKA_POLLINTERFACE_H
