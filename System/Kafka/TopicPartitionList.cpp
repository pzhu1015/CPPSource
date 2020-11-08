///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Kafka/TopicPartitionList.h"
#include "System/Kafka/TopicPartition.h"
#include "System/Kafka/Metadata.h"
using std::vector;
using std::set;
using std::ostream;
using std::string;
using std::equal;
namespace System
{
	namespace Kafka
	{
		TopicPartitionsListPtr convert(const TopicPartitionList& topic_partitions) {
			TopicPartitionsListPtr handle(rd_kafka_topic_partition_list_new(topic_partitions.size()),
				&rd_kafka_topic_partition_list_destroy);
			for (const auto& item : topic_partitions) {
				rd_kafka_topic_partition_t* new_item = rd_kafka_topic_partition_list_add(
					handle.get(),
					item.get_topic().data(),
					item.get_partition()
				);
				new_item->offset = item.get_offset();
			}
			return handle;
		}

		TopicPartitionList convert(const TopicPartitionsListPtr& topic_partitions) {
			return convert(topic_partitions.get());
		}

		TopicPartitionList convert(rd_kafka_topic_partition_list_t* topic_partitions) {
			TopicPartitionList output;
			for (int i = 0; i < topic_partitions->cnt; ++i) {
				const auto& elem = topic_partitions->elems[i];
				output.emplace_back(elem.topic, elem.partition, elem.offset);
			}
			return output;
		}

		TopicPartitionList convert(const std::string& topic,
			const std::vector<PartitionMetadata>& partition_metadata)
		{
			TopicPartitionList output;
			for (const auto& meta : partition_metadata) {
				output.emplace_back(topic, meta.get_id());
			}
			return output;
		}

		TopicPartitionsListPtr make_handle(rd_kafka_topic_partition_list_t* handle) {
			return TopicPartitionsListPtr(handle, &rd_kafka_topic_partition_list_destroy);
		}

		TopicPartitionList find_matches(const TopicPartitionList& partitions,
			const set<string>& topics) {
			TopicPartitionList subset;
			for (const auto& partition : partitions) {
				for (const auto& topic : topics) {
					if (topic.size() == partition.get_topic().size()) {
						// compare both strings
						bool match = std::equal(topic.begin(), topic.end(), partition.get_topic().begin(),
							[](char c1, char c2)->bool {
							return toupper(c1) == toupper(c2);
						});
						if (match) {
							subset.emplace_back(partition);
						}
					}
				}
			}
			return subset;
		}

		TopicPartitionList find_matches(const TopicPartitionList& partitions,
			const set<int>& ids) {
			TopicPartitionList subset;
			for (const auto& partition : partitions) {
				if (ids.count(partition.get_partition()) > 0) {
					subset.emplace_back(partition);
				}
			}
			return subset;
		}

		ostream& operator<<(ostream& output, const TopicPartitionList& rhs) {
			output << "[ ";
			for (auto iter = rhs.begin(); iter != rhs.end(); ++iter) {
				if (iter != rhs.begin()) {
					output << ", ";
				}
				output << *iter;
			}
			output << " ]";
			return output;
		}
	}
}