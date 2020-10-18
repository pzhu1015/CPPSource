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
using namespace System::Reflections;

#define SERIALIZE_TO(json, name) JsonSerialize::SerializeTo(json, #name, name);
#define SERIALIZE_FROM(json, name) JsonSerialize::SerializeFrom(json, #name, name);
namespace System
{
	template <typename T>
	struct is_optional : std::false_type {};

	template <typename T>
	struct is_optional<std::unique_ptr<T>> : std::true_type {};

	template <typename T>
	constexpr bool is_optional_v = is_optional<std::decay_t<T>>::value;

	template <typename T>
	constexpr bool has_schema = std::tuple_size<decltype(StructSchema<T>())>::value;

	namespace Serializers
	{
		class SYSTEM_API JsonSerialize
		{
		public:
			virtual void SerializeTo(CJsonObject &json) = 0;

			virtual void SerializeFrom(CJsonObject &json) = 0;

			//single type
			static void SerializeTo(CJsonObject &json, const std::string &name, __int8 &value)
			{
				json.Add(name, value);
			}

			static void SerializeTo(CJsonObject &json, const std::string &name, __int16 &value)
			{
				json.Add(name, value);
			}

			static void SerializeTo(CJsonObject &json, const std::string &name, __int32 & value)
			{
				json.Add(name, value);
			}

			static void SerializeTo(CJsonObject &json, const std::string &name, __int64 & value)
			{
				json.Add(name, value);
			}

			static void SerializeTo(CJsonObject &json, const std::string &name, unsigned __int8 &value)
			{
				json.Add(name, (unsigned __int32)value);
			}

			static void SerializeTo(CJsonObject &json, const std::string &name, unsigned __int16 &value)
			{
				json.Add(name, (unsigned __int32)value);
			}

			static void SerializeTo(CJsonObject &json, const std::string &name, unsigned __int32 & value)
			{
				json.Add(name, value);
			}

			static void SerializeTo(CJsonObject &json, const std::string &name, unsigned __int64 & value)
			{
				json.Add(name, value);
			}

			static void SerializeTo(CJsonObject &json, const std::string &name, bool & value)
			{
				json.Add(name, value);
			}

			static void SerializeTo(CJsonObject &json, const std::string &name, float & value)
			{
				json.Add(name, value);
			}

			static void SerializeTo(CJsonObject &json, const std::string &name, double & value)
			{
				json.Add(name, value);
			}

			static void SerializeTo(CJsonObject &json, const std::string &name, std::string & value)
			{
				json.Add(name, value);
			}

			template <class T, class B = JsonSerialize, class = typename std::enable_if<std::is_base_of<B, T>::value>::type>
			static void SerializeTo(CJsonObject &json, const std::string &name, T & value)
			{
				json.AddEmptySubObject(name);
				value.SerializeTo(json[name]);
			}

			//vector type
			static void SerializeTo(CJsonObject &json, const std::string &name, std::vector<__int8> & value)
			{
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}

			static void SerializeTo(CJsonObject &json, const std::string &name, std::vector<__int16> & value)
			{
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}

			static void SerializeTo(CJsonObject &json, const std::string &name, std::vector<__int32> & value)
			{
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}

			static void SerializeTo(CJsonObject &json, const std::string &name, std::vector<__int64> & value)
			{
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}

			static void SerializeTo(CJsonObject &json, const std::string &name, std::vector<unsigned __int8> & value)
			{
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add((unsigned __int32)item);
				}
			}

			static void SerializeTo(CJsonObject &json, const std::string &name, std::vector<unsigned __int16> & value)
			{
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add((unsigned __int32)item);
				}
			}

			static void SerializeTo(CJsonObject &json, const std::string &name, std::vector<unsigned __int32> & value)
			{
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}

			static void SerializeTo(CJsonObject &json, const std::string &name, std::vector<unsigned __int64> & value)
			{
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}

			static void SerializeTo(CJsonObject &json, const std::string &name, std::vector<bool> & value)
			{
				json.AddEmptySubArray(name);
				for (auto item : value)
				{
					json[name].Add(item);
				}
			}

			static void SerializeTo(CJsonObject &json, const std::string &name, std::vector<float> & value)
			{
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}

			static void SerializeTo(CJsonObject &json, const std::string &name, std::vector<double> & value)
			{
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}

			static void SerializeTo(CJsonObject &json, const std::string &name, std::vector<std::string> & value)
			{
				json.AddEmptySubArray(name);
				for (auto item : value)
				{
					json[name].Add(item);
				}
			}

			//list type
			static void SerializeTo(CJsonObject &json, const std::string &name, std::list<__int8> & value)
			{
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}

