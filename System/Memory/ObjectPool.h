///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_MEMORY_OBJECTPOOL_H
#define SYSTEM_MEMORY_OBJECTPOOL_H
#include "System/Base/DllExport.h"
#include "System/Base/NoCopy.h"
#include "System/Exceptions/ArgumentOutOfRangeException.h"
#include <assert.h>
#include <queue>
#include <vector>
using namespace System::Exceptions;
namespace System
{
	namespace Memory
	{
		template<typename T>
		class SYSTEM_API ObjectPool : public NoCopy
		{
		public:
			ObjectPool()
			{

			}

			ObjectPool(size_t size)
			{
				Init(size);
			}

			virtual ~ObjectPool()
			{
				for (size_t i=0; i < m_objs.size(); i++)
				{
					delete[] (T*)m_objs[i];
				}
			}

			void Init(size_t size)
			{
				if (size < 0)
				{
					throw ArgumentOutOfRangeException("size");
				}
				assert(size > 0);
				T* objs = new T[size];
				m_objs.push_back(objs);
				for (size_t i = 0; i < size; i++)
				{
					m_pool.push(&objs[i]);
				}
				m_size += size;
			}
			
			T& Allocate()
			{
				if (m_pool.empty())
				{
					//allocate
					Init(m_size);
				}
				T* obj = m_pool.front();
				m_pool.pop();
				return (*obj);
			}

			void Release(T& obj)
			{
				m_pool.push(&obj);
			}
		private:
			size_t m_size;
			std::queue<T*> m_pool;
			std::vector<T*> m_objs;
		};
	}
}
#endif // !SYSTEM_MEMORY_OBJECTPOOL_H
