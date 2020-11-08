///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Kafka/Config.h"
#include "System/Kafka/Exceptions.h"
#include "System/Kafka/Message.h"
#include "System/Kafka/Consumer.h"
#include "System/Kafka/Producer.h"
#include <vector>
#include <librdkafka/rdkafka.h>

using std::string;
using std::map;
using std::move;
using std::vector;
using std::initializer_list;
using std::chrono::milliseconds;
namespace System
{
	namespace Kafka
	{
		// Callback proxies

		void delivery_report_callback_proxy(rd_kafka_t*, const rd_kafka_message_t* msg, void *opaque) {
			Producer* handle = static_cast<Producer*>(opaque);
			Message message = Message::make_non_owning((rd_kafka_message_t*)msg);
			CallbackInvoker<Config::DeliveryReportCallback>
				("delivery report", handle->get_configuration().get_delivery_report_callback(), handle)
				(*handle, message);
		}

		void offset_commit_callback_proxy(rd_kafka_t*, rd_kafka_resp_err_t err,
			rd_kafka_topic_partition_list_t *offsets, void *opaque) {
			Consumer* handle = static_cast<Consumer*>(opaque);
			TopicPartitionList list = offsets ? convert(offsets) : TopicPartitionList{};
			CallbackInvoker<Config::OffsetCommitCallback>
				("offset commit", handle->get_configuration().get_offset_commit_callback(), handle)
				(*handle, err, list);
		}

		void error_callback_proxy(rd_kafka_t*, int err, const char *reason, void *opaque) {
			KafkaHandleBase* handle = static_cast<KafkaHandleBase*>(opaque);
			CallbackInvoker<Config::ErrorCallback>
				("error", handle->get_configuration().get_error_callback(), handle)
				(*handle, err, reason);
		}

		void throttle_callback_proxy(rd_kafka_t*, const char* broker_name,
			int32_t broker_id, int throttle_time_ms, void *opaque) {
			KafkaHandleBase* handle = static_cast<KafkaHandleBase*>(opaque);
			CallbackInvoker<Config::ThrottleCallback>
				("throttle", handle->get_configuration().get_throttle_callback(), handle)
				(*handle, broker_name, broker_id, milliseconds(throttle_time_ms));
		}

		void log_callback_proxy(const rd_kafka_t* h, int level,
			const char* facility, const char* message) {
			KafkaHandleBase* handle = static_cast<KafkaHandleBase*>(rd_kafka_opaque(h));
			CallbackInvoker<Config::LogCallback>
				("log", handle->get_configuration().get_log_callback(), nullptr)
				(*handle, level, facility, message);
		}

		int stats_callback_proxy(rd_kafka_t*, char *json, size_t json_len, void *opaque) {
			KafkaHandleBase* handle = static_cast<KafkaHandleBase*>(opaque);
			CallbackInvoker<Config::StatsCallback>
				("statistics", handle->get_configuration().get_stats_callback(), handle)
				(*handle, string(json, json + json_len));
			return 0;
		}

		int socket_callback_proxy(int domain, int type, int protocol, void* opaque) {
			KafkaHandleBase* handle = static_cast<KafkaHandleBase*>(opaque);
			return CallbackInvoker<Config::SocketCallback>
				("socket", handle->get_configuration().get_socket_callback(), handle)
				(domain, type, protocol);
		}

		void background_event_callback_proxy(rd_kafka_t*, rd_kafka_event_t* event_ptr, void *opaque) {
			KafkaHandleBase* handle = static_cast<KafkaHandleBase*>(opaque);
			CallbackInvoker<Config::BackgroundEventCallback>
				("background_event", handle->get_configuration().get_background_event_callback(), handle)
				(*handle, Event{ event_ptr });
		}

		// Config

		Config::Config()
			: handle_(make_handle(rd_kafka_conf_new())) {

		}

		Config::Config(const vector<ConfigOption>& options)
			: Config() {
			set(options);
		}

		Config::Config(const initializer_list<ConfigOption>& options)
			: Config() {
			set(options);
		}

		Config::Config(rd_kafka_conf_t* ptr)
			: handle_(make_handle(ptr)) {

		}

		Config& Config::set(const string& name, const string& value) {
			char error_buffer[512];
			rd_kafka_conf_res_t result;
			result = rd_kafka_conf_set(handle_.get(), name.data(), value.data(), error_buffer,
				sizeof(error_buffer));
			if (result != RD_KAFKA_CONF_OK) {
				throw ConfigException(name, error_buffer);
			}
			return *this;
		}

