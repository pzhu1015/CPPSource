///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_KAFKA_CLONABLEPTR_H
#define SYSTEM_KAFKA_CLONABLEPTR_H
#include <memory>
namespace System
{
	namespace Kafka
	{
		/**
		* Smart pointer which allows copying via a clone functor
		*/
		template <typename T, typename Deleter, typename Cloner>
		class ClonablePtr {
		public:
			/**
			* \brief Creates an instance
			*
			* \param ptr The pointer to be wrapped
			* \param deleter The deleter functor
			* \param cloner The clone functor
			*/
			ClonablePtr(T* ptr, const Deleter& deleter, const Cloner& cloner)
				: handle_(ptr, deleter), cloner_(cloner) {

			}

			/**
			* \brief Copies the given ClonablePtr
			*
			* Cloning will be done by invoking the Cloner type
			*
			* \param rhs The pointer to be copied
			*/
			ClonablePtr(const ClonablePtr& rhs)
				: handle_(std::unique_ptr<T, Deleter>(rhs.try_clone(), rhs.get_deleter())),
				cloner_(rhs.get_cloner()) {

			}

			/**
			* \brief Copies and assigns the given pointer
			*
			* \param rhs The pointer to be copied
			*/
			ClonablePtr& operator=(const ClonablePtr& rhs) {
				if (this != &rhs) {
					handle_ = std::unique_ptr<T, Deleter>(rhs.try_clone(), rhs.get_deleter());
					cloner_ = rhs.get_cloner();
				}
				return *this;
			}

			ClonablePtr(ClonablePtr&&) = default;
			ClonablePtr& operator=(ClonablePtr&&) = default;
			~ClonablePtr() = default;

			/**
			* \brief Getter for the internal pointer
			*/
			T* get() const {
				return handle_.get();
			}

			/**
			* \brief Releases ownership of the internal pointer
			*/
			T* release() {
				return handle_.release();
			}

			/**
			* \brief Reset the internal pointer to a new one
			*/
			void reset(T* ptr) {
				handle_.reset(ptr);
			}

			/**
			* \brief Get the deleter
			*/
			const Deleter& get_deleter() const {
				return handle_.get_deleter();
			}

			/**
			* \brief Get the cloner
			*/
			const Cloner& get_cloner() const {
				return cloner_;
			}

			/**
			* \brief Indicates whether this ClonablePtr instance is valid (not null)
			*/
			explicit operator bool() const {
				return static_cast<bool>(handle_);
			}
		private:
			T* try_clone() const {
				return cloner_ ? cloner_(get()) : get();
			}

			std::unique_ptr<T, Deleter> handle_;
			Cloner cloner_;
		};

	}
}
#endif // !SYSTEM_KAFKA_CLONABLEPTR_H