			static void SerializeTo(CJsonObject &json, const std::string &name, std::list<__int16> & value)
			{
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}

			static void SerializeTo(CJsonObject &json, const std::string &name, std::list<__int32> & value)
			{
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}

			static void SerializeTo(CJsonObject &json, const std::string &name, std::list<__int64> & value)
			{
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}

			static void SerializeTo(CJsonObject &json, const std::string &name, std::list<unsigned __int8> & value)
			{
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add((unsigned __int32)item);
				}
			}

			static void SerializeTo(CJsonObject &json, const std::string &name, std::list<unsigned __int16> & value)
			{
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add((unsigned __int32)item);
				}
			}

			static void SerializeTo(CJsonObject &json, const std::string &name, std::list<unsigned __int32> & value)
			{
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}

			static void SerializeTo(CJsonObject &json, const std::string &name, std::list<unsigned __int64> & value)
			{
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}

			static void SerializeTo(CJsonObject &json, const std::string &name, std::list<bool> & value)
			{
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}

			static void SerializeTo(CJsonObject &json, const std::string &name, std::list<float> & value)
			{
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}

			static void SerializeTo(CJsonObject &json, const std::string &name, std::list<double> & value)
			{
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}

			static void SerializeTo(CJsonObject &json, const std::string &name, std::list<std::string> & value)
			{
				json.AddEmptySubArray(name);
				for (auto item : value)
				{
					json[name].Add(item);
				}
			}

			//set type
			static void SerializeTo(CJsonObject &json, const std::string &name, std::set<__int8> & value)
			{
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}

			static void SerializeTo(CJsonObject &json, const std::string &name, std::set<__int16> & value)
			{
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}

			static void SerializeTo(CJsonObject &json, const std::string &name, std::set<__int32> & value)
			{
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}

			static void SerializeTo(CJsonObject &json, const std::string &name, std::set<__int64> & value)
			{
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}

			static void SerializeTo(CJsonObject &json, const std::string &name, std::set<unsigned __int8> & value)
			{
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add((unsigned __int32)item);
				}
			}

			static void SerializeTo(CJsonObject &json, const std::string &name, std::set<unsigned __int16> & value)
			{
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add((unsigned __int32)item);
				}
			}

			static void SerializeTo(CJsonObject &json, const std::string &name, std::set<unsigned __int32> & value)
			{
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}

			static void SerializeTo(CJsonObject &json, const std::string &name, std::set<unsigned __int64> & value)
			{
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}

			static void SerializeTo(CJsonObject &json, const std::string &name, std::set<bool> & value)
			{
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}

			static void SerializeTo(CJsonObject &json, const std::string &name, std::set<float> & value)
			{
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}

			static void SerializeTo(CJsonObject &json, const std::string &name, std::set<double> & value)
			{
				json.AddEmptySubArray(name);
				for (auto &item : value)
				{
					json[name].Add(item);
				}
			}

			static void SerializeTo(CJsonObject &json, const std::string &name, std::set<std::string> & value)
			{
				json.AddEmptySubArray(name);
				for (auto item : value)
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
						obj.SerializeFrom(json_obj);
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
						obj.SerializeFrom(json_obj);
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
						obj.SerializeFrom(json_obj);
						value.insert(obj);
					}
				}
			}

		};

		template <class T, class B = JsonSerialize, class = typename std::enable_if<std::is_base_of<B, T>::value>::type>
		struct adl_serializer
		{
			template <typename BasicJsonType>
			static void to_json(BasicJsonType& json, const T& value)
			{
				ForEachField(value, [&json](auto&& field, auto&& name) 
				{ 
					JsonSerialize::SerializeFrom(json, name, field);
				});
			}

			template <typename BasicJsonType>
			static void from_json(const BasicJsonType& json, T& value) {
				ForEachField(value, [&json](auto&& field, auto&& name) 
				{
					JsonSerialize::SerializeTo(json, name, field);
				});
			}
		};

		

		struct SYSTEM_API SimpleStruct : public JsonSerialize 
		{
			bool bool_;
			int int_;
			double double_;
			std::string string_;
			virtual void SerializeTo(CJsonObject &json)
			{

			}

			virtual void SerializeFrom(CJsonObject &json)
			{

			}
		};

		DEFINE_STRUCT_SCHEMA(SimpleStruct,
			DEFINE_STRUCT_FIELD(bool_),
			DEFINE_STRUCT_FIELD(int_),
			DEFINE_STRUCT_FIELD(double_),
			DEFINE_STRUCT_FIELD(string_)
		);
	}
}
#endif // !SYSTEM_SERIALIZERS_JSONSERIALIZE_H
