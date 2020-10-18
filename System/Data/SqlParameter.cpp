///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Data/SqlParameter.h"
#include "System/Base/Object.h"
#include "System/Exceptions/NotSupportedException.h"
#include "System/Exceptions/NullReferenceException.h"
using namespace System::Exceptions;
namespace System
{
	namespace Data
	{
		SqlParameter::SqlParameter()
		{
			m_parameter = CreateParameter("", DataTypeEnum::adEmpty, _variant_t(), ParameterDirectionEnum::adParamInput);
			if (m_parameter == nullptr)
			{
				throw NullReferenceException("m_parameter is nullptr");
			}
		}

		SqlParameter::SqlParameter(const std::string & name, DataTypeEnum type, _variant_t & value, ParameterDirectionEnum direction)
		{
			m_parameter = CreateParameter(name, type, value, direction);
			if (m_parameter == nullptr)
			{
				throw NullReferenceException("m_parameter is nullptr");
			}
		}

		SqlParameter::SqlParameter(const _ParameterPtr &param)
		{
			m_parameter = param;
		}

		SqlParameter::~SqlParameter()
		{
			m_command = nullptr;
		}

		DataTypeEnum SqlParameter::GetDbType()
		{
			if (m_parameter == nullptr)
			{
				throw NullReferenceException("m_parameter is nullptr");
			}
			return m_parameter->GetType();
		}

		void SqlParameter::SetDbType(DataTypeEnum type)
		{
			if (m_parameter == nullptr)
			{
				throw NullReferenceException("m_parameter is nullptr");
			}
			m_parameter->PutType(type);
		}

		bool SqlParameter::IsNullable()
		{
			throw NotSupportedException(__func__);
		}

		std::string SqlParameter::GetParameterName()
		{
			if (m_parameter == nullptr)
			{
				throw NullReferenceException("m_parameter is nullptr");
			}
			return (const char*)m_parameter->GetName();
		}

		void SqlParameter::SetParameterName(const std::string & name)
		{
			if (m_parameter == nullptr)
			{
				throw NullReferenceException("m_parameter is nullptr");
			}
			m_parameter->PutName(name.data());
		}

		std::string SqlParameter::GetSourceColumn()
		{
			throw NotSupportedException(__func__);
		}

		void SqlParameter::SetSourceColumn()
		{
			throw NotSupportedException(__func__);
		}

		__int8 SqlParameter::GetPrecision()
		{
			if (m_parameter == nullptr)
			{
				throw NullReferenceException("m_parameter is nullptr");
			}
			return m_parameter->GetPrecision();
		}

		void SqlParameter::SetPrecision(char precision)
		{
			if (m_parameter == nullptr)
			{
				throw NullReferenceException("m_parameter is nullptr");
			}
			m_parameter->PutPrecision(precision);
		}

		__int8 SqlParameter::GetScale()
		{
			if (m_parameter == nullptr)
			{
				throw NullReferenceException("m_parameter is nullptr");
			}
			return m_parameter->GetNumericScale();
		}

		void SqlParameter::SetScale(char scale)
		{
			if (m_parameter == nullptr)
			{
				throw NullReferenceException("m_parameter is nullptr");
			}
			return m_parameter->PutNumericScale(scale);
		}

		_variant_t SqlParameter::GetValue()
		{
			if (m_parameter == nullptr)
			{
				throw NullReferenceException("m_parameter is nullptr");
			}
			return m_parameter->GetValue();
		}

		void SqlParameter::SetValue(const _variant_t & value)
		{
			if (m_parameter == nullptr)
			{
				throw NullReferenceException("m_parameter is nullptr");
			}
			m_parameter->PutValue(value);
		}

		ParameterDirectionEnum SqlParameter::GetDirection()
		{
			if (m_parameter == nullptr)
			{
				throw NullReferenceException("m_parameter is nullptr");
			}
			return m_parameter->GetDirection();
		}

		void SqlParameter::SetDirection(ParameterDirectionEnum direction)
		{
			if (m_parameter == nullptr)
			{
				throw NullReferenceException("m_parameter is nullptr");
			}
			m_parameter->PutDirection(direction);
		}

		const _ParameterPtr & SqlParameter::GetParameter() const
		{
			return m_parameter;
		}

		_ParameterPtr SqlParameter::CreateParameter(const std::string & name, DataTypeEnum type, _variant_t & value, ParameterDirectionEnum direction)
		{
			long size = 0;
			_CommandPtr command;
			command.CreateInstance(__uuidof(Command));
			if (command == nullptr)
			{
				throw NullReferenceException("command is nullptr");
			}
			switch (type)
			{
			case DataTypeEnum::adBoolean:
				size = sizeof(char);
				value.vt = VARENUM::VT_BOOL;
				break;
			case DataTypeEnum::adTinyInt:
				size = sizeof(char);
				value.vt = VARENUM::VT_I1;
				break;
			case DataTypeEnum::adSmallInt:
				size = sizeof(short);
				value.vt = VARENUM::VT_I2;
				break;
			case DataTypeEnum::adInteger:
				size = sizeof(int);
				value.vt = VARENUM::VT_I4;
				break;
			case DataTypeEnum::adBigInt:
				size = sizeof(int64_t);
				value.vt = VT_I8;
				break;
			case DataTypeEnum::adUnsignedTinyInt:
				size = sizeof(unsigned char);
				value.vt = VARENUM::VT_UI1;
				break;
			case DataTypeEnum::adUnsignedSmallInt:
				size = sizeof(unsigned short);
				value.vt = VARENUM::VT_UI2;
				break;
			case DataTypeEnum::adUnsignedInt:
				size = sizeof(unsigned int);
				value.vt = VARENUM::VT_UI4;
				break;
			case DataTypeEnum::adUnsignedBigInt:
				size = sizeof(int64_t);
				value.vt = VT_UI8;
				break;
			case DataTypeEnum::adDecimal:
				throw NotSupportedException(__func__);
				break;
			case DataTypeEnum::adDouble:
				size = sizeof(double);
				value.vt = VARENUM::VT_R8;
				break;
			case DataTypeEnum::adVarChar:
			case DataTypeEnum::adBSTR:
			case DataTypeEnum::adVarWChar:
			case DataTypeEnum::adWChar:
				size = wcslen(value.bstrVal);
				if (size == 0)
				{
					size = 1;
				}
				value.vt = VARENUM::VT_BSTR;
				break;
			case DataTypeEnum::adDate:
			case DataTypeEnum::adDBDate:
			case DataTypeEnum::adDBTimeStamp:
				throw NotSupportedException(__func__);
				break;
			default:
				throw NotSupportedException(__func__);
				break;
			}
			_ParameterPtr parameter = command->CreateParameter(name.data(), type, direction, size, value);
			if (parameter == nullptr)
			{
				throw NullReferenceException("parameter is nullptr");
			}
			return parameter;
		}
	}
}