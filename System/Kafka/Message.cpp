///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Kafka/Message.h"
#include "System/Kafka/MessageInternal.h"
using std::chrono::milliseconds;
namespace System
{
	namespace Kafka
	{
		void dummy_deleter(rd_kafka_message_t*) {

		}

		Message Message::make_non_owning(rd_kafka_message_t* handle) {
			return Message(handle, NonOwningTag());
		}

		Message::Message()
			: handle_(nullptr, nullptr),
			user_data_(nullptr) {

		}

		Message::Message(rd_kafka_message_t* handle)
			: Message(HandlePtr(handle, &rd_kafka_message_destroy)) {

		}

		Message::Message(rd_kafka_message_t* handle, NonOwningTag)
			: Message(HandlePtr(handle, &dummy_deleter)) {

		}

		Message::Message(HandlePtr handle)
			: handle_(move(handle)),
			payload_(handle_ ? Buffer((const Buffer::DataType*)handle_->payload, handle_->len) : Buffer()),
			key_(handle_ ? Buffer((const Buffer::DataType*)handle_->key, handle_->key_len) : Buffer()),
			user_data_(handle_ ? handle_->_private : nullptr) {
#if (RD_KAFKA_VERSION >= RD_KAFKA_HEADERS_SUPPORT_VERSION)
			// get the header list if any
			if (handle_) {
				rd_kafka_headers_t* headers_handle;
				Error error = rd_kafka_message_headers(handle_.get(), &headers_handle);
				if (!error) {
					header_list_ = HeaderListType::make_non_owning(headers_handle);
				}
			}
#endif
		}

		Message& Message::load_internal() {
			if (user_data_) {
				MessageInternal* mi = static_cast<MessageInternal*>(user_data_);
				user_data_ = mi->get_user_data();
				internal_ = mi->get_internal();
			}
			return *this;
		}

		nonstd::optional<MessageTimestamp> Message::get_timestamp() const {
			rd_kafka_timestamp_type_t type = RD_KAFKA_TIMESTAMP_NOT_AVAILABLE;
			int64_t timestamp = rd_kafka_message_timestamp(handle_.get(), &type);
			if (timestamp == -1 || type == RD_KAFKA_TIMESTAMP_NOT_AVAILABLE) {
				return{};
			}
			return MessageTimestamp(std::chrono::milliseconds(timestamp),
				static_cast<MessageTimestamp::TimestampType>(type));
		}
	}
}