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

			virtual bool GetBool(int ordinal) = 0;
			virtual char GetChar(int ordinal) = 0;
			virtual double GetDouble(int ordinal) = 0;
			virtual float GetFloat(int ordinal) = 0;
			virtual short GetInt16(int ordinal) = 0;
			virtual int GetInt(int ordinal) = 0;
			virtual int64_t GetInt64(int ordinal) = 0;
			virtual unsigned short GetUInt16(int ordinal) = 0;
			virtual unsigned int GetUInt(int ordinal) = 0;
			virtual uint64_t GetUInt64(int ordinal) = 0;
			virtual std::string GetString(int ordinal) = 0;
			virtual bool IsDBNull(int ordinal) = 0;

			virtual bool GetBool(const std::string & ordinal) = 0;
			virtual char GetChar(const std::string & ordinal) = 0;
			virtual double GetDouble(const std::string & ordinal) = 0;
			virtual float GetFloat(const std::string & ordinal) = 0;
			virtual short GetInt16(const std::string & ordinal) = 0;
			virtual int GetInt(const std::string & ordinal) = 0;
			virtual int64_t GetInt64(const std::string & ordinal) = 0;
			virtual unsigned short GetUInt16(const std::string & ordinal) = 0;
			virtual unsigned int GetUInt(const std::string & ordinal) = 0;
			virtual uint64_t GetUInt64(const std::string & ordinal) = 0;
			virtual std::string GetString(const std::string & ordinal) = 0;
			virtual bool IsDBNull(const std::string & ordinal) = 0;
		};
	}
}
#endif // !SYSTEM_DATA_DATAREADER_H
