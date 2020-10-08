///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_SERIALIZERS_JSONSERIALIZE_H
#define SYSTEM_SERIALIZERS_JSONSERIALIZE_H
#include "System/Base/DllExport.h"
#include "System/Jsons/CJsonObject.hpp"
#include <type_traits>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <assert.h>
#include <iostream>
using namespace System::Jsons;

#define SERIALIZE_TO(json, name) JsonSerialize::SerializeTo(json, #name, name);
#define SERIALIZE_FROM(json, name) JsonSerialize::SerializeFrom(json, #name, name);
#define SERIALIZE_FROM_VECTOR(json, name) JsonSerialize::SerializeFromVector(json, #name, name);
#define SERIALIZE_FROM_LIST(json, name) JsonSerialize::SerializeFromList(json, #name, name);
#define SERIALIZE_FROM_SET(json, name) JsonSerialize::SerializeFromSet(json, #name, name);
namespace System
{
	namespace Serializers
	{
		class SYSTEM_API JsonSerialize
		{
		public:
			virtual void SerializeTo(CJsonObject &json) = 0;

			virtual void SerializeFrom(CJsonObject &json) = 0;

			//single type
			static void SerializeTo(CJsonObject &json, const std::string &name, char* value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				json.Add(name, value);
			}
			static void SerializeTo(CJsonObject &json, const std::string &name, char &value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				json.Add(name, value);
			}
			static void SerializeTo(CJsonObject &json, const std::string &name, int & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				json.Add(name, value);
			}
			static void SerializeTo(CJsonObject &json, const std::string &name, uint32_t & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				json.Add(name, value);
			}
			static void SerializeTo(CJsonObject &json, const std::string &name, int64_t & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				json.Add(name, value);
			}
			static void SerializeTo(CJsonObject &json, const std::string &name, uint64_t & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				json.Add(name, value);
			}
			static void SerializeTo(CJsonObject &json, const std::string &name, bool & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				json.Add(name, value);
			}
			static void SerializeTo(CJsonObject &json, const std::string &name, float & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				json.Add(name, value);
			}
			static void SerializeTo(CJsonObject &json, const std::string &name, double & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				json.Add(name, value);
			}
			static void SerializeTo(CJsonObject &json, const std::string &name, std::string & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				json.Add(name, value);
			}
			template <class T, class B = JsonSerialize, class = typename std::enable_if<std::is_base_of<B, T>::value>::type>
			static void SerializeTo(CJsonObject &json, const std::string &name, T & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				json.AddEmptySubObject(name);
				value.SerializeTo(json[name]);
			}
			//vector type
			static void SerializeTo(CJsonObject &json, const std::string &name, std::vector<int> & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}
			static void SerializeTo(CJsonObject &json, const std::string &name, std::vector<uint32_t> & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}
			static void SerializeTo(CJsonObject &json, const std::string &name, std::vector<int64_t> & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}
			static void SerializeTo(CJsonObject &json, const std::string &name, std::vector<uint64_t> & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}
			static void SerializeTo(CJsonObject &json, const std::string &name, std::vector<bool> & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}
			static void SerializeTo(CJsonObject &json, const std::string &name, std::vector<float> & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}
			static void SerializeTo(CJsonObject &json, const std::string &name, std::vector<double> & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}
			static void SerializeTo(CJsonObject &json, const std::string &name, std::vector<std::string> & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				json.AddEmptySubArray(name);
				for (auto item : value)
				{
					json[name].Add(item);
				}
			}
			//list type
			static void SerializeTo(CJsonObject &json, const std::string &name, std::list<int> & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}
			static void SerializeTo(CJsonObject &json, const std::string &name, std::list<uint32_t> & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}
			static void SerializeTo(CJsonObject &json, const std::string &name, std::list<int64_t> & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}
			static void SerializeTo(CJsonObject &json, const std::string &name, std::list<uint64_t> & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}
			static void SerializeTo(CJsonObject &json, const std::string &name, std::list<bool> & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}
			static void SerializeTo(CJsonObject &json, const std::string &name, std::list<float> & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}
			static void SerializeTo(CJsonObject &json, const std::string &name, std::list<double> & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}
			static void SerializeTo(CJsonObject &json, const std::string &name, std::list<std::string> & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				json.AddEmptySubArray(name);
				for (auto item : value)
				{
					json[name].Add(item);
				}
			}
			//set type
			static void SerializeTo(CJsonObject &json, const std::string &name, std::set<int> & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}
			static void SerializeTo(CJsonObject &json, const std::string &name, std::set<uint32_t> & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}
			static void SerializeTo(CJsonObject &json, const std::string &name, std::set<int64_t> & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}
			static void SerializeTo(CJsonObject &json, const std::string &name, std::set<uint64_t> & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}
			static void SerializeTo(CJsonObject &json, const std::string &name, std::set<bool> & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}
			static void SerializeTo(CJsonObject &json, const std::string &name, std::set<float> & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}
			static void SerializeTo(CJsonObject &json, const std::string &name, std::set<double> & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}
			static void SerializeTo(CJsonObject &json, const std::string &name, std::set<std::string> & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				json.AddEmptySubArray(name);
				for (auto item : value)
				{
					json[name].Add(item);
				}
			}

