///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_KAFKA_MESSAGEINTERNAL_H
#define SYSTEM_KAFKA_MESSAGEINTERNAL_H
#include "System/Base/DllExport.h"
#include <memory>
namespace System
{
	namespace Kafka
	{
		class Message;

		class Internal {
		public:
			virtual ~Internal() = default;
		};
		using InternalPtr = std::shared_ptr<Internal>;

		/**
		* \brief Private message data structure
		*/
		class SYSTEM_API MessageInternal {
		public:
			MessageInternal(void* user_data, std::shared_ptr<Internal> internal);
			static std::unique_ptr<MessageInternal> load(Message& message);
			void* get_user_data() const;
			InternalPtr get_internal() const;
		private:
			void*          user_data_;
			InternalPtr    internal_;
		};

		template <typename BuilderType>
		class MessageInternalGuard {
		public:
			MessageInternalGuard(BuilderType& builder)
				: builder_(builder),
				user_data_(builder.user_data()) {
				if (builder_.internal()) {
					// Swap contents with user_data
					ptr_.reset(new MessageInternal(user_data_, builder_.internal()));
					builder_.user_data(ptr_.get()); //overwrite user data
				}
			}
			~MessageInternalGuard() {
				//Restore user data
				builder_.user_data(user_data_);
			}
			void release() {
				ptr_.release();
			}
		private:
			BuilderType& builder_;
			std::unique_ptr<MessageInternal> ptr_;
			void* user_data_;
		};
	}
}
#endif // !SYSTEM_KAFKA_MESSAGEINTERNAL_H
