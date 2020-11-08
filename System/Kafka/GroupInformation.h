///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_KAFKA_GROUPINFORMATION_H
#define SYSTEM_KAFKA_GROUPINFORMATION_H
#include "System/Base/DllExport.h"
#include "System/Kafka/Metadata.h"
#include "System/Kafka/Error.h"
#include "System/Kafka/TopicPartitionList.h"
#include <vector>
#include <cstdint>
namespace System
{
	namespace Kafka
	{
		/**
		* \brief Parses the member assignment information
		*
		* This class parses the data in GroupMemberInformation::get_member_assignment.
		*/
		class SYSTEM_API MemberAssignmentInformation {
		public:
			/**
			* Constructs an instance
			*/
			MemberAssignmentInformation(const std::vector<uint8_t>& data);

			/**
			* Gets the version
			*/
			uint16_t get_version() const;

			/**
			* Gets the topic/partition assignment
			*/
			const TopicPartitionList& get_topic_partitions() const;
		private:
			uint16_t version_;
			TopicPartitionList topic_partitions_;
		};

		/**
		* \brief Represents the information about a specific consumer group member
		*/
		class SYSTEM_API GroupMemberInformation {
		public:
			/**
			* Constructs an instance using the provided information
			*
			* \param info The information pointer
			*/
			GroupMemberInformation(const rd_kafka_group_member_info& info);

			/**
			* Gets the member id
			*/
			const std::string& get_member_id() const;

			/**
			* Gets the client id
			*/
			const std::string& get_client_id() const;

			/**
			* Gets the client host
			*/
			const std::string& get_client_host() const;

			/**
			* Gets the member metadata
			*/
			const std::vector<uint8_t>& get_member_metadata() const;

			/**
			* Gets the member assignment
			*/
			const std::vector<uint8_t>& get_member_assignment() const;
		private:
			std::string member_id_;
			std::string client_id_;
			std::string client_host_;
			std::vector<uint8_t> member_metadata_;
			std::vector<uint8_t> member_assignment_;
		};

		/**
		* \brief Represents the information about a specific consumer group
		*/
		class SYSTEM_API GroupInformation {
		public:
			/**
			* Constructs an instance using the provided information.
			*
			* \param info The information pointer
			*/
			GroupInformation(const rd_kafka_group_info& info);

			/**
			* Gets the broker metadata
			*/
			const BrokerMetadata& get_broker() const;

			/**
			* Gets the group name
			*/
			const std::string& get_name() const;

			/**
			* Gets the broker-originated error
			*/
			Error get_error() const;

			/**
			* Gets the group state
			*/
			const std::string& get_state() const;

			/**
			* Gets the group protocol type
			*/
			const std::string& get_protocol_type() const;

			/**
			* Gets the group protocol
			*/
			const std::string& get_protocol() const;

			/**
			* Gets the group members
			*/
			const std::vector<GroupMemberInformation>& get_members() const;
		private:
			BrokerMetadata broker_;
			std::string name_;
			Error error_;
			std::string state_;
			std::string protocol_type_;
			std::string protocol_;
			std::vector<GroupMemberInformation> members_;
		};

		using GroupInformationList = std::vector<GroupInformation>;
	}
}
#endif // !SYSTEM_KAFKA_GROUPINFORMATION_H
