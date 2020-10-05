///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_DATA_SQLDATAREADER_H
#define SYSTEM_DATA_SQLDATAREADER_H
#include "System/Data/DbDataReader.h"
namespace System
{
	namespace Data
	{
		class SYSTEM_API SqlDataReader : public DbDataReader
		{
		public:
			SqlDataReader();
			SqlDataReader(const _RecordsetPtr &record);
			virtual ~SqlDataReader();
			virtual bool HasRows() override;
			virtual int FieldCount() override;
			virtual bool IsClosed() override;
			virtual int RecordsAffected() override;
			virtual void Close() override;
			virtual bool Read() override;
			virtual bool NextResult() override;

			virtual bool GetBool(int ordinal) override;
			virtual char GetChar(int ordinal) override;
			virtual double GetDouble(int ordinal) override;
			virtual float GetFloat(int ordinal) override;
			virtual short GetInt16(int ordinal) override;
			virtual int GetInt(int ordinal) override;
			virtual int64_t GetInt64(int ordinal) override;
			virtual unsigned short GetUInt16(int ordinal) override;
			virtual unsigned int GetUInt(int ordinal) override;
			virtual uint64_t GetUInt64(int ordinal) override;
			virtual std::string GetString(int ordinal) override;
			virtual bool IsDBNull(int ordinal) override;

			virtual bool GetBool(const std::string & ordinal) override;
			virtual char GetChar(const std::string & ordinal) override;
			virtual double GetDouble(const std::string & ordinal) override;
			virtual float GetFloat(const std::string & ordinal) override;
			virtual short GetInt16(const std::string & ordinal) override;
			virtual int GetInt(const std::string & ordinal) override;
			virtual int64_t GetInt64(const std::string & ordinal) override;
			virtual unsigned short GetUInt16(const std::string & ordinal) override;
			virtual unsigned int GetUInt(const std::string & ordinal) override;
			virtual uint64_t GetUInt64(const std::string & ordinal) override;
			virtual std::string GetString(const std::string & ordinal) override;
			virtual bool IsDBNull(const std::string & ordinal) override;
		private:
			_RecordsetPtr m_record;
		};
	}
}
#endif // !SYSTEM_DATA_SQLDATAREADER_H
