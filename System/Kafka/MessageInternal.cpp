///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Kafka/MessageInternal.h"
#include "System/Kafka/Message.h"
#include "System/Kafka/MessageBuilder.h"

namespace System
{
	namespace Kafka
	{
		MessageInternal::MessageInternal(void* user_data,
			std::shared_ptr<Internal> internal)
			: user_data_(user_data),
			internal_(internal) {
		}

		std::unique_ptr<MessageInternal> MessageInternal::load(Message& message) {
			return std::unique_ptr<MessageInternal>(message.load_internal().get_handle() ?
				static_cast<MessageInternal*>(message.get_handle()->_private) : nullptr);
		}

		void* MessageInternal::get_user_data() const {
			return user_data_;
		}

		InternalPtr MessageInternal::get_internal() const {
			return internal_;
		}
	}
}