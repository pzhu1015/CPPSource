///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_KAFKA_MESSAGE_H
#define SYSTEM_KAFKA_MESSAGE_H
#include "System/Base/DllExport.h"
#include "System/Kafka/Header.h"
#include "System/Kafka/Buffer.h"
#include "System/Kafka/HeaderList.h"
#include "System/Kafka/MessageTimestamp.h"
#include "System/Base/optional.hpp"
#include <assert.h>
#include <memory>
#include <chrono>
#include <librdkafka/rdkafka.h>
namespace System
{
	namespace Kafka
	{
		class Internal;

		/**
		* \brief Thin wrapper over a rdkafka message handle
		*
		* This is a non copyable, movable class that wraps a rd_kafka_message_t*.
		*
		* Messages can be empty (contain a null rd_kafka_message_t*). Therefore, users must check
		* that the message isn't empty by using the operator bool() before using them. This is especially
		* necessary when calling Consumer::poll() as any poll operation that returns a null pointer will
		* return an empty message.
		*/
		class SYSTEM_API Message {
		public:
			friend class MessageInternal;
			using InternalPtr = std::shared_ptr<Internal>;
#if (RD_KAFKA_VERSION >= RD_KAFKA_HEADERS_SUPPORT_VERSION)
			using HeaderType = Header<Buffer>;
			using HeaderListType = HeaderList<HeaderType>;
#endif
			/**
			* Constructs a message that won't take ownership of the given pointer
			*/
			static Message make_non_owning(rd_kafka_message_t* handle);

			/**
			* Constructs an empty message
			*/
			Message();

			/**
			* \brief Constructs a message from a handle
			*
			* The constructed message instance *will own* the given pointer, calling
			* rd_kafka_message_destroy upon destruction.
			*
			* \param handle The message handle to be wrapped
			*/
			Message(rd_kafka_message_t* handle);
			Message(const Message&) = delete;
			Message(Message&& rhs) = default;
			Message& operator=(const Message&) = delete;
			Message& operator=(Message&& rhs) = default;

			/**
			* \brief Gets the error attribute
			*/
			Error get_error() const {
				assert(handle_);
				return handle_->err;
			}

			/**
			* \brief Utility function to check for get_error() == RD_KAFKA_RESP_ERR__PARTITION_EOF
			*/
			bool is_eof() const {
				return get_error() == RD_KAFKA_RESP_ERR__PARTITION_EOF;
			}

			/**
			* \brief Gets the topic that this message belongs to
			*/
			std::string get_topic() const {
				assert(handle_);
				return handle_->rkt ? rd_kafka_topic_name(handle_->rkt) : std::string{};
			}

			/**
			* \brief Gets the partition that this message belongs to
			*/
			int get_partition() const {
				assert(handle_);
				return handle_->partition;
			}

			/**
			* \brief Gets the message's payload
			*/
			const Buffer& get_payload() const {
				return payload_;
			}

#if (RD_KAFKA_VERSION >= RD_KAFKA_HEADERS_SUPPORT_VERSION)
			/**
			* \brief Sets the message's header list.
			* \note This calls rd_kafka_message_set_headers.
			*/
			void set_header_list(const HeaderListType& headers) {
				assert(handle_);
				if (!headers) {
					return; //nothing to set
				}
				rd_kafka_headers_t* handle_copy = rd_kafka_headers_copy(headers.get_handle());
				rd_kafka_message_set_headers(handle_.get(), handle_copy);
				header_list_ = HeaderListType::make_non_owning(handle_copy);
			}

			/**
			* \brief Gets the message's header list
			*/
			const HeaderListType& get_header_list() const {
				return header_list_;
			}

			/**
			* \brief Detaches the message's header list
			*/
			template <typename HeaderType>
			HeaderList<HeaderType> detach_header_list() {
				rd_kafka_headers_t* headers_handle;
				Error error = rd_kafka_message_detach_headers(handle_.get(), &headers_handle);
				return error ? HeaderList<HeaderType>() : HeaderList<HeaderType>(headers_handle);
			}
#endif

			/**
			* \brief Gets the message's key
			*/
			const Buffer& get_key() const {
				return key_;
			}

			/**
			* \brief Gets the message offset
			*/
			int64_t get_offset() const {
				assert(handle_);
				return handle_->offset;
			}

			/**
			* \brief Gets the private user data.
			*
			* This should only be used on messages produced by a Producer that were set a private data
			* attribute
			*/
			void* get_user_data() const {
				return user_data_;
			}

			/**
			* \brief Gets this Message's timestamp
			*
			* If calling rd_kafka_message_timestamp returns -1, then boost::none_t will be returned.
			*/
			nonstd::optional<MessageTimestamp> get_timestamp() const;

#if RD_KAFKA_VERSION >= RD_KAFKA_MESSAGE_LATENCY_SUPPORT_VERSION
			/**
			* \brief Gets the message latency in microseconds as measured from the produce() call.
			*/
			std::chrono::microseconds get_latency() const {
				assert(handle_);
				return std::chrono::microseconds(rd_kafka_message_latency(handle_.get()));
			}
#endif

#if (RD_KAFKA_VERSION >= RD_KAFKA_MESSAGE_STATUS_SUPPORT_VERSION)
			/**
			* \brief Gets the message persistence status
			*/
			rd_kafka_msg_status_t get_status() const {
				assert(handle_);
				return rd_kafka_message_status(handle_.get());
			}
#endif

			/**
			* \brief Indicates whether this message is valid (not null)
			*/
			explicit operator bool() const {
				return handle_ != nullptr;
			}

			/**
			* \brief Gets the rdkafka message handle
			*/
			rd_kafka_message_t* get_handle() const {
				return handle_.get();
			}

			/**
			* \brief Internal private const data accessor (internal use only)
			*/
			InternalPtr internal() const {
				return internal_;
			}
		private:
			using HandlePtr = std::unique_ptr<rd_kafka_message_t, decltype(&rd_kafka_message_destroy)>;

			struct NonOwningTag { };

			Message(rd_kafka_message_t* handle, NonOwningTag);
			Message(HandlePtr handle);
			Message& load_internal();

			HandlePtr handle_;
			Buffer payload_;
			Buffer key_;
#if (RD_KAFKA_VERSION >= RD_KAFKA_HEADERS_SUPPORT_VERSION)
			HeaderListType header_list_;
#endif
			void* user_data_;
			InternalPtr internal_;
		};

		using MessageList = std::vector<Message>;
	}
}
#endif // !SYSTEM_KAFKA_MESSAGE_H