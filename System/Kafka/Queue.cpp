///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Kafka/Queue.h"
#include "System/Kafka/Exceptions.h"

using std::vector;
using std::exception;
using std::chrono::milliseconds;
using std::allocator;
namespace System
{
	namespace Kafka
	{
		void dummy_deleter(rd_kafka_queue_t*) {

		}

		const milliseconds Queue::DEFAULT_TIMEOUT{ 1000 };

		Queue Queue::make_non_owning(rd_kafka_queue_t* handle) {
			return Queue(handle, NonOwningTag{});
		}

		Queue Queue::make_queue(rd_kafka_queue_t* handle) {
			if (rd_kafka_version() <= RD_KAFKA_QUEUE_REFCOUNT_BUG_VERSION) {
				return Queue::make_non_owning(handle);
			}
			else {
				return Queue(handle);
			}
		}

		Queue::Queue()
			: handle_(nullptr, nullptr),
			timeout_ms_(DEFAULT_TIMEOUT) {

		}

		Queue::Queue(rd_kafka_queue_t* handle)
			: handle_(handle, &rd_kafka_queue_destroy),
			timeout_ms_(DEFAULT_TIMEOUT) {

		}

		Queue::Queue(rd_kafka_queue_t* handle, NonOwningTag)
			: handle_(handle, &dummy_deleter) {

		}

		rd_kafka_queue_t* Queue::get_handle() const {
			return handle_.get();
		}

		size_t Queue::get_length() const {
			return rd_kafka_queue_length(handle_.get());
		}

		void Queue::forward_to_queue(const Queue& forward_queue) const {
			return rd_kafka_queue_forward(handle_.get(), forward_queue.handle_.get());
		}

		void Queue::disable_queue_forwarding() const {
			return rd_kafka_queue_forward(handle_.get(), nullptr);
		}

		void Queue::set_timeout(milliseconds timeout) {
			timeout_ms_ = timeout;
		}

		milliseconds Queue::get_timeout() const {
			return timeout_ms_;
		}

		Message Queue::consume() const {
			return consume(timeout_ms_);
		}

		Message Queue::consume(milliseconds timeout) const {
			return Message(rd_kafka_consume_queue(handle_.get(), static_cast<int>(timeout.count())));
		}

		vector<Message> Queue::consume_batch(size_t max_batch_size) const {
			return consume_batch(max_batch_size, timeout_ms_, allocator<Message>());
		}

		vector<Message> Queue::consume_batch(size_t max_batch_size, milliseconds timeout) const {
			return consume_batch(max_batch_size, timeout, allocator<Message>());
		}

		Event Queue::next_event() const {
			return next_event(timeout_ms_);
		}

		Event Queue::next_event(milliseconds timeout) const {
			return Event(rd_kafka_queue_poll(handle_.get(), (int)timeout.count()));
		}

	}
}