///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Data/SqlDataReader.h"
#include "System/Exceptions/SqlException.h"
#include "System/Exceptions/NotSupportedException.h"
#include <ATLComTime.h>
using namespace System::Exceptions;
namespace System
{
	namespace Data
	{
		SqlDataReader::SqlDataReader()
		{
		}

		SqlDataReader::SqlDataReader(const _RecordsetPtr & record)
		{
			m_record = record;
		}

		SqlDataReader::~SqlDataReader()
		{
			Close();
		}

		bool SqlDataReader::HasRows()
		{
			assert(m_record);
			return !m_record->GetadoEOF();
		}

		int SqlDataReader::FieldCount()
		{
			assert(m_record);
			FieldsPtr fields = m_record->GetFields();
			if (!fields) return 0;
			return fields->GetCount();
		}

		bool SqlDataReader::IsClosed()
		{
			assert(m_record);
			return m_record->GetState() == ObjectStateEnum::adStateClosed;
		}

		int SqlDataReader::RecordsAffected()
		{
			assert(m_record);
			return m_record->GetRecordCount();
		}

		void SqlDataReader::Close()
		{
			try
			{
				if (m_record != nullptr)
				{
					if (!IsClosed())
					{
						m_record->Close();
						m_record = nullptr;
					}
				}
			}
			catch (_com_error &e)
			{
				throw SqlException(e);
			}
		}

		bool SqlDataReader::Read()
		{
			try
			{
				assert(m_record);
				if (m_first)
				{
					HRESULT hr = m_record->MoveFirst();
					assert(!FAILED(hr));
					m_first = false;
				}
				else
				{
					HRESULT hr = m_record->MoveNext();
					assert(!FAILED(hr));
				}
				return HasRows();
			}
			catch (_com_error &e)
			{
				throw SqlException(e);
			}
			return false;
		}

		bool SqlDataReader::NextResult()
		{
			try
			{
				_variant_t rows;
				auto record = m_record->NextRecordset(&rows);
				if (!record) return false;
				Close();
				m_record = record;
				m_first = true;
				return true;
			}
			catch (_com_error &e)
			{
				throw SqlException(e);
			}
			return false;
		}

