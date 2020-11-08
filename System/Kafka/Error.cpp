///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Kafka/Error.h"
namespace System
{
	namespace Kafka
	{
		Error::Error(rd_kafka_resp_err_t error)
			: error_(error) {

		}

		rd_kafka_resp_err_t Error::get_error() const {
			return error_;
		}

		std::string Error::to_string() const {
			return rd_kafka_err2str(error_);
		}

		Error::operator bool() const {
			return error_ != RD_KAFKA_RESP_ERR_NO_ERROR;
		}

		bool Error::operator==(const Error& rhs) const {
			return error_ == rhs.error_;
		}

		bool Error::operator!=(const Error& rhs) const {
			return !(*this == rhs);
		}

		std::ostream& operator<<(std::ostream& output, const Error& rhs) {
			return output << rhs.to_string();
		}
	}
}