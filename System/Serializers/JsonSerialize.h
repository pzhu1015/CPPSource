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
#include "System/Exceptions/OverflowException.h"
#include "System/Reflections/Reflection.h"
#include <type_traits>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <memory>
using namespace System::Jsons;
using namespace System::Exceptions;

#define SERIALIZE_TO(json, name) JsonSerialize::SerializeTo(json, #name, name);
#define SERIALIZE_FROM(json, name) JsonSerialize::SerializeFrom(json, #name, name);
namespace System
{
	namespace Serializers
	{
		class SYSTEM_API JsonSerialize
		{
		public:
			virtual void SerializeTo(CJsonObject &json) = 0;

			virtual void SerializeFrom(CJsonObject &json) = 0;

			template <class T, class = typename std::enable_if<
				std::is_same<T, std::string>::value ||
				std::is_same<T, bool>::value ||
				std::is_same<T, float>::value ||
				std::is_same<T, double>::value ||
				std::is_same<T, __int8>::value ||
				std::is_same<T, __int16>::value ||
				std::is_same<T, __int32>::value ||
				std::is_same<T, __int64>::value ||
				std::is_same<T, unsigned __int8>::value ||
				std::is_same<T, unsigned __int16>::value ||
				std::is_same<T, unsigned __int32>::value ||
				std::is_same<T, unsigned __int64>::value>::type>
			static void SerializeTo(CJsonObject &json, const std::string &name, T & value)
			{
				json.Add(name, value);
			}

			template <class T, class B = JsonSerialize, class = typename std::enable_if<std::is_base_of<B, T>::value>::type>
			static void SerializeTo(CJsonObject &json, const std::string &name, T & value)
			{
				json.AddEmptySubObject(name);
				value.SerializeTo(json[name]);
			}

			template <class T, class B = JsonSerialize, class = typename std::enable_if<std::is_base_of<B, T>::value>::type>
			static void SerializeTo(CJsonObject &json, const std::string &name, std::shared_ptr<T> & value)
			{
				json.AddEmptySubObject(name);
				value->SerializeTo(json[name]);
			}

			//vector type
			template <class T, class = typename std::enable_if<
			std::is_same<T, std::string>::value ||
			std::is_same<T, bool>::value ||
			std::is_same<T, float>::value ||
			std::is_same<T, double>::value ||
			std::is_same<T, __int8>::value ||
			std::is_same<T, __int16>::value ||
			std::is_same<T, __int32>::value ||
			std::is_same<T, __int64>::value ||
			std::is_same<T, unsigned __int8>::value ||
			std::is_same<T, unsigned __int16>::value ||
			std::is_same<T, unsigned __int32>::value ||
			std::is_same<T, unsigned __int64>::value>::type>
			static void SerializeTo(CJsonObject &json, const std::string &name, std::vector<T> & value)
			{
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}

			//list type
			template <class T, class = typename std::enable_if<
			std::is_same<T, std::string>::value ||
			std::is_same<T, bool>::value ||
			std::is_same<T, float>::value ||
			std::is_same<T, double>::value ||
			std::is_same<T, __int8>::value ||
			std::is_same<T, __int16>::value ||
			std::is_same<T, __int32>::value ||
			std::is_same<T, __int64>::value ||
			std::is_same<T, unsigned __int8>::value ||
			std::is_same<T, unsigned __int16>::value ||
			std::is_same<T, unsigned __int32>::value ||
			std::is_same<T, unsigned __int64>::value>::type>
			static void SerializeTo(CJsonObject &json, const std::string &name, std::list<T> & value)
			{
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}

			//set type
			template <class T, class = typename std::enable_if<
			std::is_same<T, std::string>::value ||
			std::is_same<T, bool>::value ||
			std::is_same<T, float>::value ||
			std::is_same<T, double>::value ||
			std::is_same<T, __int8>::value ||
			std::is_same<T, __int16>::value ||
			std::is_same<T, __int32>::value ||
			std::is_same<T, __int64>::value ||
			std::is_same<T, unsigned __int8>::value ||
			std::is_same<T, unsigned __int16>::value ||
			std::is_same<T, unsigned __int32>::value ||
			std::is_same<T, unsigned __int64>::value>::type>
			static void SerializeTo(CJsonObject &json, const std::string &name, std::set<T> & value)
			{
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}

