///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Kafka/BackoffCommitter.h"
#include <algorithm>
using std::min;
namespace System
{
	namespace Kafka
	{
		BackoffCommitter::BackoffCommitter(Consumer& consumer)
			: consumer_(consumer) {

		}

		void BackoffCommitter::set_error_callback(ErrorCallback callback) {
			callback_ = move(callback);
		}

		void BackoffCommitter::commit() {
			perform([&] {
				return do_commit();
			});
		}

		void BackoffCommitter::commit(const Message& msg) {
			perform([&] {
				return do_commit(msg);
			});
		}

		void BackoffCommitter::commit(const TopicPartitionList& topic_partitions) {
			perform([&] {
				return do_commit(topic_partitions);
			});
		}

		Consumer& BackoffCommitter::get_consumer() {
			return consumer_;
		}
	}
}