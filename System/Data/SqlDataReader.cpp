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
			if (m_record == nullptr)
			{
				throw NullReferenceException("m_record is nullptr");
			}
			return !m_record->GetadoEOF();
		}

		int SqlDataReader::FieldCount()
		{
			if (m_record == nullptr)
			{
				throw NullReferenceException("m_record is nullptr");
			}
			FieldsPtr fields = m_record->GetFields();
			if (!fields) return 0;
			return fields->GetCount();
		}

		bool SqlDataReader::IsClosed()
		{
			if (m_record == nullptr)
			{
				throw NullReferenceException("m_record is nullptr");
			}
			return m_record->GetState() == ObjectStateEnum::adStateClosed;
		}

		int SqlDataReader::RecordsAffected()
		{
			if (m_record == nullptr)
			{
				throw NullReferenceException("m_record is nullptr");
			}
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
				if (m_record == nullptr)
				{
					throw NullReferenceException("m_record is nullptr");
				}
				HRESULT hr;
				if (m_first)
				{
					hr = m_record->MoveFirst();
					m_first = false;
				}
				else
				{
					hr = m_record->MoveNext();
				}
				if (FAILED(hr)) return false;
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
				if (m_record == nullptr)
				{
					throw NullReferenceException("m_record is nullptr");
				}
				if (IsDigital(ordinal.vt))
				{
					if ((long)ordinal < 0)
					{
						throw IndexOutOfRangeException("index is " + (long)ordinal);
					}
					auto var = m_record->GetCollect((long)ordinal);
					assert(var.vt == VARENUM::VT_BOOL);
					return var.boolVal;
				}
				else if (ordinal.vt == VARENUM::VT_BSTR)
				{
					auto var = m_record->GetCollect(ordinal);
					assert(var.vt == VARENUM::VT_BOOL);
					return var.boolVal;
				}
				else
				{
					throw NotSupportedException("not support type");
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
				if (m_record == nullptr)
				{
					throw NullReferenceException("m_record is nullptr");
				}
				if (IsDigital(ordinal.vt))
				{
					if ((long)ordinal < 0)
					{
						throw IndexOutOfRangeException("index is " + (long)ordinal);
					}
					auto var = m_record->GetCollect((long)ordinal);
					assert(var.vt == VARENUM::VT_DECIMAL);
					return var;
				}
				else if (ordinal.vt == VARENUM::VT_BSTR)
				{
					auto var = m_record->GetCollect(ordinal);
					assert(var.vt == VARENUM::VT_DECIMAL);
					return var;
				}
				else
				{
					throw NotSupportedException("not support type");
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
				if (m_record == nullptr)
				{
					throw NullReferenceException("m_record is nullptr");
				}
				if (IsDigital(ordinal.vt))
				{
					if ((long)ordinal < 0)
					{
						throw IndexOutOfRangeException("index is " + (long)ordinal);
					}
					auto var = m_record->GetCollect((long)ordinal);
					if (var.vt == VARENUM::VT_NULL)
					{
						return byte();
					}
					assert(var.vt == VARENUM::VT_UI1);
					return var.bVal;
				}
				else if (ordinal.vt == VARENUM::VT_BSTR)
				{
					auto var = m_record->GetCollect(ordinal);
					if (var.vt == VARENUM::VT_NULL)
					{
						return byte();
					}
					assert(var.vt == VARENUM::VT_UI1);
					return var.bVal;
				}
				else
				{
					throw NotSupportedException("not support type");
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
				if (m_record == nullptr)
				{
					throw NullReferenceException("m_record is nullptr");
				}
				if (IsDigital(ordinal.vt))
				{
					if ((long)ordinal < 0)
					{
						throw IndexOutOfRangeException("index is " + (long)ordinal);
					}
					auto var = m_record->GetCollect((long)ordinal);
					if (var.vt == VARENUM::VT_NULL)
					{
						return double();
					}
					assert(var.vt == VARENUM::VT_R8);
					return var.dblVal;
				}
				else if (ordinal.vt == VARENUM::VT_BSTR)
				{
					auto var = m_record->GetCollect(ordinal);
					if (var.vt == VARENUM::VT_NULL)
					{
						return double();
					}
					assert(var.vt == VARENUM::VT_R8);
					return var.dblVal;
				}
				else
				{
					throw NotSupportedException("not support type");
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
				if (m_record == nullptr)
				{
					throw NullReferenceException("m_record is nullptr");
				}
				if (IsDigital(ordinal.vt))
				{
					if ((long)ordinal < 0)
					{
						throw IndexOutOfRangeException("index is " + (long)ordinal);
					}
					auto var = m_record->GetCollect((long)ordinal);
					if (var.vt == VARENUM::VT_NULL)
					{
						return float();
					}
					assert(var.vt == VARENUM::VT_R4);
					return var.fltVal;
				}
				else if (ordinal.vt == VARENUM::VT_BSTR)
				{
					auto var = m_record->GetCollect(ordinal);
					if (var.vt == VARENUM::VT_NULL)
					{
						return float();
					}
					assert(var.vt == VARENUM::VT_R4);
					return var.fltVal;
				}
				else
				{
					throw NotSupportedException("not support type");
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
				if (m_record == nullptr)
				{
					throw NullReferenceException("m_record is nullptr");
				}
				if (IsDigital(ordinal.vt))
				{
					if ((long)ordinal < 0)
					{
						throw IndexOutOfRangeException("index is " + (long)ordinal);
					}
					auto var = m_record->GetCollect((long)ordinal);
					if (var.vt == VARENUM::VT_NULL)
					{
						return __int8();
					}
					assert(var.vt == VARENUM::VT_I2 || var.vt == VARENUM::VT_I1);
					return var.cVal;
				}
				else if (ordinal.vt == VARENUM::VT_BSTR)
				{
					auto var = m_record->GetCollect(ordinal);
					if (var.vt == VARENUM::VT_NULL)
					{
						return __int8();
					}
					assert(var.vt == VARENUM::VT_I2 || var.vt == VARENUM::VT_I1);
					return var.cVal;
				}
				else
				{
					throw NotSupportedException("not support type");
				}
			}
			catch (_com_error &e)
			{
				throw SqlException(e);
			}
			return __int8();
		}

		__int16 SqlDataReader::GetInt16(const _variant_t &ordinal)
		{
			try
			{
				if (m_record == nullptr)
				{
					throw NullReferenceException("m_record is nullptr");
				}
				if (IsDigital(ordinal.vt))
				{
					if ((long)ordinal < 0)
					{
						throw IndexOutOfRangeException("index is " + (long)ordinal);
					}
					auto var = m_record->GetCollect((long)ordinal);
					if (var.vt == VARENUM::VT_NULL)
					{
						return __int16();
					}
					assert(var.vt == VARENUM::VT_I2);
					return var.iVal;
				}
				else if (ordinal.vt == VARENUM::VT_BSTR)
				{
					auto var = m_record->GetCollect(ordinal);
					if (var.vt == VARENUM::VT_NULL)
					{
						return __int16();
					}
					assert(var.vt == VARENUM::VT_I2);
					return var.iVal;
				}
				else
				{
					throw NotSupportedException("not support type");
				}
			}
			catch (_com_error &e)
			{
				throw SqlException(e);
			}
			return __int16();
		}

		__int32 SqlDataReader::GetInt32(const _variant_t &ordinal)
		{
			try
			{
				if (m_record == nullptr)
				{
					throw NullReferenceException("m_record is nullptr");
				}
				if (IsDigital(ordinal.vt))
				{
					if ((long)ordinal < 0)
					{
						throw IndexOutOfRangeException("index is " + (long)ordinal);
					}
					auto var = m_record->GetCollect((long)ordinal);
					if (var.vt == VARENUM::VT_NULL)
					{
						return __int32();
					}
					assert(var.vt == VARENUM::VT_I4 || var.vt == VARENUM::VT_INT);
					return var.intVal;
				}
				else if (ordinal.vt == VARENUM::VT_BSTR)
				{
					auto var = m_record->GetCollect(ordinal);
					if (var.vt == VARENUM::VT_NULL)
					{
						return __int32();
					}
					assert(var.vt == VARENUM::VT_I4 || var.vt == VARENUM::VT_INT);
					return var.intVal;
				}
				else
				{
					throw NotSupportedException("not support type");
				}
			}
			catch (_com_error &e)
			{
				throw SqlException(e);
			}
			return __int32();
		}

		__int64 SqlDataReader::GetInt64(const _variant_t &ordinal)
		{
			try
			{
				if (m_record == nullptr)
				{
					throw NullReferenceException("m_record is nullptr");
				}
				if (IsDigital(ordinal.vt))
				{
					if ((long)ordinal < 0)
					{
						throw IndexOutOfRangeException("index is " + (long)ordinal);
					}
					auto var = m_record->GetCollect((long)ordinal);
					if (var.vt == VARENUM::VT_NULL)
					{
						return __int64();
					}
					assert(var.vt == VARENUM::VT_DECIMAL);
					return var.decVal.Lo64;
				}
				else if (ordinal.vt == VARENUM::VT_BSTR)
				{
					auto var = m_record->GetCollect(ordinal);
					if (var.vt == VARENUM::VT_NULL)
					{
						return __int16();
					}
					assert(var.vt == VARENUM::VT_DECIMAL);
					return var.decVal.Lo64;
				}
				else
				{
					throw NotSupportedException("not support type");
				}
			}
			catch (_com_error &e)
			{
				throw SqlException(e);
			}
			return __int64();
		}

		unsigned __int8 SqlDataReader::GetUInt8(const _variant_t &ordinal)
		{
			try
			{
				if (m_record == nullptr)
				{
					throw NullReferenceException("m_record is nullptr");
				}
				if (IsDigital(ordinal.vt))
				{
					if ((long)ordinal < 0)
					{
						throw IndexOutOfRangeException("index is " + (long)ordinal);
					}
					auto var = m_record->GetCollect((long)ordinal);
					if (var.vt == VARENUM::VT_NULL)
					{
						return unsigned __int8();
					}
					assert(var.vt == VARENUM::VT_UI2);
					return var.cVal;
				}
				else if (ordinal.vt == VARENUM::VT_BSTR)
				{
					auto var = m_record->GetCollect(ordinal);
					if (var.vt == VARENUM::VT_NULL)
					{
						return unsigned __int8();
					}
					assert(var.vt == VARENUM::VT_UI2);
					return var.cVal;
				}
				else
				{
					throw NotSupportedException("not support type");
				}
			}
			catch (_com_error &e)
			{
				throw SqlException(e);
			}
			return unsigned __int8();
		}

		unsigned __int16 SqlDataReader::GetUInt16(const _variant_t &ordinal)
		{
			try
			{
				if (m_record == nullptr)
				{
					throw NullReferenceException("m_record is nullptr");
				}
				if (IsDigital(ordinal.vt))
				{
					if ((long)ordinal < 0)
					{
						throw IndexOutOfRangeException("index is " + (long)ordinal);
					}
					auto var = m_record->GetCollect((long)ordinal);
					if (var.vt == VARENUM::VT_NULL)
					{
						return unsigned __int16();
					}
					assert(var.vt == VARENUM::VT_UI2);
					return var.uiVal;
				}
				else if (ordinal.vt == VARENUM::VT_BSTR)
				{
					auto var = m_record->GetCollect(ordinal);
					if (var.vt == VARENUM::VT_NULL)
					{
						return unsigned __int16();
					}
					assert(var.vt == VARENUM::VT_UI2);
					return var.uiVal;
				}
				else
				{
					throw NotSupportedException("not support type");
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
				if (m_record == nullptr)
				{
					throw NullReferenceException("m_record is nullptr");
				}
				if (IsDigital(ordinal.vt))
				{
					if ((long)ordinal < 0)
					{
						throw IndexOutOfRangeException("index is " + (long)ordinal);
					}
					auto var = m_record->GetCollect((long)ordinal);
					if (var.vt == VARENUM::VT_NULL)
					{
						return unsigned __int32();
					}
					assert(var.vt == VARENUM::VT_UI4 || var.vt == VARENUM::VT_UINT);
					return var.uintVal;
				}
				else if (ordinal.vt == VARENUM::VT_BSTR)
				{
					auto var = m_record->GetCollect(ordinal);
					if (var.vt == VARENUM::VT_NULL)
					{
						return unsigned __int32();
					}
					assert(var.vt == VARENUM::VT_UI4 || var.vt == VARENUM::VT_UINT);
					return var.uintVal;
				}
				else
				{
					throw NotSupportedException("not support type");
				}
			}
			catch (_com_error &e)
			{
				throw SqlException(e);
			}
			return unsigned __int32();
		}

		unsigned __int64 SqlDataReader::GetUInt64(const _variant_t &ordinal)
		{
			try
			{
				if (m_record == nullptr)
				{
					throw NullReferenceException("m_record is nullptr");
				}
				if (IsDigital(ordinal.vt))
				{
					if ((long)ordinal < 0)
					{
						throw IndexOutOfRangeException("index is " + (long)ordinal);
					}
					auto var = m_record->GetCollect((long)ordinal);
					if (var.vt == VARENUM::VT_NULL)
					{
						return unsigned __int64();
					}
					assert(var.vt == VARENUM::VT_UI8);
					return var.ullVal;
				}
				else if (ordinal.vt == VARENUM::VT_BSTR)
				{
					auto var = m_record->GetCollect(ordinal);
					if (var.vt == VARENUM::VT_NULL)
					{
						return unsigned __int64();
					}
					assert(var.vt == VARENUM::VT_UI8);
					return var.ullVal;
				}
				else
				{
					throw NotSupportedException("not support type");
				}
			}
			catch (_com_error &e)
			{
				throw SqlException(e);
			}
			return unsigned __int64();
		}

		std::string SqlDataReader::GetString(const _variant_t &ordinal)
		{
			try
			{
				if (m_record == nullptr)
				{
					throw NullReferenceException("m_record is nullptr");
				}
				if (IsDigital(ordinal.vt))
				{
					if ((long)ordinal < 0)
					{
						throw IndexOutOfRangeException("index is " + (long)ordinal);
					}
					auto var = m_record->GetCollect((long)ordinal);
					if (var.vt == VARENUM::VT_NULL)
					{
						return std::string();
					}
					assert(var.vt == VARENUM::VT_BSTR);
					return (const char*)_bstr_t(var);
				}
				else if (ordinal.vt == VARENUM::VT_BSTR)
				{
					auto var = m_record->GetCollect(ordinal);
					if (var.vt == VARENUM::VT_NULL)
					{
						return std::string();
					}
					assert(var.vt == VARENUM::VT_BSTR);
					return (const char*)_bstr_t(var);
				}
				else
				{
					throw NotSupportedException("not support type");
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
				if (m_record == nullptr)
				{
					throw NullReferenceException("m_record is nullptr");
				}
				if (IsDigital(ordinal.vt))
				{
					if ((long)ordinal < 0)
					{
						throw IndexOutOfRangeException("index is " + (long)ordinal);
					}
					auto var = m_record->GetCollect((long)ordinal);
					if (var.vt == VARENUM::VT_NULL)
					{
						return COleDateTime();
					}
					assert(var.vt == VARENUM::VT_DATE);
					return COleDateTime(var.date);
				}
				else if (ordinal.vt == VARENUM::VT_BSTR)
				{
					auto var = m_record->GetCollect(ordinal);
					if (var.vt == VARENUM::VT_NULL)
					{
						return COleDateTime();
					}
					assert(var.vt == VARENUM::VT_DATE);
					return COleDateTime(var.date);
				}
				else
				{
					throw NotSupportedException("not support type");
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
				if (m_record == nullptr)
				{
					throw NullReferenceException("m_record is nullptr");
				}
				if (IsDigital(ordinal.vt))
				{
					if ((long)ordinal < 0)
					{
						throw IndexOutOfRangeException("index is " + (long)ordinal);
					}
					auto var = m_record->GetCollect((long)ordinal);
					return (var.vt == VARENUM::VT_NULL);
				}
				else if (ordinal.vt == VARENUM::VT_BSTR)
				{
					auto var = m_record->GetCollect(ordinal);
					return (var.vt == VARENUM::VT_NULL);
				}
				else
				{
					throw NotSupportedException("not support type");
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