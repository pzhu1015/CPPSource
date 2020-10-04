///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Data/MySqlDataReader.h"
namespace System
{
	/*
	Byte bVal;							// VT_UI1.
	Short iVal;							// VT_I2.
	long lVal;							// VT_I4.
	float fltVal;						// VT_R4.
	double dblVal;						// VT_R8.
	VARIANT_BOOL boolVal;				// VT_BOOL.
	SCODE scode;						// VT_ERROR.
	CY cyVal;							// VT_CY.
	DATE date;							// VT_DATE.
	BSTR bstrVal;						// VT_BSTR.
	DECIMAL FAR* pdecVal				// VT_BYREF|VT_DECIMAL.
	IUnknown FAR* punkVal;				// VT_UNKNOWN.
	IDispatch FAR* pdispVal;			// VT_DISPATCH.
	SAFEARRAY FAR* parray;				// VT_ARRAY|*.
	Byte FAR* pbVal;					// VT_BYREF|VT_UI1.
	short FAR* piVal;					// VT_BYREF|VT_I2.
	long FAR* plVal;					// VT_BYREF|VT_I4.
	float FAR* pfltVal;					// VT_BYREF|VT_R4.
	double FAR* pdblVal;				// VT_BYREF|VT_R8.
	VARIANT_BOOL FAR* pboolVal;			// VT_BYREF|VT_BOOL.
	SCODE FAR* pscode;					// VT_BYREF|VT_ERROR.
	CY FAR* pcyVal;						// VT_BYREF|VT_CY.
	DATE FAR* pdate;					// VT_BYREF|VT_DATE.
	BSTR FAR* pbstrVal;					// VT_BYREF|VT_BSTR.
	IUnknown FAR* FAR* ppunkVal;		// VT_BYREF|VT_UNKNOWN.
	IDispatch FAR* FAR* ppdispVal;		// VT_BYREF|VT_DISPATCH.
	SAFEARRAY FAR* FAR* pparray;		// VT_ARRAY|*.
	VARIANT FAR* pvarVal;				// VT_BYREF|VT_VARIANT.
	void FAR* byref;					// Generic ByRef.
	char cVal;							// VT_I1.
	unsigned short uiVal;				// VT_UI2.
	unsigned long ulVal;				// VT_UI4.
	int intVal;							// VT_INT.
	unsigned int uintVal;				// VT_UINT.
	char FAR * pcVal;					// VT_BYREF|VT_I1.
	unsigned short FAR * puiVal;		// VT_BYREF|VT_UI2.
	unsigned long FAR * pulVal;			// VT_BYREF|VT_UI4.
	int FAR * pintVal;					// VT_BYREF|VT_INT.
	unsigned int FAR * puintVal;		//VT_BYREF|VT_UINT.
	*/
	namespace Data
	{
		MySqlDataReader::MySqlDataReader()
		{
		}
		MySqlDataReader::MySqlDataReader(const _RecordsetPtr & record)
		{
			m_record = record;
		}
		MySqlDataReader::~MySqlDataReader()
		{
			Close();
		}
		bool MySqlDataReader::HasRows()
		{
			assert(m_record);
			return m_record->GetadoEOF();
		}
		int MySqlDataReader::FieldCount()
		{
			assert(m_record);
			FieldsPtr fields = m_record->GetFields();
			if (!fields) return 0;
			return fields->GetCount();
		}

		bool MySqlDataReader::IsClosed()
		{
			assert(m_record);
			return m_record->GetState() == ObjectStateEnum::adStateClosed;
		}

		int MySqlDataReader::RecordsAffected()
		{
			assert(m_record);
			return -1;
		}

		void MySqlDataReader::Close()
		{
			assert(m_record);
			m_record->Close();
			m_record = nullptr;
		}

		bool MySqlDataReader::Read()
		{
			assert(m_record);
			return !m_record->GetadoEOF();
		}

		bool MySqlDataReader::NextResult()
		{
			assert(m_record);
			HRESULT hr = m_record->MoveNext();
			return !FAILED(hr);
		}

		bool MySqlDataReader::GetBool(int ordinal)
		{
			assert(m_record);
			auto var = m_record->GetCollect((long)ordinal);
			assert(var.vt == VARENUM::VT_BOOL);
			return var.boolVal;
		}

		char MySqlDataReader::GetChar(int ordinal)
		{
			assert(m_record);
			auto var = m_record->GetCollect((long)ordinal);
			assert(var.vt == VARENUM::VT_I1);
			return var.cVal;
		}

		double MySqlDataReader::GetDouble(int ordinal)
		{
			assert(m_record);
			auto var = m_record->GetCollect((long)ordinal);
			assert(var.vt == VARENUM::VT_R8);
			return var.dblVal;
		}

		float MySqlDataReader::GetFloat(int ordinal)
		{
			assert(m_record);
			auto var = m_record->GetCollect((long)ordinal);
			assert(var.vt == VARENUM::VT_R4);
			return var.fltVal;
		}

