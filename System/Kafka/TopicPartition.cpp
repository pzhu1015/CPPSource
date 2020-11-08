///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Kafka/TopicPartition.h"
#include <tuple>
#include <librdkafka/rdkafka.h>
using std::string;
using std::to_string;
using std::ostream;
using std::tie;
namespace System
{
	namespace Kafka
	{
		TopicPartition::TopicPartition()
			: TopicPartition("") {

		}

		TopicPartition::TopicPartition(const char* topic)
			: TopicPartition(string(topic)) {

		}

		TopicPartition::TopicPartition(string topic)
			: TopicPartition(move(topic), RD_KAFKA_PARTITION_UA) {

		}

		TopicPartition::TopicPartition(string topic, int partition)
			: TopicPartition(move(topic), partition, RD_KAFKA_OFFSET_INVALID) {

		}

		TopicPartition::TopicPartition(string topic, int partition, int64_t offset)
			: topic_(move(topic)), partition_(partition), offset_(offset) {

		}

		const string& TopicPartition::get_topic() const {
			return topic_;
		}

		int TopicPartition::get_partition() const {
			return partition_;
		}

		int64_t TopicPartition::get_offset() const {
			return offset_;
		}

		void TopicPartition::set_partition(int partition) {
			partition_ = partition;
		}

		void TopicPartition::set_offset(int64_t offset) {
			offset_ = offset;
		}

		bool TopicPartition::operator<(const TopicPartition& rhs) const {
			return tie(topic_, partition_) < tie(rhs.topic_, rhs.partition_);
		}

		bool TopicPartition::operator==(const TopicPartition& rhs) const {
			return tie(topic_, partition_) == tie(rhs.topic_, rhs.partition_);
		}

		bool TopicPartition::operator!=(const TopicPartition& rhs) const {
			return !(*this == rhs);
		}

		ostream& operator<<(ostream& output, const TopicPartition& rhs) {
			return output << rhs.get_topic() << "["
				<< rhs.get_partition() << ":"
				<< (rhs.get_offset() == RD_KAFKA_OFFSET_INVALID ? "#" : to_string(rhs.get_offset()))
				<< "]";
		}

	}
}