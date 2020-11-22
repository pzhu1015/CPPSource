///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_DATA_DBPARAMETERCOLLECTION_H
#define SYSTEM_DATA_DBPARAMETERCOLLECTION_H
#include "System/Data/Ptrs.h"
#include <string>
namespace System
{
	namespace Data
	{
		template <class T>
		class iterator {
		private:
			T _data;
		public:
			iterator(T data_) :
				_data(data)
			{}

			bool operator !=(const iterator& that) {
				return _data == &that;
			}

			iterator& operator ++() {
				_data = _data++;
				return *this;
			}

			T& operator *() {
				return *_data;
			}

			iterator(const iterator&) = delete;
			iterator& operator =(const iterator&) = delete;
			~iterator() = default;
		};
		class DbParameterCollection
		{
		public:
			virtual int GetCount() = 0;
			virtual void Clear() = 0;
			virtual int Add(const DbParameterPtr &value) = 0;
		};
	}
}
#endif // !SYSTEM_DATA_DBPARAMETERCOLLECTION_H