			template <class T, class B = JsonSerialize, class = typename std::enable_if<std::is_base_of<B, T>::value>::type>
			static void SerializeTo(CJsonObject &json, const std::string &name, std::vector<T> & value)
			{
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					CJsonObject json_obj;
					item.SerializeTo(json_obj);
					json[name].Add(json_obj);
				}
			}

			template <class T, class B = JsonSerialize, class = typename std::enable_if<std::is_base_of<B, T>::value>::type>
			static void SerializeTo(CJsonObject &json, const std::string &name, std::list<T> & value)
			{
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					CJsonObject json_obj;
					item.SerializeTo(json_obj);
					json[name].Add(json_obj);
				}
			}

			template <class T, class B = JsonSerialize, class = typename std::enable_if<std::is_base_of<B, T>::value>::type>
			static void SerializeTo(CJsonObject &json, const std::string &name, std::set<T> & value)
			{
				json.AddEmptySubArray(name);
				for (auto item : value)
				{
					CJsonObject json_obj;
					item.SerializeTo(json_obj);
					json[name].Add(json_obj);
				}
			}

			template <class T, class B = JsonSerialize, class = typename std::enable_if<std::is_base_of<B, T>::value>::type>
			static void SerializeTo(CJsonObject &json, const std::string &name, std::vector<std::shared_ptr<T>> & value)
			{
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					CJsonObject json_obj;
					item->SerializeTo(json_obj);
					json[name].Add(json_obj);
				}
			}

			template <class T, class B = JsonSerialize, class = typename std::enable_if<std::is_base_of<B, T>::value>::type>
			static void SerializeTo(CJsonObject &json, const std::string &name, std::list<std::shared_ptr<T>> & value)
			{
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					CJsonObject json_obj;
					item->SerializeTo(json_obj);
					json[name].Add(json_obj);
				}
			}

			template <class T, class B = JsonSerialize, class = typename std::enable_if<std::is_base_of<B, T>::value>::type>
			static void SerializeTo(CJsonObject &json, const std::string &name, std::set<std::shared_ptr<T>> & value)
			{
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					CJsonObject json_obj;
					item->SerializeTo(json_obj);
					json[name].Add(json_obj);
				}
			}
			///////////////////////////////////////////////////////////////////////////////
			static void SerializeFrom(CJsonObject &json, const std::string &name, __int8 & value)
			{
				if (!json.IsNull(name))
				{
					__int32 v = 0;
					json.Get(name, v);
					if (v > INT8_MAX || v < INT8_MIN)
					{
						throw OverflowException("__int32 conver to __int8 " + v);
					}
					value = (__int8)v;
				}
			}

			static void SerializeFrom(CJsonObject &json, const std::string &name, __int16 & value)
			{
				if (!json.IsNull(name))
				{
					__int32 v = 0;
					json.Get(name, v);
					if (v > INT16_MAX || v < INT16_MIN)
					{
						throw OverflowException("__int32 conver to __int16 " + v);
					}
					value = (__int16)v;
				}
			}

			static void SerializeFrom(CJsonObject &json, const std::string &name, __int32 & value)
			{
				json.Get(name, value);
			}

			static void SerializeFrom(CJsonObject &json, const std::string &name, __int64 & value)
			{
				json.Get(name, value);
			}

			static void SerializeFrom(CJsonObject &json, const std::string &name, unsigned __int8 & value)
			{
				if (!json.IsNull(name))
				{
					unsigned __int32 v = 0;
					json.Get(name, v);
					if (v > UINT8_MAX)
					{
						throw OverflowException("unsigned __int32 conver to unsigned __int8 " + v);
					}
					value = (unsigned __int8)v;
				}
			}

			static void SerializeFrom(CJsonObject &json, const std::string &name, unsigned __int16 & value)
			{
				if (!json.IsNull(name))
				{
					unsigned __int32 v = 0;
					json.Get(name, v);
					if (v > UINT16_MAX)
					{
						throw OverflowException("unsigned __int32 conver to unsigned __int16 " + v);
					}
					value = (unsigned __int16)v;
				}
			}

			static void SerializeFrom(CJsonObject &json, const std::string &name, unsigned __int32 & value)
			{
				json.Get(name, value);
			}

			static void SerializeFrom(CJsonObject &json, const std::string &name, unsigned __int64 & value)
			{
				json.Get(name, value);
			}

			static void SerializeFrom(CJsonObject &json, const std::string &name, bool & value)
			{
				json.Get(name, value);
			}

			static void SerializeFrom(CJsonObject &json, const std::string &name, float & value)
			{
				json.Get(name, value);
			}

			static void SerializeFrom(CJsonObject &json, const std::string &name, double & value)
			{
				json.Get(name, value);
			}

			static void SerializeFrom(CJsonObject &json, const std::string &name, std::string & value)
			{
				json.Get(name, value);
			}

			template <class T, class B = JsonSerialize, class = typename std::enable_if<std::is_base_of<B, T>::value>::type>
			static void SerializeFrom(CJsonObject &json, const std::string &name, T & value)
			{
				if (!json.IsNull(name))
				{
					value.SerializeFrom(json[name]);
				}
			}

			template <class T, class B = JsonSerialize, class = typename std::enable_if<std::is_base_of<B, T>::value>::type>
			static void SerializeFrom(CJsonObject &json, const std::string &name, std::shared_ptr<T> & value)
			{
				if (!json.IsNull(name))
				{
					value->SerializeFrom(json[name]);
				}
			}

			//vector type
			static void SerializeFrom(CJsonObject &json, const std::string &name, std::vector<__int8> & value)
			{
				if (json[name].IsArray())
				{
					__int32 size = json[name].GetArraySize();
					value.resize(size);
					for (__int32 i = 0; i < size; i++)
					{
						__int32 v = 0;
						json[name].Get(i, v);
						if (v > INT8_MAX || v < INT8_MIN)
						{
							throw OverflowException("__int32 conver to __int8 " + v);
						}
						value[i] = (__int8)v;
					}
				}
			}

			static void SerializeFrom(CJsonObject &json, const std::string &name, std::vector<__int16> & value)
			{
				if (json[name].IsArray())
				{
					__int32 size = json[name].GetArraySize();
					value.resize(size);
					for (__int32 i = 0; i < size; i++)
					{
						__int32 v = 0;
						json[name].Get(i, v);
						if (v > INT16_MAX || v < INT16_MIN)
						{
							throw OverflowException("__int32 conver to __int16 " + v);
						}
						value[i] = (__int16)v;
					}
				}
			}

			static void SerializeFrom(CJsonObject &json, const std::string &name, std::vector<__int32> & value)
			{
				if (json[name].IsArray())
				{
					__int32 size = json[name].GetArraySize();
					value.resize(size);
					for (__int32 i = 0; i < size; i++)
					{
						json[name].Get(i, value[i]);
					}
				}
			}

			static void SerializeFrom(CJsonObject &json, const std::string &name, std::vector<__int64> & value)
			{
				if (json[name].IsArray())
				{
					__int32 size = json[name].GetArraySize();
					value.resize(size);
					for (__int32 i = 0; i < size; i++)
					{
						json[name].Get(i, value[i]);
					}
				}
			}

			static void SerializeFrom(CJsonObject &json, const std::string &name, std::vector<unsigned __int8> & value)
			{
				if (json[name].IsArray())
				{
					__int32 size = json[name].GetArraySize();
					value.resize(size);
					for (__int32 i = 0; i < size; i++)
					{
						unsigned __int32 v = 0;
						json[name].Get(i, v);
						if (v > UINT8_MAX)
						{
							throw OverflowException("unsigned __int32 conver to unsigned __int8 " + v);
						}
						value[i] = (unsigned __int8)v;
					}
				}
			}

			static void SerializeFrom(CJsonObject &json, const std::string &name, std::vector<unsigned __int16> & value)
			{
				if (json[name].IsArray())
				{
					__int32 size = json[name].GetArraySize();
					value.resize(size);
					for (__int32 i = 0; i < size; i++)
					{
						unsigned __int32 v = 0;
						json[name].Get(i, v);
						if (v > UINT16_MAX)
						{
							throw OverflowException("unsigned __int32 conver to unsigned __int16 " + v);
						}
						value[i] = (unsigned __int16)v;
					}
				}
			}

			static void SerializeFrom(CJsonObject &json, const std::string &name, std::vector<unsigned __int32> & value)
			{
				if (json[name].IsArray())
				{
					__int32 size = json[name].GetArraySize();
					value.resize(size);
					for (__int32 i = 0; i < size; i++)
					{
						json[name].Get(i, value[i]);
					}
				}
			}

			static void SerializeFrom(CJsonObject &json, const std::string &name, std::vector<unsigned __int64> & value)
			{
				if (json[name].IsArray())
				{
					__int32 size = json[name].GetArraySize();
					value.resize(size);
					for (__int32 i = 0; i < size; i++)
					{
						json[name].Get(i, value[i]);
					}
				}
			}

			static void SerializeFrom(CJsonObject &json, const std::string &name, std::vector<bool> & value)
			{
				if (json[name].IsArray())
				{
					__int32 size = json[name].GetArraySize();
					value.resize(size);
					for (__int32 i = 0; i < size; i++)
					{
						bool v;
						json[name].Get(i, v);
						value[i] = v;
					}
				}
			}

			static void SerializeFrom(CJsonObject &json, const std::string &name, std::vector<float> & value)
			{
				if (json[name].IsArray())
				{
					__int32 size = json[name].GetArraySize();
					value.resize(size);
					for (__int32 i = 0; i < size; i++)
					{
						json[name].Get(i, value[i]);
					}
				}
			}

			static void SerializeFrom(CJsonObject &json, const std::string &name, std::vector<double> & value)
			{
				if (json[name].IsArray())
				{
					__int32 size = json[name].GetArraySize();
					value.resize(size);
					for (__int32 i = 0; i < size; i++)
					{
						json[name].Get(i, value[i]);
					}
				}
			}

			static void SerializeFrom(CJsonObject &json, const std::string &name, std::vector<std::string> & value)
			{
				if (json[name].IsArray())
				{
					__int32 size = json[name].GetArraySize();
					value.resize(size);
					for (__int32 i = 0; i < size; i++)
					{
						json[name].Get(i, value[i]);
					}
				}
			}

			//list type
			static void SerializeFrom(CJsonObject &json, const std::string &name, std::list<__int8> & value)
			{
				if (json[name].IsArray())
				{
					__int32 size = json[name].GetArraySize();
					for (__int32 i = 0; i < size; i++)
					{
						__int32 v;
						json[name].Get(i, v);
						if (v > INT8_MAX || v < INT8_MIN)
						{
							throw OverflowException("__int32 conver to __int8 " + v);
						}
						value.push_back((__int8)v);
					}
				}
			}

			static void SerializeFrom(CJsonObject &json, const std::string &name, std::list<__int16> & value)
			{
				if (json[name].IsArray())
				{
					__int32 size = json[name].GetArraySize();
					for (__int32 i = 0; i < size; i++)
					{
						__int32 v;
						json[name].Get(i, v);
						if (v > INT16_MAX || v < INT16_MIN)
						{
							throw OverflowException("__int32 conver to __int16 " + v);
						}
						value.push_back((__int16)v);
					}
				}
			}

			static void SerializeFrom(CJsonObject &json, const std::string &name, std::list<__int32> & value)
			{
				if (json[name].IsArray())
				{
					__int32 size = json[name].GetArraySize();
					for (__int32 i = 0; i < size; i++)
					{
						__int32 v;
						json[name].Get(i, v);
						value.push_back(v);
					}
				}
			}

			static void SerializeFrom(CJsonObject &json, const std::string &name, std::list<__int64> & value)
			{
				if (json[name].IsArray())
				{
					__int32 size = json[name].GetArraySize();
					for (__int32 i = 0; i < size; i++)
					{
						__int64 v;
						json[name].Get(i, v);
						value.push_back(v);
					}
				}
			}

			static void SerializeFrom(CJsonObject &json, const std::string &name, std::list<unsigned __int8> & value)
			{
				if (json[name].IsArray())
				{
					__int32 size = json[name].GetArraySize();
					for (__int32 i = 0; i < size; i++)
					{
						unsigned __int32 v;
						json[name].Get(i, v);
						if (v > UINT8_MAX)
						{
							throw OverflowException("unsigned __int32 conver to unsigned __int8 " + v);
						}
						value.push_back((unsigned __int8)v);
					}
				}
			}

			static void SerializeFrom(CJsonObject &json, const std::string &name, std::list<unsigned __int16> & value)
			{
				if (json[name].IsArray())
				{
					__int32 size = json[name].GetArraySize();
					for (__int32 i = 0; i < size; i++)
					{
						unsigned __int32 v;
						json[name].Get(i, v);
						if (v > UINT16_MAX)
						{
							throw OverflowException("unsigned __int32 conver to unsigned __int16 " + v);
						}
						value.push_back((unsigned __int16)v);
					}
				}
			}

			static void SerializeFrom(CJsonObject &json, const std::string &name, std::list<unsigned __int32> & value)
			{
				if (json[name].IsArray())
				{
					__int32 size = json[name].GetArraySize();
					for (__int32 i = 0; i < size; i++)
					{
						unsigned __int32 v;
						json[name].Get(i, v);
						value.push_back(v);
					}
				}
			}

			static void SerializeFrom(CJsonObject &json, const std::string &name, std::list<unsigned __int64> & value)
			{
				if (json[name].IsArray())
				{
					__int32 size = json[name].GetArraySize();
					for (__int32 i = 0; i < size; i++)
					{
						unsigned __int64 v;
						json[name].Get(i, v);
						value.push_back(v);
					}
				}
			}

			static void SerializeFrom(CJsonObject &json, const std::string &name, std::list<bool> & value)
			{
				if (json[name].IsArray())
				{
					__int32 size = json[name].GetArraySize();
					for (__int32 i = 0; i < size; i++)
					{
						bool v;
						json[name].Get(i, v);
						value.push_back(v);
					}
				}
			}

			static void SerializeFrom(CJsonObject &json, const std::string &name, std::list<float> & value)
			{
				if (json[name].IsArray())
				{
					__int32 size = json[name].GetArraySize();
					for (__int32 i = 0; i < size; i++)
					{
						float v;
						json[name].Get(i, v);
						value.push_back(v);
					}
				}
			}

			static void SerializeFrom(CJsonObject &json, const std::string &name, std::list<double> & value)
			{
				if (json[name].IsArray())
				{
					__int32 size = json[name].GetArraySize();
					for (__int32 i = 0; i < size; i++)
					{
						double v;
						json[name].Get(i, v);
						value.push_back(v);
					}
				}
			}

			static void SerializeFrom(CJsonObject &json, const std::string &name, std::list<std::string> & value)
			{
				if (json[name].IsArray())
				{
					__int32 size = json[name].GetArraySize();
					for (__int32 i = 0; i < size; i++)
					{
						std::string v;
						json[name].Get(i, v);
						value.push_back(v);
					}
				}
			}
			//set type
			static void SerializeFrom(CJsonObject &json, const std::string &name, std::set<__int8> & value)
			{
				if (json[name].IsArray())
				{
					__int32 size = json[name].GetArraySize();
					for (__int32 i = 0; i < size; i++)
					{
						__int32 v;
						json[name].Get(i, v);
						if (v > INT8_MAX || v < INT8_MIN)
						{
							throw OverflowException("__int32 conver to __int8 " + v);
						}
						value.insert((__int8)v);
					}
				}
			}

			static void SerializeFrom(CJsonObject &json, const std::string &name, std::set<__int16> & value)
			{
				if (json[name].IsArray())
				{
					__int32 size = json[name].GetArraySize();
					for (__int32 i = 0; i < size; i++)
					{
						__int32 v;
						json[name].Get(i, v);
						if (v > INT16_MAX || v < INT16_MIN)
						{
							throw OverflowException("__int32 conver to __int16 " + v);
						}
						value.insert((__int16)v);
					}
				}
			}

			static void SerializeFrom(CJsonObject &json, const std::string &name, std::set<__int32> & value)
			{
				if (json[name].IsArray())
				{
					__int32 size = json[name].GetArraySize();
					for (__int32 i = 0; i < size; i++)
					{
						__int32 v;
						json[name].Get(i, v);
						value.insert(v);
					}
				}
			}

			static void SerializeFrom(CJsonObject &json, const std::string &name, std::set<__int64> & value)
			{
				if (json[name].IsArray())
				{
					__int32 size = json[name].GetArraySize();
					for (__int32 i = 0; i < size; i++)
					{
						__int64 v;
						json[name].Get(i, v);
						value.insert(v);
					}
				}
			}

			static void SerializeFrom(CJsonObject &json, const std::string &name, std::set<unsigned __int8> & value)
			{
				if (json[name].IsArray())
				{
					__int32 size = json[name].GetArraySize();
					for (__int32 i = 0; i < size; i++)
					{
						unsigned __int32 v;
						json[name].Get(i, v);
						if (v > UINT8_MAX)
						{
							throw OverflowException("unsigned __int32 conver to unsigned __int8 " + v);
						}
						value.insert((unsigned __int8)v);
					}
				}
			}

			static void SerializeFrom(CJsonObject &json, const std::string &name, std::set<unsigned __int16> & value)
			{
				if (json[name].IsArray())
				{
					__int32 size = json[name].GetArraySize();
					for (__int32 i = 0; i < size; i++)
					{
						unsigned __int32 v;
						json[name].Get(i, v);
						if (v > UINT16_MAX)
						{
							throw OverflowException("unsigned __int32 conver to unsigned __int16 " + v);
						}
						value.insert((unsigned __int16)v);
					}
				}
			}

			static void SerializeFrom(CJsonObject &json, const std::string &name, std::set<unsigned __int32> & value)
			{
				if (json[name].IsArray())
				{
					__int32 size = json[name].GetArraySize();
					for (__int32 i = 0; i < size; i++)
					{
						unsigned __int32 v;
						json[name].Get(i, v);
						value.insert(v);
					}
				}
			}

			static void SerializeFrom(CJsonObject &json, const std::string &name, std::set<unsigned __int64> & value)
			{
				if (json[name].IsArray())
				{
					__int32 size = json[name].GetArraySize();
					for (__int32 i = 0; i < size; i++)
					{
						unsigned __int64 v;
						json[name].Get(i, v);
						value.insert(v);
					}
				}
			}

			static void SerializeFrom(CJsonObject &json, const std::string &name, std::set<bool> & value)
			{
				if (json[name].IsArray())
				{
					__int32 size = json[name].GetArraySize();
					for (__int32 i = 0; i < size; i++)
					{
						bool v;
						json[name].Get(i, v);
						value.insert(v);
					}
				}
			}

			static void SerializeFrom(CJsonObject &json, const std::string &name, std::set<float> & value)
			{
				if (json[name].IsArray())
				{
					__int32 size = json[name].GetArraySize();
					for (__int32 i = 0; i < size; i++)
					{
						float v;
						json[name].Get(i, v);
						value.insert(v);
					}
				}
			}

			static void SerializeFrom(CJsonObject &json, const std::string &name, std::set<double> & value)
			{
				if (json[name].IsArray())
				{
					__int32 size = json[name].GetArraySize();
					for (__int32 i = 0; i < size; i++)
					{
						double v;
						json[name].Get(i, v);
						value.insert(v);
					}
				}
			}

			static void SerializeFrom(CJsonObject &json, const std::string &name, std::set<std::string> & value)
			{
				if (json[name].IsArray())
				{
					__int32 size = json[name].GetArraySize();
					for (__int32 i = 0; i < size; i++)
					{
						std::string v;
						json[name].Get(i, v);
						value.insert(v);
					}
				}
			}

			template <class T, class B = JsonSerialize, class = typename std::enable_if<std::is_base_of<B, T>::value>::type>
			static void SerializeFrom(CJsonObject &json, const std::string &name, std::vector<T> & value)
			{				
				if (json[name].IsArray())
				{
					__int32 size = json[name].GetArraySize();
					for (__int32 i = 0; i < size; i++)
					{
						CJsonObject json_obj;
						json[name].Get(i, json_obj);
						T obj;
						obj.SerializeFrom(json_obj);
						value.push_back(obj);
					}

				}
			}

			template <class T, class B = JsonSerialize, class = typename std::enable_if<std::is_base_of<B, T>::value>::type>
			static void SerializeFrom(CJsonObject &json, const std::string &name, std::list<T> & value)
			{
				if (json[name].IsArray())
				{
					__int32 size = json[name].GetArraySize();
					for (__int32 i = 0; i < size; i++)
					{
						CJsonObject json_obj;
						json[name].Get(i, json_obj);
						T obj;
						obj.SerializeFrom(json_obj);
						value.push_back(obj);
					}
				}
			}

			template <class T, class B = JsonSerialize, class = typename std::enable_if<std::is_base_of<B, T>::value>::type>
			static void SerializeFrom(CJsonObject &json, const std::string &name, std::set<T> & value)
			{
				if (json[name].IsArray())
				{
					__int32 size = json[name].GetArraySize();
					for (__int32 i = 0; i < size; i++)
					{
						CJsonObject json_obj;
						json[name].Get(i, json_obj);
						T obj;
						obj.SerializeFrom(json_obj);
						value.insert(obj);
					}
				}
			}

			template <class T, class B = JsonSerialize, class = typename std::enable_if<std::is_base_of<B, T>::value>::type>
			static void SerializeFrom(CJsonObject &json, const std::string &name, std::vector<std::shared_ptr<T>> & value)
			{
				if (json[name].IsArray())
				{
					__int32 size = json[name].GetArraySize();
					for (__int32 i = 0; i < size; i++)
					{
						CJsonObject json_obj;
						json[name].Get(i, json_obj);
						std::shared_ptr<T> obj = std::make_shared<T>();
						obj->SerializeFrom(json_obj);
						value.push_back(obj);
					}

				}
			}

			template <class T, class B = JsonSerialize, class = typename std::enable_if<std::is_base_of<B, T>::value>::type>
			static void SerializeFrom(CJsonObject &json, const std::string &name, std::list<std::shared_ptr<T>> & value)
			{
				if (json[name].IsArray())
				{
					__int32 size = json[name].GetArraySize();
					for (__int32 i = 0; i < size; i++)
					{
						CJsonObject json_obj;
						json[name].Get(i, json_obj);
						std::shared_ptr<T> obj = std::make_shared<T>();
						obj->SerializeFrom(json_obj);
						value.push_back(obj);
					}
				}
			}

			template <class T, class B = JsonSerialize, class = typename std::enable_if<std::is_base_of<B, T>::value>::type>
			static void SerializeFrom(CJsonObject &json, const std::string &name, std::set<std::shared_ptr<T>> & value)
			{
				if (json[name].IsArray())
				{
					__int32 size = json[name].GetArraySize();
					for (__int32 i = 0; i < size; i++)
					{
						CJsonObject json_obj;
						json[name].Get(i, json_obj);
						std::shared_ptr<T> obj = std::make_shared<T>();
						obj->SerializeFrom(json_obj);
						value.insert(obj);
					}
				}
			}

		};
	}
}
#endif // !SYSTEM_SERIALIZERS_JSONSERIALIZE_H
