///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_KAFKA_HEADERITERATOR_H
#define SYSTEM_KAFKA_HEADERITERATOR_H
#include "System/Kafka/Header.h"
#if (RD_KAFKA_VERSION >= RD_KAFKA_HEADERS_SUPPORT_VERSION)
namespace System
{
	namespace Kafka
	{
		template <typename HeaderType>
		class HeaderList;

		template <typename HeaderType>
		class HeaderIterator;

		template <typename HeaderType>
		bool operator==(const HeaderIterator<HeaderType>& lhs, const HeaderIterator<HeaderType>& rhs);

		/**
		* \brief Iterator over a HeaderList object.
		* \tparam HeaderType The type of header this iterator points to.
		*/
		template <typename HeaderType>
		class HeaderIterator {
		public:
			friend HeaderList<HeaderType>;
			using HeaderListType = HeaderList<HeaderType>;
			using BufferType = typename HeaderType::ValueType;
			//std::iterator_traits
			using difference_type = std::ptrdiff_t;
			using value_type = HeaderType;
			using pointer = value_type*;
			using reference = value_type&;
			using iterator_category = std::bidirectional_iterator_tag;
			friend bool operator==<HeaderType>(const HeaderIterator<HeaderType>& lhs,
				const HeaderIterator<HeaderType>& rhs);

			HeaderIterator(const HeaderIterator& other)
				: header_list_(other.header_list_),
				header_(make_header(other.header_)),
				index_(other.index_) {

			}
			HeaderIterator& operator=(const HeaderIterator& other) {
				if (this == &other) return *this;
				header_list_ = other.header_list_;
				header_ = make_header(other.header_);
				index_ = other.index_;
				return *this;
			}
			HeaderIterator(HeaderIterator&&) = default;
			HeaderIterator& operator=(HeaderIterator&&) = default;

			/**
			* \brief Prefix increment of the iterator.
			* \return Itself after being incremented.
			*/
			HeaderIterator& operator++() {
				assert(index_ < header_list_.size());
				++index_;
				return *this;
			}

			/**
			* \brief Postfix increment of the iterator.
			* \return Itself before being incremented.
			*/
			HeaderIterator operator++(int) {
				HeaderIterator tmp(*this);
				operator++();
				return tmp;
			}

			/**
			* \brief Prefix decrement of the iterator.
			* \return Itself after being decremented.
			*/
			HeaderIterator& operator--() {
				assert(index_ > 0);
				--index_;
				return *this;
			}

			/**
			* \brief Postfix decrement of the iterator.
			* \return Itself before being decremented.
			*/
			HeaderIterator operator--(int) {
				HeaderIterator tmp(*this);
				operator--();
				return tmp;
			}

			/**
			* \brief Dereferences this iterator.
			* \return A reference to the header the iterator points to.
			* \warning Throws if invalid or if *this == end().
			*/
			const HeaderType& operator*() const {
				header_ = header_list_.at(index_);
				return header_;
			}
			HeaderType& operator*() {
				header_ = header_list_.at(index_);
				return header_;
			}

			/**
			* \brief Dereferences this iterator.
			* \return The address to the header the iterator points to.
			* \warning Throws if invalid or if *this == end().
			*/
			const HeaderType* operator->() const {
				header_ = header_list_.at(index_);
				return &header_;
			}
			HeaderType* operator->() {
				header_ = header_list_.at(index_);
				return &header_;
			}

		private:
			HeaderIterator(const HeaderListType& headers,
				size_t index)
				: header_list_(headers),
				index_(index) {
			}

			template <typename T>
			T make_header(const T& other) {
				return other;
			}

			Header<Buffer> make_header(const Header<Buffer>& other) {
				return Header<Buffer>(other.get_name(),
					Buffer(other.get_value().get_data(),
						other.get_value().get_size()));
			}

			const HeaderListType& header_list_;
			HeaderType header_;
			size_t index_;
		};

		// Equality comparison operators
		template <typename HeaderType>
		bool operator==(const HeaderIterator<HeaderType>& lhs, const HeaderIterator<HeaderType>& rhs) {
			return (lhs.header_list_.get_handle() == rhs.header_list_.get_handle()) && (lhs.index_ == rhs.index_);
		}

		template <typename HeaderType>
		bool operator!=(const HeaderIterator<HeaderType>& lhs, const HeaderIterator<HeaderType>& rhs) {
			return !(lhs == rhs);
		}

	}
}

#endif //RD_KAFKA_HEADERS_SUPPORT_VERSION
#endif // !SYSTEM_KAFKA_HEADERITERATOR_H
