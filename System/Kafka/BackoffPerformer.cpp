///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Kafka/BackoffPerformer.h"
#include <algorithm>
#include <limits>
using std::min;
using std::numeric_limits;
#ifdef _MINWINDEF_
#undef _MINWINDEF_
#endif // _MINWINDEF_

namespace System
{
	namespace Kafka
	{
		const BackoffPerformer::TimeUnit BackoffPerformer::DEFAULT_INITIAL_BACKOFF{ 100 };
		const BackoffPerformer::TimeUnit BackoffPerformer::DEFAULT_BACKOFF_STEP{ 50 };
		const BackoffPerformer::TimeUnit BackoffPerformer::DEFAULT_MAXIMUM_BACKOFF{ 1000 };
		const size_t BackoffPerformer::DEFAULT_MAXIMUM_RETRIES{ (numeric_limits<size_t>::max)() };

		BackoffPerformer::BackoffPerformer()
			: initial_backoff_(DEFAULT_INITIAL_BACKOFF),
			backoff_step_(DEFAULT_BACKOFF_STEP), maximum_backoff_(DEFAULT_MAXIMUM_BACKOFF),
			policy_(BackoffPolicy::LINEAR), maximum_retries_(DEFAULT_MAXIMUM_RETRIES) {

		}

		void BackoffPerformer::set_backoff_policy(BackoffPolicy policy) {
			policy_ = policy;
		}

		void BackoffPerformer::set_initial_backoff(TimeUnit value) {
			initial_backoff_ = value;
		}

		void BackoffPerformer::set_backoff_step(TimeUnit value) {
			backoff_step_ = value;
		}

		void BackoffPerformer::set_maximum_backoff(TimeUnit value) {
			maximum_backoff_ = value;
		}

		void BackoffPerformer::set_maximum_retries(size_t value) {
			maximum_retries_ = value == 0 ? 1 : value;
		}

		BackoffPerformer::TimeUnit BackoffPerformer::increase_backoff(TimeUnit backoff) {
			if (policy_ == BackoffPolicy::LINEAR) {
				backoff = backoff + backoff_step_;
			}
			else {
				backoff = backoff * 2;
			}
			return min(backoff, maximum_backoff_);
		}

	}
}