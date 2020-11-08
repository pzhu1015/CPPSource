///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_KAFKA_TOPICPARTITION_H
#define SYSTEM_KAFKA_TOPICPARTITION_H
#include "System/Base/DllExport.h"
#include <string>
#include <iosfwd>
namespace System
{
	namespace Kafka
	{
		/**
		* Represents a topic/partition
		*/
		class SYSTEM_API TopicPartition {
		public:
			/**
			* Special offsets enum
			*/
			enum Offset {
				OFFSET_BEGINNING = -2,
				OFFSET_END = -1,
				OFFSET_STORED = -1000,
				OFFSET_INVALID = -1001
			};

			/**
			* Default constructs a topic/partition
			*/
			TopicPartition();

			/**
			* \brief Constructs a topic/partition
			*
			* The partition value will be RD_KAFKA_OFFSET_INVALID
			*
			* \param topic The topic name
			*/
			TopicPartition(const char* topic);

			/**
			* \brief Constructs a topic/partition
			*
			* The partition value will be RD_KAFKA_OFFSET_INVALID
			*
			* \param topic The topic name
			*/
			TopicPartition(std::string topic);

			/**
			* Constructs a topic/partition
			*
			* \param topic The topic name
			* \param partition The partition to be used
			*/
			TopicPartition(std::string topic, int partition);

			/**
			* Constructs a topic/partition
			*
			* \param topic The topic name
			* \param partition The partition to be used
			* \param offset The offset to be used
			*/
			TopicPartition(std::string topic, int partition, int64_t offset);

			/**
			* Gets the topic name
			*/
			const std::string& get_topic() const;

			/**
			* Gets the partition
			*/
			int get_partition() const;

			/**
			* Gets the offset
			*/
			int64_t get_offset() const;

			/**
			* @brief Sets the partition
			*/
			void set_partition(int partition);

			/**
			* Sets the offset
			*/
			void set_offset(int64_t offset);

			/**
			* Compare the (topic, partition) for less-than equality
			*/
			bool operator<(const TopicPartition& rhs) const;

			/**
			* Compare the (topic, partition) for equality
			*/
			bool operator==(const TopicPartition& rhs) const;

			/**
			* Compare the (topic, partition) for in-equality
			*/
			bool operator!=(const TopicPartition& rhs) const;

			/**
			* Print to a stream
			*/
			SYSTEM_API friend std::ostream& operator<<(std::ostream& output, const TopicPartition& rhs);
		private:
			std::string topic_;
			int partition_;
			int64_t offset_;
		};
	}
}
#endif // !SYSTEM_KAFKA_TOPICPARTITION_H