		bool SqlDataReader::GetBool(const _variant_t &ordinal)
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
					ordinal.vt == VARENUM::VT_UI8
				);
				if (ordinal.vt == VARENUM::VT_I1 ||
					ordinal.vt == VARENUM::VT_I2 ||
					ordinal.vt == VARENUM::VT_INT ||
					ordinal.vt == VARENUM::VT_I4 ||
					ordinal.vt == VARENUM::VT_I8 ||
					ordinal.vt == VARENUM::VT_UI1 ||
					ordinal.vt == VARENUM::VT_UI2 ||
					ordinal.vt == VARENUM::VT_UI4 ||
					ordinal.vt == VARENUM::VT_UI8
					)
				{
					assert((long)ordinal >= 0);
					auto var = m_record->GetCollect((long)ordinal);
					assert(var.vt == VARENUM::VT_BOOL);
					return var.boolVal;
				}
				else
				{
					auto var = m_record->GetCollect(ordinal);
					assert(var.vt == VARENUM::VT_BOOL);
					return var.boolVal;
				}
			}
			catch (_com_error &e)
			{
				throw SqlException(e);
			}
			return bool();
		}

		DECIMAL SqlDataReader::GetDecimal(const _variant_t & ordinal)
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
					assert((long)ordinal >= 0);
					auto var = m_record->GetCollect((long)ordinal);
					assert(var.vt == VARENUM::VT_DECIMAL);
					return var;
				}
				else
				{
					auto var = m_record->GetCollect(ordinal);
					assert(var.vt == VARENUM::VT_DECIMAL);
					return var;
				}
			}
			catch (_com_error &e)
			{
				throw SqlException(e);
			}
			return DECIMAL();
		}

		byte SqlDataReader::GetByte(const _variant_t &ordinal)
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
					assert((long)ordinal >= 0);
					auto var = m_record->GetCollect((long)ordinal);
					assert(var.vt == VARENUM::VT_UI1);
					return var.bVal;
				}
				else
				{
					auto var = m_record->GetCollect(ordinal);
					assert(var.vt == VARENUM::VT_UI1);
					return var.bVal;
				}
			}
			catch (_com_error &e)
			{
				throw SqlException(e);
			}
			return byte();
		}

		double SqlDataReader::GetDouble(const _variant_t &ordinal)
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
					assert((long)ordinal >= 0);
					auto var = m_record->GetCollect((long)ordinal);
					assert(var.vt == VARENUM::VT_R8);
					return var.dblVal;
				}
				else
				{
					auto var = m_record->GetCollect(ordinal);
					assert(var.vt == VARENUM::VT_R8);
					return var.dblVal;
				}
			}
			catch (_com_error &e)
			{
				throw SqlException(e);
			}
			return double();
		}

		float SqlDataReader::GetFloat(const _variant_t &ordinal)
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
					assert((long)ordinal >= 0);
					auto var = m_record->GetCollect((long)ordinal);
					assert(var.vt == VARENUM::VT_R4);
					return var.fltVal;
				}
				else
				{
					auto var = m_record->GetCollect(ordinal);
					assert(var.vt == VARENUM::VT_R4);
					return var.fltVal;
				}
			}
			catch (_com_error &e)
			{
				throw SqlException(e);
			}
			return float();
		}

		__int8 SqlDataReader::GetInt8(const _variant_t &ordinal)
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
					assert((long)ordinal >= 0);
					auto var = m_record->GetCollect((long)ordinal);
					assert(var.vt == VARENUM::VT_I2 || var.vt == VARENUM::VT_I1);
					return var.cVal;
				}
				else
				{
					auto var = m_record->GetCollect(ordinal);
					assert(var.vt == VARENUM::VT_I2 || var.vt == VARENUM::VT_I1);
					return var.cVal;
				}
			}
			catch (_com_error &e)
			{
				throw SqlException(e);
			}
			return char();
		}

		__int16 SqlDataReader::GetInt16(const _variant_t &ordinal)
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
					assert((long)ordinal >= 0);
					auto var = m_record->GetCollect((long)ordinal);
					assert(var.vt == VARENUM::VT_I2);
					return var.iVal;
				}
				else
				{
					auto var = m_record->GetCollect(ordinal);
					assert(var.vt == VARENUM::VT_I2);
					return var.iVal;
				}
			}
			catch (_com_error &e)
			{
				throw SqlException(e);
			}
			return short();
		}

		__int32 SqlDataReader::GetInt32(const _variant_t &ordinal)
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
					assert((long)ordinal >= 0);
					auto var = m_record->GetCollect((long)ordinal);
					assert(var.vt == VARENUM::VT_I4 || var.vt == VARENUM::VT_INT);
					return var.intVal;
				}
				else
				{
					auto var = m_record->GetCollect(ordinal);
					assert(var.vt == VARENUM::VT_I4 || var.vt == VARENUM::VT_INT);
					return var.intVal;
				}
			}
			catch (_com_error &e)
			{
				throw SqlException(e);
			}
			return int();
		}

		__int64 SqlDataReader::GetInt64(const _variant_t &ordinal)
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
					assert((long)ordinal >= 0);
					auto var = m_record->GetCollect((long)ordinal);
					assert(var.vt == VARENUM::VT_DECIMAL);
					return var.decVal.Lo64;
				}
				else
				{
					auto var = m_record->GetCollect(ordinal);
					assert(var.vt == VARENUM::VT_DECIMAL);
					return var.decVal.Lo64;
				}
			}
			catch (_com_error &e)
			{
				throw SqlException(e);
			}
			return int64_t();
		}

		unsigned __int8 SqlDataReader::GetUInt8(const _variant_t &ordinal)
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
					assert((long)ordinal >= 0);
					auto var = m_record->GetCollect((long)ordinal);
					assert(var.vt == VARENUM::VT_UI2);
					return var.cVal;
				}
				else
				{
					auto var = m_record->GetCollect(ordinal);
					assert(var.vt == VARENUM::VT_UI2);
					return var.cVal;
				}
			}
			catch (_com_error &e)
			{
				throw SqlException(e);
			}
			return unsigned char();
		}

		unsigned __int16 SqlDataReader::GetUInt16(const _variant_t &ordinal)
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
					assert((long)ordinal >= 0);
					auto var = m_record->GetCollect((long)ordinal);
					assert(var.vt == VARENUM::VT_UI2);
					return var.uiVal;
				}
				else
				{
					auto var = m_record->GetCollect(ordinal);
					assert(var.vt == VARENUM::VT_UI2);
					return var.uiVal;
				}
			}
			catch (_com_error &e)
			{
				throw SqlException(e);
			}
			return unsigned short();
		}

		unsigned __int32 SqlDataReader::GetUInt32(const _variant_t &ordinal)
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
					assert((long)ordinal >= 0);
					auto var = m_record->GetCollect((long)ordinal);
					assert(var.vt == VARENUM::VT_UI4 || var.vt == VARENUM::VT_UINT);
					return var.uintVal;
				}
				else
				{
					auto var = m_record->GetCollect(ordinal);
					assert(var.vt == VARENUM::VT_UI4 || var.vt == VARENUM::VT_UINT);
					return var.uintVal;
				}
			}
			catch (_com_error &e)
			{
				throw SqlException(e);
			}
			return unsigned int();
		}

		unsigned __int64 SqlDataReader::GetUInt64(const _variant_t &ordinal)
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
					assert((long)ordinal >= 0);
					auto var = m_record->GetCollect((long)ordinal);
					assert(var.vt == VARENUM::VT_UI8);
					return var.ullVal;
				}
				else
				{
					auto var = m_record->GetCollect(ordinal);
					assert(var.vt == VARENUM::VT_UI8);
					return var.ullVal;
				}
			}
			catch (_com_error &e)
			{
				throw SqlException(e);
			}
			return uint64_t();
		}

		std::string SqlDataReader::GetString(const _variant_t &ordinal)
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
					assert((long)ordinal >= 0);
					auto var = m_record->GetCollect((long)ordinal);
					assert(var.vt == VARENUM::VT_BSTR);
					return (const char*)_bstr_t(var);
				}
				else
				{
					auto var = m_record->GetCollect(ordinal);
					assert(var.vt == VARENUM::VT_BSTR);
					return (const char*)_bstr_t(var);
				}
			}
			catch (_com_error &e)
			{
				throw SqlException(e);
			}
			return std::string();
		}

		COleDateTime SqlDataReader::GetDateTime(const _variant_t &ordinal)
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
					assert((long)ordinal >= 0);
					auto var = m_record->GetCollect((long)ordinal);
					assert(var.vt == VARENUM::VT_DATE);
					return COleDateTime(var.date);
				}
				else
				{
					auto var = m_record->GetCollect(ordinal);
					assert(var.vt == VARENUM::VT_DATE);
					return COleDateTime(var.date);
				}
			}
			catch (_com_error &e)
			{
				throw SqlException(e);
			}
			return COleDateTime();
		}

		bool SqlDataReader::IsDBNull(const _variant_t &ordinal)
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
					assert((long)ordinal >= 0);
					auto var = m_record->GetCollect((long)ordinal);
					return (var.vt == VARENUM::VT_NULL);
				}
				else
				{
					auto var = m_record->GetCollect(ordinal);
					return (var.vt == VARENUM::VT_NULL);
				}
			}
			catch (_com_error &e)
			{
				throw SqlException(e);
			}
			return false;
		}
	}
}