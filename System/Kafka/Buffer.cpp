///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Kafka/Buffer.h"
#include <algorithm>
#include <iostream>
#include <iomanip>

using std::string;
using std::equal;
using std::lexicographical_compare;
using std::ostream;
using std::hex;
using std::dec;
namespace System
{
	namespace Kafka
	{
		Buffer::Buffer()
			: data_(nullptr), size_(0) {

		}

		Buffer::Buffer(const string& data)
			: Buffer(data.data(), data.size()) {

		}

		const Buffer::DataType* Buffer::get_data() const {
			return data_;
		}

		size_t Buffer::get_size() const {
			return size_;
		}

		Buffer::const_iterator Buffer::begin() const {
			return data_;
		}

		Buffer::const_iterator Buffer::end() const {
			return data_ + size_;
		}

		Buffer::operator bool() const {
			return size_ != 0;
		}

		Buffer::operator string() const {
			return string(data_, data_ + size_);
		}

		ostream& operator<<(ostream& output, const Buffer& rhs) {
			for (const uint8_t value : rhs) {
				if (value >= 0x20 && value < 0x7f) {
					output << value;
				}
				else {
					output << "\\x";
					if (value < 16) {
						output << '0';
					}
					output << hex << static_cast<int>(value) << dec;
				}
			}
			return output;
		}

		bool operator==(const Buffer& lhs, const Buffer& rhs) {
			if (lhs.get_size() != rhs.get_size()) {
				return false;
			}
			return equal(lhs.get_data(), lhs.get_data() + lhs.get_size(), rhs.get_data());
		}

		bool operator!=(const Buffer& lhs, const Buffer& rhs) {
			return !(lhs == rhs);
		}

		bool operator<(const Buffer& lhs, const Buffer& rhs) {
			return lexicographical_compare(lhs.get_data(), lhs.get_data() + lhs.get_size(),
				rhs.get_data(), rhs.get_data() + rhs.get_size());
		}

		bool operator>(const Buffer& lhs, const Buffer& rhs) {
			return lexicographical_compare(rhs.get_data(), rhs.get_data() + rhs.get_size(),
				lhs.get_data(), lhs.get_data() + lhs.get_size());
		}

		bool operator<=(const Buffer& lhs, const Buffer& rhs) {
			return !(lhs > rhs);
		}

		bool operator>=(const Buffer& lhs, const Buffer& rhs) {
			return !(lhs < rhs);
		}

	}
}