///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_KAFKA_ROUNDROBINPOLLSTRATEGY_H
#define SYSTEM_KAFKA_ROUNDROBINPOLLSTRATEGY_H
#include "System/Kafka/Exceptions.h"
#include "System/Kafka/Consumer.h"
#include "System/Kafka/Queue.h"
#include "System/Kafka/PollStrategyBase.h"
#include <map>
#include <string>
namespace System
{
	namespace Kafka
	{
		/**
		* \brief This adapter changes the default polling strategy of the Consumer into a fair round-robin
		*        polling mechanism.
		*
		* The default librdkafka (and cppkafka) poll() and poll_batch() behavior is to consume batches of
		* messages from each partition in turn. For performance reasons, librdkafka pre-fetches batches
		* of messages from the kafka broker (one batch from each partition), and stores them locally in
		* partition queues. Since all the internal partition queues are forwarded by default unto the
		* group consumer queue (one per consumer), these batches end up being polled and consumed in the
		* same sequence order.
		* This adapter allows fair round-robin polling of all assigned partitions, one message at a time
		* (or one batch at a time if poll_batch() is used). Note that poll_batch() has nothing to do with
		* the internal batching mechanism of librdkafka.
		*
		* Example code on how to use this:
		*
		* \code
		* // Create a consumer
		* Consumer consumer(...);
		* consumer.subscribe({ "my_topic" });
		*
		* // Optionally set the callbacks. This must be done *BEFORE* creating the strategy adapter
		* consumer.set_assignment_callback(...);
		* consumer.set_revocation_callback(...);
		* consumer.set_rebalance_error_callback(...);
		*
		* // Create the adapter and use it for polling
		* RoundRobinPollStrategy poll_strategy(consumer);
		*
		* while (true) {
		*     // Poll each partition in turn
		*     Message msg = poll_strategy.poll();
		*     if (msg) {
		*         // process valid message
		*         }
		*     }
		* }
		* \endcode
		*
		* \warning Calling directly poll() or poll_batch() on the Consumer object while using this adapter will
		* lead to undesired results since the RoundRobinPollStrategy modifies the internal queuing mechanism of
		* the Consumer instance it owns.
		*/

		class RoundRobinPollStrategy : public PollStrategyBase {
		public:
			RoundRobinPollStrategy(Consumer& consumer);

			~RoundRobinPollStrategy();

			/**
			* \sa PollInterface::poll
			*/
			Message poll() override;

			/**
			* \sa PollInterface::poll
			*/
			Message poll(std::chrono::milliseconds timeout) override;

			/**
			* \sa PollInterface::poll_batch
			*/
			template <typename Allocator>
			std::vector<Message, Allocator> poll_batch(size_t max_batch_size,
				const Allocator& alloc);
			std::vector<Message> poll_batch(size_t max_batch_size) override;

			/**
			* \sa PollInterface::poll_batch
			*/
			template <typename Allocator>
			std::vector<Message, Allocator> poll_batch(size_t max_batch_size,
				std::chrono::milliseconds timeout,
				const Allocator& alloc);
			std::vector<Message> poll_batch(size_t max_batch_size,
				std::chrono::milliseconds timeout) override;

		protected:
			/**
			* \sa PollStrategyBase::reset_state
			*/
			void reset_state() final;

			QueueData& get_next_queue();

		private:
			template <typename Allocator>
			void consume_batch(Queue& queue,
				std::vector<Message, Allocator>& messages,
				ssize_t& count,
				std::chrono::milliseconds timeout,
				const Allocator& alloc);

			void restore_forwarding();

			// Members
			QueueMap::iterator  queue_iter_;
		};

		// Implementations
		template <typename Allocator>
		std::vector<Message, Allocator> RoundRobinPollStrategy::poll_batch(size_t max_batch_size,
			const Allocator& alloc) {
			return poll_batch(max_batch_size, get_consumer().get_timeout(), alloc);
		}

		template <typename Allocator>
		std::vector<Message, Allocator> RoundRobinPollStrategy::poll_batch(size_t max_batch_size,
			std::chrono::milliseconds timeout,
			const Allocator& alloc) {
			std::vector<Message, Allocator> messages(alloc);
			ssize_t count = max_batch_size;

			// batch from the group event queue first (non-blocking)
			consume_batch(get_consumer_queue().queue, messages, count, std::chrono::milliseconds(0), alloc);
			size_t num_queues = get_partition_queues().size();
			while ((count > 0) && (num_queues--)) {
				// batch from the next partition (non-blocking)
				consume_batch(get_next_queue().queue, messages, count, std::chrono::milliseconds(0), alloc);
			}
			// we still have space left in the buffer
			if (count > 0) {
				// wait on the event queue until timeout
				consume_batch(get_consumer_queue().queue, messages, count, timeout, alloc);
			}
			return messages;
		}

		template <typename Allocator>
		void RoundRobinPollStrategy::consume_batch(Queue& queue,
			std::vector<Message, Allocator>& messages,
			ssize_t& count,
			std::chrono::milliseconds timeout,
			const Allocator& alloc) {
			std::vector<Message, Allocator> queue_messages = queue.consume_batch(count, timeout, alloc);
			if (queue_messages.empty()) {
				return;
			}
			// concatenate both lists
			messages.insert(messages.end(),
				make_move_iterator(queue_messages.begin()),
				make_move_iterator(queue_messages.end()));
			// reduce total batch count
			count -= queue_messages.size();
		}
	}
}
#endif // !SYSTEM_KAFKA_ROUNDROBINPOLLSTRATEGY_H
