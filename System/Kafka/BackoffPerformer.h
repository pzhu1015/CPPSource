///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_KAFKA_BACKOFFPERFORMER_H
#define SYSTEM_KAFKA_BACKOFFPERFORMER_H
#include "System/Base/DllExport.h"
#include "System/Kafka/Consumer.h"
#include "System/Kafka/Exceptions.h"
#include <chrono>
#include <functional>
#include <thread>
namespace System
{
	namespace Kafka
	{
		class SYSTEM_API BackoffPerformer {
		public:
			using TimeUnit = std::chrono::milliseconds;
			static const TimeUnit DEFAULT_INITIAL_BACKOFF;
			static const TimeUnit DEFAULT_BACKOFF_STEP;
			static const TimeUnit DEFAULT_MAXIMUM_BACKOFF;
			static const size_t DEFAULT_MAXIMUM_RETRIES;

			/**
			* The backoff policy to use
			*/
			enum class BackoffPolicy {
				LINEAR,
				EXPONENTIAL
			};

			/**
			* Constructs an instance of backoff performer
			*
			* By default, the linear backoff policy is used
			*/
			BackoffPerformer();

			/**
			* \brief Sets the backoff policy
			*
			* \param policy The backoff policy to be used
			*/
			void set_backoff_policy(BackoffPolicy policy);

			/**
			* \brief Sets the initial backoff
			*
			* The first time a commit fails, this will be the delay between the request is sent
			* and we re-try doing so
			*
			* \param value The value to be used
			*/
			void set_initial_backoff(TimeUnit value);

			/**
			* \brief Sets the backoff step
			*
			* When using the linear backoff policy, this will be the delay between sending a request
			* that fails and re-trying it
			*
			* \param value The value to be used
			*/
			void set_backoff_step(TimeUnit value);

			/**
			* \brief Sets the maximum backoff
			*
			* The backoff used will never be larger than this number
			*
			* \param value The value to be used
			*/
			void set_maximum_backoff(TimeUnit value);

			/**
			* \brief Sets the maximum number of retries for the commit operation
			*
			* \param value The number of retries before giving up
			*
			* \remark Setting value to 0 is equivalent to 1, i.e. it will try at least once
			*/
			void set_maximum_retries(size_t value);

			/**
			* \brief Executes an action and backs off if it fails
			*
			* This will call the functor and will retry in case it returns false
			*
			* \param callback The action to be executed
			*/
			template <typename Functor>
			void perform(const Functor& callback) {
				TimeUnit backoff = initial_backoff_;
				size_t retries = maximum_retries_;
				while (retries--) {
					auto start = std::chrono::steady_clock::now();
					// If the callback returns true, we're done
					if (callback()) {
						return; //success
					}
					auto end = std::chrono::steady_clock::now();
					auto time_elapsed = end - start;
					// If we still have time left, then sleep
					if (time_elapsed < backoff) {
						std::this_thread::sleep_for(backoff - time_elapsed);
					}
					// Increase out backoff depending on the policy being used
					backoff = increase_backoff(backoff);
				}
				// No more retries left or we have a terminal error.
				throw ActionTerminatedException("Commit failed: no more retries.");
			}
		private:
			TimeUnit increase_backoff(TimeUnit backoff);

			TimeUnit initial_backoff_;
			TimeUnit backoff_step_;
			TimeUnit maximum_backoff_;
			BackoffPolicy policy_;
			size_t maximum_retries_;
		};
	}
}
#endif // !SYSTEM_KAFKA_BACKOFFPERFORMER_H
