///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_DATA_DATAREADER_H
#define SYSTEM_DATA_DATAREADER_H
#include "System/Data/ADO.h"
#include "System/Base/DllExport.h"
#include <string>
namespace System
{
	namespace Data
	{
		class value
		{
		public:
			value() throw()
			{

			}
			value(const value& v)
			{

			}
			value(float v) throw()
			{

			}
			value(double v)
			{
				double_v = v;
			}
			value(bool v) throw()
			{
				bool_v = v;
			}
			value(char v) throw()
			{
				char_v = v;
			}
			value(short v)
			{
				short_v = v;
			}
			value(int v) throw()
			{
				int_v = v;
			}
			value(__int64 v) throw()
			{
				int64_v = v;
			}
			value(unsigned char v) throw()
			{
				uchar_v = v;
			}
			value(unsigned short v) throw()
			{
				ushort_v = v;
			}
			value(unsigned int v) throw()
			{
				uint_v = v;
			}
			value(unsigned __int64 v) throw()
			{
				uint64_v = v;
			}
			value(const _bstr_t& v)
			{
				bstr_v = v;
			}
			value(const wchar_t *v)
			{
				wchar_bin_v = v;
			}
			value(const char* v)
			{
				char_bin_v = v;
			}
			~value() throw()
			{

			}

			operator float() const
			{
				return float_v;
			}
			operator double() const
			{
				return double_v;
			}
			operator bool() const
			{
				return bool_v;
			}
			operator char() const
			{
				return char_v;
			}
			operator short() const
			{
				return short_v;
			}
			operator int() const
			{
				return int_v;
			}
			operator __int64() const
			{
				return int64_v;
			}
			operator unsigned char() const
			{
				return uchar_v;
			}
			operator unsigned short() const
			{
				return ushort_v;
			}
			operator unsigned int() const
			{
				return uint_v;
			}
			operator unsigned __int64() const
			{
				return uint64_v;
			}
			operator _bstr_t() const
			{
				return bstr_v;
			}
			operator const wchar_t*() const
			{
				return wchar_bin_v;
			}
			operator const char*() const
			{
				return char_bin_v;
			}

			value& operator=(float v)
			{
				float_v = v;
			}
			value& operator=(double v)
			{
				double_v = v;
			}
			value& operator=(bool v)
			{
				bool_v = v;
			}
			value& operator=(char v)
			{
				char_v = v;
			}
			value& operator=(short v)
			{
				short_v = v;
			}
			value& operator=(int v)
			{
				int_v = v;
			}
			value& operator=(__int64 v)
			{
				int64_v = v;
			}
			value& operator=(unsigned char v)
			{
				uchar_v = v;
			}
			value& operator=(unsigned short v)
			{
				ushort_v = v;
			}
			value& operator=(unsigned int v)
			{
				uint_v = v;
			}
			value& operator=(unsigned __int64 v)
			{
				int64_v = v;
			}
			value& operator=(const _bstr_t& v)
			{
				bstr_v = v;
			}
			value& operator=(const wchar_t* v)
			{
				wchar_bin_v = v;
			}
			value& operator=(const char* v)
			{
				char_bin_v = v;
			}
			union
			{
				float float_v;
				double double_v;
				bool bool_v;
				char char_v;
				short short_v;
				int int_v;
				__int64 int64_v;
				unsigned char uchar_v;
				unsigned short ushort_v;
				unsigned int uint_v;
				unsigned __int64 uint64_v;
				_bstr_t bstr_v;
				const wchar_t* wchar_bin_v;
				const char* char_bin_v;
			};
		};
		class SYSTEM_API DbDataReader
		{
		public:
			virtual bool HasRows() = 0;
			virtual int FieldCount() = 0;
			virtual bool IsClosed() = 0;
			virtual int RecordsAffected() = 0;
			virtual void Close() = 0;
			virtual bool Read() = 0;
			virtual bool NextResult() = 0;

			virtual bool GetBool(const _variant_t &ordinal) = 0;
			virtual byte GetByte(const _variant_t &ordinal) = 0;
			virtual DECIMAL GetDecimal(const _variant_t &ordinal) = 0;
			virtual double GetDouble(const _variant_t &ordinal) = 0;
			virtual float GetFloat(const _variant_t &ordinal) = 0;
			virtual __int8 GetInt8(const _variant_t &ordinal) = 0;
			virtual __int16 GetInt16(const _variant_t &ordinal) = 0;
			virtual __int32 GetInt32(const _variant_t &ordinal) = 0;
			virtual __int64 GetInt64(const _variant_t &ordinal) = 0;
			virtual unsigned __int8 GetUInt8(const _variant_t &ordinal) = 0;
			virtual unsigned __int16 GetUInt16(const _variant_t &ordinal) = 0;
			virtual unsigned __int32 GetUInt32(const _variant_t &ordinal) = 0;
			virtual unsigned __int64 GetUInt64(const _variant_t &ordinal) = 0;
			virtual std::string GetString(const _variant_t &ordinal) = 0;
			virtual COleDateTime GetDateTime(const _variant_t &ordinal) = 0;
			virtual bool IsDBNull(const _variant_t &ordinal) = 0;
		};
	}
}
#endif // !SYSTEM_DATA_DATAREADER_H
