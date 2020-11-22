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
			virtual _variant_t GetValue(const _variant_t &ordinal) = 0;
		};
	}
}
#endif // !SYSTEM_DATA_DATAREADER_H