		Config& Config::set_delivery_report_callback(DeliveryReportCallback callback) {
			delivery_report_callback_ = move(callback);
			rd_kafka_conf_set_dr_msg_cb(handle_.get(), &delivery_report_callback_proxy);
			return *this;
		}

		Config& Config::set_offset_commit_callback(OffsetCommitCallback callback) {
			offset_commit_callback_ = move(callback);
			rd_kafka_conf_set_offset_commit_cb(handle_.get(), &offset_commit_callback_proxy);
			return *this;
		}

		Config& Config::set_error_callback(ErrorCallback callback) {
			error_callback_ = move(callback);
			rd_kafka_conf_set_error_cb(handle_.get(), &error_callback_proxy);
			return *this;
		}

		Config& Config::set_throttle_callback(ThrottleCallback callback) {
			throttle_callback_ = move(callback);
			rd_kafka_conf_set_throttle_cb(handle_.get(), &throttle_callback_proxy);
			return *this;
		}

		Config& Config::set_log_callback(LogCallback callback) {
			log_callback_ = move(callback);
			rd_kafka_conf_set_log_cb(handle_.get(), &log_callback_proxy);
			return *this;
		}

		Config& Config::set_stats_callback(StatsCallback callback) {
			stats_callback_ = move(callback);
			rd_kafka_conf_set_stats_cb(handle_.get(), &stats_callback_proxy);
			return *this;
		}

		Config& Config::set_socket_callback(SocketCallback callback) {
			socket_callback_ = move(callback);
			rd_kafka_conf_set_socket_cb(handle_.get(), &socket_callback_proxy);
			return *this;
		}

#if RD_KAFKA_VERSION >= RD_KAFKA_ADMIN_API_SUPPORT_VERSION
		Config& Config::set_background_event_callback(BackgroundEventCallback callback) {
			background_event_callback_ = move(callback);
			rd_kafka_conf_set_background_event_cb(handle_.get(), &background_event_callback_proxy);
			return *this;
		}

		Config& Config::set_events(int events) {
			rd_kafka_conf_set_events(handle_.get(), events);
			return *this;
		}
#endif

		Config&
			Config::set_default_topic_configuration(TopicConfig config) {
			//default_topic_config_ = std::move(config);
			return *this;
		}

		bool Config::has_property(const string& name) const {
			size_t size = 0;
			return rd_kafka_conf_get(handle_.get(), name.data(), nullptr, &size) == RD_KAFKA_CONF_OK;
		}

		rd_kafka_conf_t* Config::get_handle() const {
			return handle_.get();
		}

		string Config::get(const string& name) const {
			size_t size = 0;
			auto result = rd_kafka_conf_get(handle_.get(), name.data(), nullptr, &size);
			if (result != RD_KAFKA_CONF_OK) {
				throw ConfigOptionNotFound(name);
			}
			vector<char> buffer(size);
			rd_kafka_conf_get(handle_.get(), name.data(), buffer.data(), &size);
			return string(buffer.data());
		}

		map<string, string> Config::get_all() const {
			size_t count = 0;
			const char** all = rd_kafka_conf_dump(handle_.get(), &count);
			map<string, string> output = parse_dump(all, count);
			rd_kafka_conf_dump_free(all, count);
			return output;
		}

		const Config::DeliveryReportCallback& Config::get_delivery_report_callback() const {
			return delivery_report_callback_;
		}

		const Config::OffsetCommitCallback& Config::get_offset_commit_callback() const {
			return offset_commit_callback_;
		}

		const Config::ErrorCallback& Config::get_error_callback() const {
			return error_callback_;
		}

		const Config::ThrottleCallback& Config::get_throttle_callback() const {
			return throttle_callback_;
		}

		const Config::LogCallback& Config::get_log_callback() const {
			return log_callback_;
		}

		const Config::StatsCallback& Config::get_stats_callback() const {
			return stats_callback_;
		}

		const Config::SocketCallback& Config::get_socket_callback() const {
			return socket_callback_;
		}

		const Config::BackgroundEventCallback&
			Config::get_background_event_callback() const {
			return background_event_callback_;
		}

		const nonstd::optional<TopicConfig>& Config::get_default_topic_configuration() const {
			return default_topic_config_;
		}

		nonstd::optional<TopicConfig>& Config::get_default_topic_configuration() {
			return default_topic_config_;
		}

		Config::HandlePtr Config::make_handle(rd_kafka_conf_t* ptr) {
			return HandlePtr(ptr, &rd_kafka_conf_destroy, &rd_kafka_conf_dup);
		}
	}
}
