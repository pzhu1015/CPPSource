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

			virtual byte GetByte(const _variant_t &ordinal) override;
			virtual bool GetBool(const _variant_t &ordinal) override;
			virtual DECIMAL GetDecimal(const _variant_t &ordinal) override;
			virtual double GetDouble(const _variant_t &ordinal) override;
			virtual float GetFloat(const _variant_t &ordinal) override;
			virtual __int8 GetInt8(const _variant_t &ordinal) override;
			virtual __int16 GetInt16(const _variant_t &ordinal) override;
			virtual __int32 GetInt32(const _variant_t &ordinal) override;
			virtual __int64 GetInt64(const _variant_t &ordinal) override;
			virtual unsigned __int8 GetUInt8(const _variant_t &ordinal) override;
			virtual unsigned __int16 GetUInt16(const _variant_t &ordinal) override;
			virtual unsigned __int32 GetUInt32(const _variant_t &ordinal) override;
			virtual unsigned __int64 GetUInt64(const _variant_t &ordinal) override;
			virtual std::string GetString(const _variant_t &ordinal) override;
			virtual COleDateTime GetDateTime(const _variant_t &ordinal) override;
			virtual bool IsDBNull(const _variant_t &ordinal) override;

			template <class T>
			typename std::enable_if<
				std::is_same<T, bool>::value ||
				std::is_same<T, __int8>::value|| 
				std::is_same<T, __int16>::value || 
				std::is_same<T, __int32>::value || 
				std::is_same<T, __int64>::value || 
				std::is_same<T, unsigned __int8>::value || 
				std::is_same<T, unsigned __int16>::value || 
				std::is_same<T, unsigned __int32>::value || 
				std::is_same<T, unsigned __int64>::value || 
				std::is_same<T, float>::value || 
				std::is_same<T, double>::value || 
				std::is_same<T, DECIMAL>::value ||
				std::is_same<T, CString>::value, T>::type
			GetValue(const _variant_t &ordinal)
			{
				try
				{
					assert(m_record);
					assert(ordinal.vt == VARENUM::VT_BSTR ||
						ordinal.vt == VARENUM::VT_I1 ||
						ordinal.vt == VARENUM::VT_I2 ||
						ordinal.vt == VARENUM::VT_INT ||
						ordinal.vt == VARENUM::VT_I4 ||
						ordinal.vt == VARENUM::VT_I8 ||
						ordinal.vt == VARENUM::VT_UI1 ||
						ordinal.vt == VARENUM::VT_UI2 ||
						ordinal.vt == VARENUM::VT_UI4 ||
						ordinal.vt == VARENUM::VT_UI8);
					if (ordinal.vt == VARENUM::VT_I1 ||
						ordinal.vt == VARENUM::VT_I2 ||
						ordinal.vt == VARENUM::VT_INT ||
						ordinal.vt == VARENUM::VT_I4 ||
						ordinal.vt == VARENUM::VT_I8 ||
						ordinal.vt == VARENUM::VT_UI1 ||
						ordinal.vt == VARENUM::VT_UI2 ||
						ordinal.vt == VARENUM::VT_UI4 ||
						ordinal.vt == VARENUM::VT_UI8)
					{
						auto var = m_record->GetCollect((long)ordinal);
						return var;
					}
					else
					{
						auto var = m_record->GetCollect(ordinal);
						return var;
					}
				}
				catch (_com_error &e)
				{
					throw SqlException(e);
				}
				return T();
			}

			template <class T>
			typename std::enable_if<
				std::is_same<T, COleDateTime>::value, T>::type
				GetValue(const _variant_t &ordinal)
			{
				try
				{
					assert(m_record);
					assert(ordinal.vt == VARENUM::VT_BSTR ||
						ordinal.vt == VARENUM::VT_I1 ||
						ordinal.vt == VARENUM::VT_I2 ||
						ordinal.vt == VARENUM::VT_INT ||
						ordinal.vt == VARENUM::VT_I4 ||
						ordinal.vt == VARENUM::VT_I8 ||
						ordinal.vt == VARENUM::VT_UI1 ||
						ordinal.vt == VARENUM::VT_UI2 ||
						ordinal.vt == VARENUM::VT_UI4 ||
						ordinal.vt == VARENUM::VT_UI8);
					if (ordinal.vt == VARENUM::VT_I1 ||
						ordinal.vt == VARENUM::VT_I2 ||
						ordinal.vt == VARENUM::VT_INT ||
						ordinal.vt == VARENUM::VT_I4 ||
						ordinal.vt == VARENUM::VT_I8 ||
						ordinal.vt == VARENUM::VT_UI1 ||
						ordinal.vt == VARENUM::VT_UI2 ||
						ordinal.vt == VARENUM::VT_UI4 ||
						ordinal.vt == VARENUM::VT_UI8)
					{
						auto var = m_record->GetCollect((long)ordinal);
						return T(var.date);
					}
					else
					{
						auto var = m_record->GetCollect(ordinal);
						return T(var.date);
					}
				}
				catch (_com_error &e)
				{
					throw SqlException(e);
				}
				return T();
			}

			template <class T>
			typename std::enable_if<
				std::is_same<T, std::string>::value, T>::type
				GetValue(const _variant_t &ordinal)
			{
				try
				{
					assert(m_record);
					assert(ordinal.vt == VARENUM::VT_BSTR ||
						ordinal.vt == VARENUM::VT_I1 ||
						ordinal.vt == VARENUM::VT_I2 ||
						ordinal.vt == VARENUM::VT_INT ||
						ordinal.vt == VARENUM::VT_I4 ||
						ordinal.vt == VARENUM::VT_I8 ||
						ordinal.vt == VARENUM::VT_UI1 ||
						ordinal.vt == VARENUM::VT_UI2 ||
						ordinal.vt == VARENUM::VT_UI4 ||
						ordinal.vt == VARENUM::VT_UI8);
					if (ordinal.vt == VARENUM::VT_I1 ||
						ordinal.vt == VARENUM::VT_I2 ||
						ordinal.vt == VARENUM::VT_INT ||
						ordinal.vt == VARENUM::VT_I4 ||
						ordinal.vt == VARENUM::VT_I8 ||
						ordinal.vt == VARENUM::VT_UI1 ||
						ordinal.vt == VARENUM::VT_UI2 ||
						ordinal.vt == VARENUM::VT_UI4 ||
						ordinal.vt == VARENUM::VT_UI8)
					{
						auto var = m_record->GetCollect((long)ordinal);
						return (const char*)_bstr_t(var);
					}
					else
					{
						auto var = m_record->GetCollect(ordinal);
						return (const char*)_bstr_t(var);
					}
				}
				catch (_com_error &e)
				{
					throw SqlException(e);
				}
				return T();
			}

			/*
			TODO: decimal
			_variant_t vt;
			vt =r->GetCollect("rowid");
			dbRowID = vt.decVal.Lo32;
			dbRowID *= (vt.decVal.sign == 128)? -1 : 1;
			dbRowID /= pow(10.00, vt.decVal.scale);
			*/
		private:
			_RecordsetPtr m_record;
		};
	}
}
#endif // !SYSTEM_DATA_SQLDATAREADER_H
