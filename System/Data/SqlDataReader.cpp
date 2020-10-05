///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Data/SqlDataReader.h"
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
			return -1;
		}

		void SqlDataReader::Close()
		{
			assert(m_record);
			m_record->Close();
			m_record = nullptr;
		}

		bool SqlDataReader::Read()
		{
			assert(m_record);
			return !m_record->GetadoEOF();
		}

		bool SqlDataReader::NextResult()
		{
			assert(m_record);
			HRESULT hr = m_record->MoveNext();
			return !FAILED(hr);
		}

		bool SqlDataReader::GetBool(int ordinal)
		{
			assert(m_record);
			auto var = m_record->GetCollect((long)ordinal);
			assert(var.vt == VARENUM::VT_BOOL);
			return var.boolVal;
		}

		char SqlDataReader::GetChar(int ordinal)
		{
			assert(m_record);
			auto var = m_record->GetCollect((long)ordinal);
			assert(var.vt == VARENUM::VT_I1);
			return var.cVal;
		}

		double SqlDataReader::GetDouble(int ordinal)
		{
			assert(m_record);
			auto var = m_record->GetCollect((long)ordinal);
			assert(var.vt == VARENUM::VT_R8);
			return var.dblVal;
		}

		float SqlDataReader::GetFloat(int ordinal)
		{
			assert(m_record);
			auto var = m_record->GetCollect((long)ordinal);
			assert(var.vt == VARENUM::VT_R4);
			return var.fltVal;
		}

		short SqlDataReader::GetInt16(int ordinal)
		{
			assert(m_record);
			auto var = m_record->GetCollect((long)ordinal);
			assert(var.vt == VARENUM::VT_I2);
			return var.iVal;
		}

		int SqlDataReader::GetInt(int ordinal)
		{
			assert(m_record);
			auto var = m_record->GetCollect((long)ordinal);
			assert(var.vt == VARENUM::VT_I4 || var.vt == VARENUM::VT_INT);
			return var.intVal;
		}

		int64_t SqlDataReader::GetInt64(int ordinal)
		{
			assert(m_record);
			auto var = m_record->GetCollect((long)ordinal);
			assert(var.vt == VARENUM::VT_I8);
			return var.llVal;
		}

		unsigned short SqlDataReader::GetUInt16(int ordinal)
		{
			assert(m_record);
			auto var = m_record->GetCollect((long)ordinal);
			assert(var.vt == VARENUM::VT_UI2);
			return var.uiVal;
		}

		unsigned int SqlDataReader::GetUInt(int ordinal)
		{
			assert(m_record);
			auto var = m_record->GetCollect((long)ordinal);
			assert(var.vt == VARENUM::VT_UI4 || var.vt == VARENUM::VT_UINT);
			return var.uintVal;
		}

		uint64_t SqlDataReader::GetUInt64(int ordinal)
		{
			assert(m_record);
			auto var = m_record->GetCollect((long)ordinal);
			assert(var.vt == VARENUM::VT_UI8);
			return var.ullVal;
		}

		std::string SqlDataReader::GetString(int ordinal)
		{
			bool eof = m_record->adoEOF;
			assert(m_record);
			auto var = m_record->GetCollect((long)ordinal);
			assert(var.vt == VARENUM::VT_BSTR);
			return (const char*)_bstr_t(var);
		}

		bool SqlDataReader::IsDBNull(int ordinal)
		{
			assert(m_record);
			auto var = m_record->GetCollect((long)ordinal);
			return (var.vt == VARENUM::VT_NULL);
		}
		
		bool SqlDataReader::GetBool(const std::string & ordinal)
		{
			assert(m_record);
			auto var = m_record->GetCollect(ordinal.data());
			assert(var.vt == VARENUM::VT_BOOL);
			return var.boolVal;
		}

		char SqlDataReader::GetChar(const std::string & ordinal)
		{
			assert(m_record);
			auto var = m_record->GetCollect(ordinal.data());
			assert(var.vt == VARENUM::VT_I1);
			return var.cVal;
		}

		double SqlDataReader::GetDouble(const std::string & ordinal)
		{
			assert(m_record);
			auto var = m_record->GetCollect(ordinal.data());
			assert(var.vt == VARENUM::VT_R8);
			return var.dblVal;
		}

		float SqlDataReader::GetFloat(const std::string & ordinal)
		{
			assert(m_record);
			auto var = m_record->GetCollect(ordinal.data());
			assert(var.vt == VARENUM::VT_R4);
			return var.fltVal;
		}

		short SqlDataReader::GetInt16(const std::string & ordinal)
		{
			assert(m_record);
			auto var = m_record->GetCollect(ordinal.data());
			assert(var.vt == VARENUM::VT_I2);
			return var.iVal;
		}

		int SqlDataReader::GetInt(const std::string & ordinal)
		{
			assert(m_record);
			auto var = m_record->GetCollect(ordinal.data());
			assert(var.vt == VARENUM::VT_I4 || var.vt == VARENUM::VT_INT);
			return var.intVal;
		}

		int64_t SqlDataReader::GetInt64(const std::string & ordinal)
		{
			assert(m_record);
			auto var = m_record->GetCollect(ordinal.data());
			assert(var.vt == VARENUM::VT_I8);
			return var.llVal;
		}

		unsigned short SqlDataReader::GetUInt16(const std::string & ordinal)
		{
			assert(m_record);
			auto var = m_record->GetCollect(ordinal.data());
			assert(var.vt == VARENUM::VT_UI2);
			return var.uiVal;
		}

		unsigned int SqlDataReader::GetUInt(const std::string & ordinal)
		{
			assert(m_record);
			auto var = m_record->GetCollect(ordinal.data());
			assert(var.vt == VARENUM::VT_UI4 || var.vt == VARENUM::VT_UINT);
			return var.uintVal;
		}

		uint64_t SqlDataReader::GetUInt64(const std::string & ordinal)
		{
			assert(m_record);
			auto var = m_record->GetCollect(ordinal.data());
			assert(var.vt == VARENUM::VT_UI8);
			return var.ullVal;
		}

		std::string SqlDataReader::GetString(const std::string & ordinal)
		{
			bool eof = m_record->adoEOF;
			assert(m_record);
			auto var = m_record->GetCollect(ordinal.data());
			assert(var.vt == VARENUM::VT_BSTR);
			return (const char*)_bstr_t(var);
		}

		bool SqlDataReader::IsDBNull(const std::string & ordinal)
		{
			assert(m_record);
			auto var = m_record->GetCollect(ordinal.data());
			return (var.vt == VARENUM::VT_NULL);
		}
	}
}