///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_KAFKA_BUFFER_H
#define SYSTEM_KAFKA_BUFFER_H
#include "System/Base/DllExport.h"
#include "System/Kafka/Exceptions.h"
#include <array>
#include <vector>
namespace System
{
	namespace Kafka
	{
		/**
		* \brief Represents a view of a buffer.
		*
		* This is only a view, hence you should convert the contents of a buffer into
		* some other container if you want to store it somewhere.
		*
		* If you're using this to produce a message, you *need* to guarantee that the
		* pointer that this buffer points to will still until the call to Producer::produce
		* returns.
		*/
		class SYSTEM_API Buffer {
		public:
			/**
			* The type of data this buffer points to
			*/
			using DataType = unsigned char;

			/**
			* The const iterator type
			*/
			using const_iterator = const DataType*;

			/**
			* Constructs an empty buffer
			*/
			Buffer();

			/**
			* Constructs a buffer from a pointer and a size
			*
			* \param data A pointer to some type of size 1
			* \param size The size of the buffer
			*/
			template <typename T>
			Buffer(const T* data, size_t size)
				: data_(reinterpret_cast<const DataType*>(data)), size_(size) {
				static_assert(sizeof(T) == sizeof(DataType), "sizeof(T) != sizeof(DataType)");
				if ((data_ == nullptr) && (size_ > 0)) {
					throw Exception("Invalid buffer configuration");
				}
			}

			/**
			* Constructs a buffer from two iterators in the range [first,last)
			*
			* \param first An iterator to the start of data
			* \param last An iterator to the end of data (not included)
			*/
			template <typename Iter>
			Buffer(const Iter first, const Iter last)
				: Buffer(&*first, std::distance(first, last)) {
			}

			/**
			* Constructs a buffer from a vector
			*
			* \param data The vector to be used as input
			*/
			template <typename T>
			Buffer(const std::vector<T>& data)
				: data_(data.data()), size_(data.size()) {
				static_assert(sizeof(T) == sizeof(DataType), "sizeof(T) != sizeof(DataType)");
			}

			/**
			* Don't allow construction from temporary vectors
			*/
			template <typename T>
			Buffer(std::vector<T>&& data) = delete;

			/**
			* Constructs a buffer from an array
			*
			* \param data The the array to be used as input
			*/
			template <typename T, size_t N>
			Buffer(const std::array<T, N>& data)
				: data_(reinterpret_cast<const DataType*>(data.data())), size_(data.size()) {
				static_assert(sizeof(T) == sizeof(DataType), "sizeof(T) != sizeof(DataType)");
			}

			/**
			* Don't allow construction from temporary arrays
			*/
			template <typename T, size_t N>
			Buffer(std::array<T, N>&& data) = delete;

			/**
			* Constructs a buffer from a raw array
			*
			* \param data The the array to be used as input
			*/
			template <typename T, size_t N>
			Buffer(const T(&data)[N])
				: Buffer(data, N) {
			}

			// Don't allow construction from temporary raw arrays
			template <typename T, size_t N>
			Buffer(T(&&data)[N]) = delete;

			/**
			* \brief Construct a buffer from a const string ref
			*
			* Note that you *can't use temporaries* here as they would be destructed after
			* the constructor finishes.
			*/
			Buffer(const std::string& data);

			/**
			* Don't allow construction from temporary strings
			*/
			Buffer(std::string&&) = delete;

			Buffer(const Buffer&) = delete;
			Buffer(Buffer&&) = default;
			Buffer& operator=(const Buffer&) = delete;
			Buffer& operator=(Buffer&&) = default;

			/**
			* Getter for the data pointer
			*/
			const DataType* get_data() const;

			/**
			* Getter for the size of the buffer
			*/
			size_t get_size() const;

			/**
			* Gets an iterator to the beginning of this buffer
			*/
			const_iterator begin() const;

			/**
			* Gets an iterator to the end of this buffer
			*/
			const_iterator end() const;

			/**
			* Checks whether this is a non empty buffer
			*/
			explicit operator bool() const;

			/**
			* Converts the contents of the buffer into a string
			*/
			operator std::string() const;

			/**
			* \brief Converts the contents of the buffer into a vector.
			*
			* The vector must contain some type of size 1 (e.g. uint8_t, char, etc).
			*/
			template <typename T>
			operator std::vector<T>() const {
				static_assert(sizeof(T) == sizeof(DataType), "sizeof(T) != sizeof(DataType)");
				return std::vector<T>(data_, data_ + size_);
			}

			/**
			* Output operator
			*/
			SYSTEM_API friend std::ostream& operator<<(std::ostream& output, const Buffer& rhs);
		private:
			const DataType* data_;
			size_t size_;
		};

		/**
		* Compares Buffer objects for equality
		*/
		SYSTEM_API bool operator==(const Buffer& lhs, const Buffer& rhs);

		/**
		* Compares Buffer objects for inequality
		*/
		SYSTEM_API bool operator!=(const Buffer& lhs, const Buffer& rhs);

		/**
		* Compares Buffer objects lexicographically
		*/
		SYSTEM_API bool operator<(const Buffer& lhs, const Buffer& rhs);
		SYSTEM_API bool operator<=(const Buffer& lhs, const Buffer& rhs);
		SYSTEM_API bool operator>(const Buffer& lhs, const Buffer& rhs);
		SYSTEM_API bool operator>=(const Buffer& lhs, const Buffer& rhs);
	}
}
#endif // !SYSTEM_KAFKA_BUFFER_H
