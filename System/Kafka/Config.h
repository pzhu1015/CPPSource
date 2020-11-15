///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_KAFKA_CONFIG_H
#define SYSTEM_KAFKA_CONFIG_H
#include "System/Base/DllExport.h"
#include "System/Kafka/TopicPartitionList.h"
#include "System/Kafka/TopicConfig.h"
#include "System/Kafka/ClonablePtr.h"
#include "System/Kafka/ConfigBase.h"
#include "System/Kafka/Event.h"
#include "System/nonstd/optional.hpp"
#include <memory>
#include <string>
#include <functional>
#include <initializer_list>
#include <chrono>
#include <librdkafka/rdkafka.h>
namespace System
{
	namespace Kafka
	{
		class Message;
		class Error;
		class Producer;
		class Consumer;
		class KafkaHandleBase;

		/**
		* \brief Represents a global configuration (rd_kafka_conf_t).
		*
		* This wraps an rdkafka configuration handle. It can safely be copied (will use
		* rd_kafka_conf_dup under the hood) and moved.
		*
		* Some other overloads for Config::set are given via ConfigBase.
		*/
		class SYSTEM_API Config : public ConfigBase<Config> {
		public:
			using DeliveryReportCallback = std::function<void(Producer& producer, const Message&)>;
			using OffsetCommitCallback = std::function<void(Consumer& consumer,
				Error error,
				const TopicPartitionList& topic_partitions)>;
			using ErrorCallback = std::function<void(KafkaHandleBase& handle,
				int error,
				const std::string& reason)>;
			using ThrottleCallback = std::function<void(KafkaHandleBase& handle,
				const std::string& broker_name,
				int32_t broker_id,
				std::chrono::milliseconds throttle_time)>;
			using LogCallback = std::function<void(KafkaHandleBase& handle,
				int level,
				const std::string& facility,
				const std::string& message)>;
			using StatsCallback = std::function<void(KafkaHandleBase& handle, const std::string& json)>;
			using SocketCallback = std::function<int(int domain, int type, int protocol)>;
			using BackgroundEventCallback = std::function<void(KafkaHandleBase& handle, Event)>;

			using ConfigBase<Config>::set;
			using ConfigBase<Config>::get;

			/**
			* Default constructs a Config object
			*/
			Config();

			/**
			* Constructs a Config object using a list of options
			*/
			Config(const std::vector<ConfigOption>& options);

			/**
			* Constructs a Config object using a list of options
			*/
			Config(const std::initializer_list<ConfigOption>& options);

			/**
			* \brief Sets an attribute.
			*
			* This will call rd_kafka_conf_set under the hood.
			*
			* \param name The name of the attribute
			* \param value The value of the attribute
			*/
			Config& set(const std::string& name, const std::string& value);

			/**
			* Sets the delivery report callback (invokes rd_kafka_conf_set_dr_msg_cb)
			*/
			Config& set_delivery_report_callback(DeliveryReportCallback callback);

			/**
			* Sets the offset commit callback (invokes rd_kafka_conf_set_offset_commit_cb)
			*/
			Config& set_offset_commit_callback(OffsetCommitCallback callback);

			/**
			* Sets the error callback (invokes rd_kafka_conf_set_error_cb)
			*/
			Config& set_error_callback(ErrorCallback callback);

			/**
			* Sets the throttle callback (invokes rd_kafka_conf_set_throttle_cb)
			*/
			Config& set_throttle_callback(ThrottleCallback callback);

			/**
			* Sets the log callback (invokes rd_kafka_conf_set_log_cb)
			*/
			Config& set_log_callback(LogCallback callback);

			/**
			* Sets the stats callback (invokes rd_kafka_conf_set_stats_cb)
			*/
			Config& set_stats_callback(StatsCallback callback);

			/**
			* Sets the socket callback (invokes rd_kafka_conf_set_socket_cb)
			*/
			Config& set_socket_callback(SocketCallback callback);

#if RD_KAFKA_VERSION >= RD_KAFKA_ADMIN_API_SUPPORT_VERSION
			/**
			* Sets the background event callback (invokes rd_kafka_conf_set_background_event_cb)
			*/
			Config& set_background_event_callback(BackgroundEventCallback callback);

			/**
			* Sets the event mask (invokes rd_kafka_conf_set_events)
			*/
			Config& set_events(int events);
#endif

			/**
			* Sets the default topic configuration
			*/
			Config& set_default_topic_configuration(TopicConfig config);

			/**
			* Returns true if the given property name has been set
			*/
			bool has_property(const std::string& name) const;

			/**
			* Gets the rdkafka configuration handle
			*/
			rd_kafka_conf_t* get_handle() const;

			/**
			* Gets an option value
			*
			* \throws ConfigOptionNotFound if the option is not present
			*/
			std::string get(const std::string& name) const;

			/**
			* Gets all options, including default values which are set by rdkafka
			*/
			std::map<std::string, std::string> get_all() const;

			/**
			* Gets the delivery report callback
			*/
			const DeliveryReportCallback& get_delivery_report_callback() const;

			/**
			* Gets the offset commit callback
			*/
			const OffsetCommitCallback& get_offset_commit_callback() const;

			/**
			* Gets the error callback
			*/
			const ErrorCallback& get_error_callback() const;

			/**
			* Gets the throttle callback
			*/
			const ThrottleCallback& get_throttle_callback() const;

			/**
			* Gets the log callback
			*/
			const LogCallback& get_log_callback() const;

			/**
			* Gets the stats callback
			*/
			const StatsCallback& get_stats_callback() const;

			/**
			* Gets the socket callback
			*/
			const SocketCallback& get_socket_callback() const;

			/**
			* Gets the background event callback
			*/
			const BackgroundEventCallback& get_background_event_callback() const;

			///**
			//* Gets the default topic configuration
			//*/
			const nonstd::optional<TopicConfig>& get_default_topic_configuration() const;

			///**
			//* Gets the default topic configuration
			//*/
			nonstd::optional<TopicConfig>& get_default_topic_configuration();
		private:
			using HandlePtr = ClonablePtr<rd_kafka_conf_t, decltype(&rd_kafka_conf_destroy),
				decltype(&rd_kafka_conf_dup)>;

			Config(rd_kafka_conf_t* ptr);
			static HandlePtr make_handle(rd_kafka_conf_t* ptr);

			HandlePtr handle_;
			nonstd::optional<TopicConfig> default_topic_config_;
			DeliveryReportCallback delivery_report_callback_;
			OffsetCommitCallback offset_commit_callback_;
			ErrorCallback error_callback_;
			ThrottleCallback throttle_callback_;
			LogCallback log_callback_;
			StatsCallback stats_callback_;
			SocketCallback socket_callback_;
			BackgroundEventCallback background_event_callback_;
		};
	}
}
#endif // !SYSTEM_KAFKA_CONFIG_H