			template <class T, class = typename std::enable_if<
				std::is_same<T, std::vector<std::decay<decltype(*(std::declval<T>().begin()))>::type>>::value
				|| std::is_same<T, std::list<std::decay<decltype(*(std::declval<T>().begin()))>::type>>::value
				|| std::is_same<T, std::set<std::decay<decltype(*(std::declval<T>().begin()))>::type>>::value
				&& std::is_member_function_pointer<decltype(&(std::decay<decltype(*(std::declval<T>().begin()))>::type::SerializeTo))>::value
				&& std::is_member_function_pointer<decltype(&(std::decay<decltype(*(std::declval<T>().begin()))>::type::SerializeFrom))>::value
				&& std::is_base_of<JsonSerialize, std::decay<decltype(*(std::declval<T>().begin()))>::type>::value
			>::type>
				static void SerializeTo(CJsonObject &json, const std::string &name, T & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(T).name() << std::endl;
#endif
				json.AddEmptySubArray(name);
				for (auto item : value)
				{
					CJsonObject json_obj;
					item.SerializeTo(json_obj);
					json[name].Add(json_obj);
				}
			}
			///////////////////////////////////////////////////////////////////////////////

			//single type
			static void SerializeFrom(CJsonObject &json, const std::string &name, char* value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl; 
#endif
				//TODO: be careful, if value's memory space is not enough, may be crash.
				if (value != nullptr)
				{
					std::string v;
					json.Get(name, v);
					strcpy(value, v.data());
				}
			}
			static void SerializeFrom(CJsonObject &json, const std::string &name, char & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				if (!json.IsNull(name))
				{
					int v = 0;
					json.Get(name, v);
					value = (char)v;
				}
			}
			static void SerializeFrom(CJsonObject &json, const std::string &name, int & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				json.Get(name, value);
			}
			static void SerializeFrom(CJsonObject &json, const std::string &name, uint32_t & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				json.Get(name, value);
			}
			static void SerializeFrom(CJsonObject &json, const std::string &name, int64_t & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				json.Get(name, value);
			}
			static void SerializeFrom(CJsonObject &json, const std::string &name, uint64_t & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				json.Get(name, value);
			}
			static void SerializeFrom(CJsonObject &json, const std::string &name, bool & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				json.Get(name, value);
			}
			static void SerializeFrom(CJsonObject &json, const std::string &name, float & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				json.Get(name, value);
			}
			static void SerializeFrom(CJsonObject &json, const std::string &name, double & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				json.Get(name, value);
			}
			static void SerializeFrom(CJsonObject &json, const std::string &name, std::string & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				json.Get(name, value);
			}
			template <class T, class B = JsonSerialize, class = typename std::enable_if<std::is_base_of<B, T>::value>::type>
			static void SerializeFrom(CJsonObject &json, const std::string &name, T & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				if (!json.IsNull(name))
				{
					value.SerializeFrom(json[name]);
				}
			}
			//vector type
			static void SerializeFrom(CJsonObject &json, const std::string &name, std::vector<int> & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				if (json[name].IsArray())
				{
					int size = json[name].GetArraySize();
					value.resize(size);
					for (int i = 0; i < size; i++)
					{
						json[name].Get(i, value[i]);
					}
				}
			}
			static void SerializeFrom(CJsonObject &json, const std::string &name, std::vector<uint32_t> & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				if (json[name].IsArray())
				{
					int size = json[name].GetArraySize();
					value.resize(size);
					for (int i = 0; i < size; i++)
					{
						json[name].Get(i, value[i]);
					}
				}
			}
			static void SerializeFrom(CJsonObject &json, const std::string &name, std::vector<int64_t> & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				if (json[name].IsArray())
				{
					int size = json[name].GetArraySize();
					value.resize(size);
					for (int i = 0; i < size; i++)
					{
						json[name].Get(i, value[i]);
					}
				}
			}
			static void SerializeFrom(CJsonObject &json, const std::string &name, std::vector<uint64_t> & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				if (json[name].IsArray())
				{
					int size = json[name].GetArraySize();
					value.resize(size);
					for (int i = 0; i < size; i++)
					{
						json[name].Get(i, value[i]);
					}
				}
			}
			static void SerializeFrom(CJsonObject &json, const std::string &name, std::vector<bool> & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				if (json[name].IsArray())
				{
					int size = json[name].GetArraySize();
					value.resize(size);
					for (int i = 0; i < size; i++)
					{
						bool v;
						json[name].Get(i, v);
						value[i] = v;
					}
				}
			}
			static void SerializeFrom(CJsonObject &json, const std::string &name, std::vector<float> & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				if (json[name].IsArray())
				{
					int size = json[name].GetArraySize();
					value.resize(size);
					for (int i = 0; i < size; i++)
					{
						json[name].Get(i, value[i]);
					}
				}
			}
			static void SerializeFrom(CJsonObject &json, const std::string &name, std::vector<double> & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				if (json[name].IsArray())
				{
					int size = json[name].GetArraySize();
					value.resize(size);
					for (int i = 0; i < size; i++)
					{
						json[name].Get(i, value[i]);
					}
				}
			}
			static void SerializeFrom(CJsonObject &json, const std::string &name, std::vector<std::string> & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				if (json[name].IsArray())
				{
					int size = json[name].GetArraySize();
					value.resize(size);
					for (int i = 0; i < size; i++)
					{
						json[name].Get(i, value[i]);
					}
				}
			}
			//list type
			static void SerializeFrom(CJsonObject &json, const std::string &name, std::list<int> & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				if (json[name].IsArray())
				{
					int size = json[name].GetArraySize();
					for (int i = 0; i < size; i++)
					{
						int v;
						json[name].Get(i, v);
						value.push_back(v);
					}
				}
			}
			static void SerializeFrom(CJsonObject &json, const std::string &name, std::list<uint32_t> & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				if (json[name].IsArray())
				{
					int size = json[name].GetArraySize();
					for (int i = 0; i < size; i++)
					{
						uint32_t v;
						json[name].Get(i, v);
						value.push_back(v);
					}
				}
			}
			static void SerializeFrom(CJsonObject &json, const std::string &name, std::list<int64_t> & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				if (json[name].IsArray())
				{
					int size = json[name].GetArraySize();
					for (int i = 0; i < size; i++)
					{
						int64_t v;
						json[name].Get(i, v);
						value.push_back(v);
					}
				}
			}
			static void SerializeFrom(CJsonObject &json, const std::string &name, std::list<uint64_t> & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				if (json[name].IsArray())
				{
					int size = json[name].GetArraySize();
					for (int i = 0; i < size; i++)
					{
						uint64_t v;
						json[name].Get(i, v);
						value.push_back(v);
					}
				}
			}
			static void SerializeFrom(CJsonObject &json, const std::string &name, std::list<bool> & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				if (json[name].IsArray())
				{
					int size = json[name].GetArraySize();
					for (int i = 0; i < size; i++)
					{
						bool v;
						json[name].Get(i, v);
						value.push_back(v);
					}
				}
			}
			static void SerializeFrom(CJsonObject &json, const std::string &name, std::list<float> & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				if (json[name].IsArray())
				{
					int size = json[name].GetArraySize();
					for (int i = 0; i < size; i++)
					{
						float v;
						json[name].Get(i, v);
						value.push_back(v);
					}
				}
			}
			static void SerializeFrom(CJsonObject &json, const std::string &name, std::list<double> & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				if (json[name].IsArray())
				{
					int size = json[name].GetArraySize();
					for (int i = 0; i < size; i++)
					{
						double v;
						json[name].Get(i, v);
						value.push_back(v);
					}
				}
			}
			static void SerializeFrom(CJsonObject &json, const std::string &name, std::list<std::string> & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				if (json[name].IsArray())
				{
					int size = json[name].GetArraySize();
					for (int i = 0; i < size; i++)
					{
						std::string v;
						json[name].Get(i, v);
						value.push_back(v);
					}
				}
			}
			//set type
			static void SerializeFrom(CJsonObject &json, const std::string &name, std::set<int> & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				if (json[name].IsArray())
				{
					int size = json[name].GetArraySize();
					for (int i = 0; i < size; i++)
					{
						int v;
						json[name].Get(i, v);
						value.insert(v);
					}
				}
			}
			static void SerializeFrom(CJsonObject &json, const std::string &name, std::set<uint32_t> & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				if (json[name].IsArray())
				{
					int size = json[name].GetArraySize();
					for (int i = 0; i < size; i++)
					{
						uint32_t v;
						json[name].Get(i, v);
						value.insert(v);
					}
				}
			}
			static void SerializeFrom(CJsonObject &json, const std::string &name, std::set<int64_t> & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				if (json[name].IsArray())
				{
					int size = json[name].GetArraySize();
					for (int i = 0; i < size; i++)
					{
						int64_t v;
						json[name].Get(i, v);
						value.insert(v);
					}
				}
			}
			static void SerializeFrom(CJsonObject &json, const std::string &name, std::set<uint64_t> & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				if (json[name].IsArray())
				{
					int size = json[name].GetArraySize();
					for (int i = 0; i < size; i++)
					{
						uint64_t v;
						json[name].Get(i, v);
						value.insert(v);
					}
				}
			}
			static void SerializeFrom(CJsonObject &json, const std::string &name, std::set<bool> & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				if (json[name].IsArray())
				{
					int size = json[name].GetArraySize();
					for (int i = 0; i < size; i++)
					{
						bool v;
						json[name].Get(i, v);
						value.insert(v);
					}
				}
			}
			static void SerializeFrom(CJsonObject &json, const std::string &name, std::set<float> & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				if (json[name].IsArray())
				{
					int size = json[name].GetArraySize();
					for (int i = 0; i < size; i++)
					{
						float v;
						json[name].Get(i, v);
						value.insert(v);
					}
				}
			}
			static void SerializeFrom(CJsonObject &json, const std::string &name, std::set<double> & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				if (json[name].IsArray())
				{
					int size = json[name].GetArraySize();
					for (int i = 0; i < size; i++)
					{
						double v;
						json[name].Get(i, v);
						value.insert(v);
					}
				}
			}
			static void SerializeFrom(CJsonObject &json, const std::string &name, std::set<std::string> & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(value).name() << std::endl;
#endif
				if (json[name].IsArray())
				{
					int size = json[name].GetArraySize();
					for (int i = 0; i < size; i++)
					{
						std::string v;
						json[name].Get(i, v);
						value.insert(v);
					}
				}
			}

