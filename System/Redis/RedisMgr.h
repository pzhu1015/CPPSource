///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_REDIS_REDISMGR_H
#define SYSTEM_REDIS_REDISMGR_H
#include "System/Base/DllExport.h"
#include <string>
#include <map>
#include <vector>
namespace System
{
	namespace Redis
	{
		class SYSTEM_API RedisMgr
		{
		public:
			static RedisMgr& GetInstance()
			{
				static RedisMgr instance;
				return instance;
			}

			bool Start();

			bool Stop();

			bool Set(const std::string &key, const std::string &value);

			std::string Get(const std::string &key);

			//return 1: key exist
			//return 0: key not exist
			//return -1: error
			int Delete(const std::string &key);

			bool Exist(const std::string &key);

			//map
			bool HSet(const std::string &key, const std::string &field, const std::string &value);

			bool HDel(const std::string &key, const std::vector<std::string> &fields);

			bool HExist(const std::string &key, const std::string &field);

			bool HIncrement(const std::string &key, const std::string &field, int value);

			bool HIncrement(const std::string &key, const std::string &field, float value);

			//return current map.length()
			int64_t HLength(const std::string &key);

			std::vector<std::string> HKeys(const std::string &key);

			std::vector<std::string> HValues(const std::string &key);

			std::string HGet(const std::string key, const std::string &field);

			std::map<std::string, std::string> HGetAll(const std::string &key);

			//return current bitset.length()
			int64_t BitCount(const std::string &key);

			//return old value
			int SetBit(const std::string &key, int offset, int value);

			//return 0,1
			int GetBit(const std::string &key, int offset);
		};
	}
}
#endif // !SYSTEM_REDIS_REDISMGR_H