		short MySqlDataReader::GetInt16(int ordinal)
		{
			assert(m_record);
			auto var = m_record->GetCollect((long)ordinal);
			assert(var.vt == VARENUM::VT_I2);
			return var.iVal;
		}

		int MySqlDataReader::GetInt(int ordinal)
		{
			assert(m_record);
			auto var = m_record->GetCollect((long)ordinal);
			assert(var.vt == VARENUM::VT_I4);
			return var.intVal;
		}

		int64_t MySqlDataReader::GetInt64(int ordinal)
		{
			assert(m_record);
			auto var = m_record->GetCollect((long)ordinal);
			assert(var.vt == VARENUM::VT_I8);
			return var.llVal;
		}

		unsigned short MySqlDataReader::GetUInt16(int ordinal)
		{
			assert(m_record);
			auto var = m_record->GetCollect((long)ordinal);
			assert(var.vt == VARENUM::VT_UI2);
			return var.uiVal;
		}

		unsigned int MySqlDataReader::GetUInt(int ordinal)
		{
			assert(m_record);
			auto var = m_record->GetCollect((long)ordinal);
			assert(var.vt == VARENUM::VT_UINT);
			return var.uintVal;
		}

		uint64_t MySqlDataReader::GetUInt64(int ordinal)
		{
			assert(m_record);
			auto var = m_record->GetCollect((long)ordinal);
			assert(var.vt == VARENUM::VT_UI8);
			return var.ullVal;
		}

		std::string MySqlDataReader::GetString(int ordinal)
		{
			bool eof = m_record->adoEOF;
			assert(m_record);
			auto var = m_record->GetCollect((long)ordinal);
			assert(var.vt == VARENUM::VT_BSTR);
			return (const char*)_bstr_t(var);
		}

		bool MySqlDataReader::IsDBNull(int ordinal)
		{
			assert(m_record);
			auto var = m_record->GetCollect((long)ordinal);
			return (var.vt == VARENUM::VT_NULL);
		}
		
		bool MySqlDataReader::GetBool(const std::string & ordinal)
		{
			assert(m_record);
			auto var = m_record->GetCollect(ordinal.data());
			assert(var.vt == VARENUM::VT_BOOL);
			return var.boolVal;
		}

		char MySqlDataReader::GetChar(const std::string & ordinal)
		{
			assert(m_record);
			auto var = m_record->GetCollect(ordinal.data());
			assert(var.vt == VARENUM::VT_I1);
			return var.cVal;
		}

		double MySqlDataReader::GetDouble(const std::string & ordinal)
		{
			assert(m_record);
			auto var = m_record->GetCollect(ordinal.data());
			assert(var.vt == VARENUM::VT_R8);
			return var.dblVal;
		}

		float MySqlDataReader::GetFloat(const std::string & ordinal)
		{
			assert(m_record);
			auto var = m_record->GetCollect(ordinal.data());
			assert(var.vt == VARENUM::VT_R4);
			return var.fltVal;
		}

		short MySqlDataReader::GetInt16(const std::string & ordinal)
		{
			assert(m_record);
			auto var = m_record->GetCollect(ordinal.data());
			assert(var.vt == VARENUM::VT_I2);
			return var.iVal;
		}

		int MySqlDataReader::GetInt(const std::string & ordinal)
		{
			assert(m_record);
			auto var = m_record->GetCollect(ordinal.data());
			assert(var.vt == VARENUM::VT_I4);
			return var.intVal;
		}

		int64_t MySqlDataReader::GetInt64(const std::string & ordinal)
		{
			assert(m_record);
			auto var = m_record->GetCollect(ordinal.data());
			assert(var.vt == VARENUM::VT_I8);
			return var.llVal;
		}

		unsigned short MySqlDataReader::GetUInt16(const std::string & ordinal)
		{
			assert(m_record);
			auto var = m_record->GetCollect(ordinal.data());
			assert(var.vt == VARENUM::VT_UI2);
			return var.uiVal;
		}

		unsigned int MySqlDataReader::GetUInt(const std::string & ordinal)
		{
			assert(m_record);
			auto var = m_record->GetCollect(ordinal.data());
			assert(var.vt == VARENUM::VT_UI4);
			return var.uintVal;
		}

		uint64_t MySqlDataReader::GetUInt64(const std::string & ordinal)
		{
			assert(m_record);
			auto var = m_record->GetCollect(ordinal.data());
			assert(var.vt == VARENUM::VT_UI8);
			return var.ullVal;
		}

		std::string MySqlDataReader::GetString(const std::string & ordinal)
		{
			bool eof = m_record->adoEOF;
			assert(m_record);
			auto var = m_record->GetCollect(ordinal.data());
			assert(var.vt == VARENUM::VT_BSTR);
			return (const char*)_bstr_t(var);
		}

		bool MySqlDataReader::IsDBNull(const std::string & ordinal)
		{
			assert(m_record);
			auto var = m_record->GetCollect(ordinal.data());
			return (var.vt == VARENUM::VT_NULL);
		}
	}
}