			template <class T, class = typename std::enable_if<
				std::is_same<T, std::vector<std::decay<decltype(*(std::declval<T>().begin()))>::type>>::value
				&& std::is_member_function_pointer<decltype(&(std::decay<decltype(*(std::declval<T>().begin()))>::type::SerializeFrom))>::value
			>::type>
				static void SerializeFromVector(CJsonObject &json, const std::string &name, T & value)
			{				
#ifdef _DEBUG 
				std::cout << typeid(T).name() << std::endl;
				std::cout << typeid(decltype(*(std::declval<T>().begin()))).name() << std::endl;
#endif		
				if (json[name].IsArray())
				{
					int size = json[name].GetArraySize();
					//assert(std::is_same<T, std::vector<std::decay<decltype(*(std::declval<T>().begin()))>::type>>::value);
					for (int i = 0; i < size; i++)
					{
						CJsonObject json_obj;
						json[name].Get(i, json_obj);
						std::decay<decltype(*(std::declval<T>().begin()))>::type obj;
						obj.SerializeFrom(json_obj);
						value.push_back(obj);
					}

				}
			}

				template <class T, class = typename std::enable_if<
					std::is_same<T, std::list<std::decay<decltype(*(std::declval<T>().begin()))>::type>>::value
					&& std::is_member_function_pointer<decltype(&(std::decay<decltype(*(std::declval<T>().begin()))>::type::SerializeFrom))>::value
				>::type>
				static void SerializeFromList(CJsonObject &json, const std::string &name, T & value)
			{
#ifdef _DEBUG 
					std::cout << typeid(T).name() << std::endl;
					std::cout << typeid(decltype(*(std::declval<T>().begin()))).name() << std::endl;
#endif	
					if (json[name].IsArray())
				{
					int size = json[name].GetArraySize();
					//assert(std::is_same<T, std::list<std::decay<decltype(*(std::declval<T>().begin()))>::type>>::value);
					for (int i = 0; i < size; i++)
					{
						CJsonObject json_obj;
						json[name].Get(i, json_obj);
						std::decay<decltype(*(std::declval<T>().begin()))>::type obj;
						obj.SerializeFrom(json_obj);
						value.push_back(obj);
					}
				}
			}

			template <class T, class = typename std::enable_if<
				std::is_same<T, std::set<std::decay<decltype(*(std::declval<T>().begin()))>::type>>::value
				&& std::is_member_function_pointer<decltype(&(std::decay<decltype(*(std::declval<T>().begin()))>::type::SerializeFrom))>::value
			>::type>
				static void SerializeFromSet(CJsonObject &json, const std::string &name, T & value)
			{
#ifdef _DEBUG 
				std::cout << typeid(T).name() << std::endl;
				std::cout << typeid(decltype(*(std::declval<T>().begin()))).name() << std::endl;
#endif	
				if (json[name].IsArray())
				{
					int size = json[name].GetArraySize();
					//assert(std::is_same<T, std::set<std::decay<decltype(*(std::declval<T>().begin()))>::type>>::value);
					for (int i = 0; i < size; i++)
					{
						CJsonObject json_obj;
						json[name].Get(i, json_obj);
						std::decay<decltype(*(std::declval<T>().begin()))>::type obj;
						obj.SerializeFrom(json_obj);
						value.insert(obj);
					}
				}
			}

		};
	}
}
#endif // !SYSTEM_SERIALIZERS_JSONSERIALIZE_H
