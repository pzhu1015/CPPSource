///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Kafka/RoundRobinPollStrategy.h"
using std::string;
using std::chrono::milliseconds;
using std::make_move_iterator;
using std::allocator;
namespace System
{
	namespace Kafka
	{
		RoundRobinPollStrategy::RoundRobinPollStrategy(Consumer& consumer)
			: PollStrategyBase(consumer) {
			reset_state();
		}

		RoundRobinPollStrategy::~RoundRobinPollStrategy() {
			restore_forwarding();
		}


		Message RoundRobinPollStrategy::poll() {
			return poll(get_consumer().get_timeout());
		}

		Message RoundRobinPollStrategy::poll(milliseconds timeout) {
			// Always give priority to group and global events
			Message message = get_consumer_queue().queue.consume(milliseconds(0));
			if (message) {
				return message;
			}
			size_t num_queues = get_partition_queues().size();
			while (num_queues--) {
				//consume the next partition (non-blocking)
				message = get_next_queue().queue.consume(milliseconds(0));
				if (message) {
					return message;
				}
			}
			// We still don't have a valid message so we block on the event queue
			return get_consumer_queue().queue.consume(timeout);
		}

		std::vector<Message> RoundRobinPollStrategy::poll_batch(size_t max_batch_size) {
			return poll_batch(max_batch_size, get_consumer().get_timeout(), allocator<Message>());
		}

		std::vector<Message> RoundRobinPollStrategy::poll_batch(size_t max_batch_size,
			milliseconds timeout) {
			return poll_batch(max_batch_size, timeout, allocator<Message>());
		}

		void RoundRobinPollStrategy::restore_forwarding() {
			// forward all partition queues
			for (const auto& toppar : get_partition_queues()) {
				toppar.second.queue.forward_to_queue(get_consumer_queue().queue);
			}
		}

		QueueData& RoundRobinPollStrategy::get_next_queue() {
			if (get_partition_queues().empty()) {
				throw QueueException(RD_KAFKA_RESP_ERR__STATE);
			}
			if (++queue_iter_ == get_partition_queues().end()) {
				queue_iter_ = get_partition_queues().begin();
			}
			return queue_iter_->second;
		}

		void RoundRobinPollStrategy::reset_state() {
			queue_iter_ = get_partition_queues().begin();
		}
	}
}