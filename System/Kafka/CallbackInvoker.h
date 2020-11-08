///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_KAFKA_CALLBACKINVOKER_H
#define SYSTEM_KAFKA_CALLBACKINVOKER_H
#include <sstream>
#include <assert.h>
#include "System/Kafka/Logging.h"
#include "System/Kafka/KafkaHandleBase.h"
namespace System
{
	namespace Kafka
	{
		// Error values
		template <typename T>
		T error_value() { return T{}; }

		template<> inline
			void error_value<void>() {};

		template<> inline
			bool error_value<bool>() { return false; }

		template<> inline
			int error_value<int>() { return -1; }

		/**
		* \brief Wraps an std::function object and runs it while preventing all exceptions from escaping
		* \tparam Func An std::function object
		*/
		template <typename Func>
		class CallbackInvoker
		{
		public:
			using RetType = typename Func::result_type;
			using LogCallback = std::function<void(KafkaHandleBase& handle,
				int level,
				const std::string& facility,
				const std::string& message)>;
			CallbackInvoker(const char* callback_name,
				const Func& callback,
				KafkaHandleBase* handle)
				: callback_name_(callback_name),
				callback_(callback),
				handle_(handle) {
			}

			explicit operator bool() const {
				return (bool)callback_;
			}

			template <typename ...Args>
			RetType operator()(Args&&... args) const {
				static const char* library_name = "cppkafka";
				std::ostringstream error_msg;
				try {
					if (callback_) {
						return callback_(std::forward<Args>(args)...);
					}
					return error_value<RetType>();
				}
				catch (const std::exception& ex) {
					if (handle_) {
						error_msg << "Caught exception in " << callback_name_ << " callback: " << ex.what();
					}
				}
				catch (...) {
					if (handle_) {
						error_msg << "Caught unknown exception in " << callback_name_ << " callback";
					}
				}
				// Log error
				if (handle_) {
					if (handle_->get_configuration().get_log_callback()) {
						try {
							// Log it
							handle_->get_configuration().get_log_callback()(*handle_,
								static_cast<int>(LogLevel::LogErr),
								library_name,
								error_msg.str());
						}
						catch (...) {} // sink everything
					}
					else {
						rd_kafka_log_print(handle_->get_handle(),
							static_cast<int>(LogLevel::LogErr),
							library_name,
							error_msg.str().c_str());
					}
				}
				return error_value<RetType>();
			}
		private:
			const char* callback_name_;
			const Func& callback_;
			KafkaHandleBase* handle_;
		};
	}
}
#endif // !SYSTEM_KAFKA_CALLBACKINVOKER_H
