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
namespace System
{
	namespace Data
	{
		SqlParameter::SqlParameter()
		{
			m_parameter = CreateParameter("", _variant_t(), ParameterDirectionEnum::adParamInput);
		}

		SqlParameter::SqlParameter(const std::string & name, DataTypeEnum type, const _variant_t & value, ParameterDirectionEnum direction)
		{
			m_parameter = CreateParameter(name, type, value, direction);
		}

		SqlParameter::SqlParameter(const char *& name, const _variant_t & value)
		{
			m_parameter = CreateParameter(name, value, ParameterDirectionEnum::adParamInput);
		}

		SqlParameter::SqlParameter(const std::string & name, const _variant_t & value)
		{
			m_parameter = CreateParameter(name, value, ParameterDirectionEnum::adParamInput);
		}

		SqlParameter::SqlParameter(const _ParameterPtr &param)
		{
			m_parameter = param;
		}

		SqlParameter::~SqlParameter()
		{
		}

		DataTypeEnum SqlParameter::GetDbType()
		{
			assert(m_parameter);
			return m_parameter->GetType();
		}

		void SqlParameter::SetDbType(DataTypeEnum type)
		{
			assert(m_parameter);
			m_parameter->PutType(type);
		}

		bool SqlParameter::IsNullable()
		{
			assert(m_parameter);
			return false;
		}

		std::string SqlParameter::GetParameterName()
		{
			assert(m_parameter);
			return (const char*)m_parameter->GetName();
		}

		void SqlParameter::SetParameterName(const std::string & name)
		{
			assert(m_parameter);
			m_parameter->PutName(name.data());
		}

		std::string SqlParameter::GetSourceColumn()
		{
			assert(m_parameter);
			return "";
		}

		void SqlParameter::SetSourceColumn()
		{
			assert(m_parameter);
		}

		char SqlParameter::GetPrecision()
		{
			assert(m_parameter);
			return m_parameter->GetPrecision();
		}

		void SqlParameter::SetPrecision(char precision)
		{
			assert(m_parameter);
			m_parameter->PutPrecision(precision);
		}

		char SqlParameter::GetScale()
		{
			assert(m_parameter);
			return m_parameter->GetNumericScale();
		}

		void SqlParameter::SetScale(char scale)
		{
			assert(m_parameter);
			return m_parameter->PutNumericScale(scale);
		}

		_variant_t SqlParameter::GetValue()
		{
			assert(m_parameter);
			return m_parameter->GetValue();
		}

		void SqlParameter::SetValue(const _variant_t & value)
		{
			assert(m_parameter);
			m_parameter->PutValue(value);
		}

		ParameterDirectionEnum SqlParameter::GetDirection()
		{
			assert(m_parameter);
			return m_parameter->GetDirection();
		}

		void SqlParameter::SetDirection(ParameterDirectionEnum direction)
		{
			assert(m_parameter);
			m_parameter->PutDirection(direction);
		}

		const _ParameterPtr & SqlParameter::GetParameter() const
		{
			return m_parameter;
		}

		_ParameterPtr SqlParameter::CreateParameter(const std::string & name, const _variant_t & value, ParameterDirectionEnum direction)
		{
			long size = 0;
			_CommandPtr command;
			command.CreateInstance(__uuidof(Command));
			assert(command);
			DataTypeEnum type = DataTypeEnum::adEmpty;
			switch (value.vt)
			{
			case VARENUM::VT_I1:
				size = sizeof(char);
				type = DataTypeEnum::adTinyInt;
				break;
			case VARENUM::VT_I2:
				size = sizeof(short);
				type = DataTypeEnum::adSmallInt;
				break;
			case VARENUM::VT_I4:
			case VARENUM::VT_INT:
				size = sizeof(int);
				type = DataTypeEnum::adInteger;
				break;
			case VARENUM::VT_I8:
				size = sizeof(int64_t);
				type = DataTypeEnum::adBigInt;
				break;
			case VARENUM::VT_UI1:
				size = sizeof(unsigned char);
				type = DataTypeEnum::adUnsignedTinyInt;
				break;
			case VARENUM::VT_UI2:
				size = sizeof(unsigned short);
				type = DataTypeEnum::adUnsignedSmallInt;
				break;
			case VARENUM::VT_UI4:
			case VARENUM::VT_UINT:
				size = sizeof(unsigned int);
				type = DataTypeEnum::adUnsignedInt;
				break;
			case VARENUM::VT_UI8:
				size = sizeof(uint64_t);
				type = DataTypeEnum::adUnsignedBigInt;
				break;
			case VARENUM::VT_R4:
				size = sizeof(float);
				type = DataTypeEnum::adDecimal;
				break;
			case VARENUM::VT_R8:
				size = sizeof(double);
				type = DataTypeEnum::adDouble;
				break;
			case VARENUM::VT_BOOL:
				size = sizeof(bool);
				type = DataTypeEnum::adBoolean;
				break;
			case VARENUM::VT_BSTR:
				type = DataTypeEnum::adBSTR;
				break;
			default:
				type = DataTypeEnum::adEmpty;
				break;
			}
			_ParameterPtr parameter = command->CreateParameter(name.data(), type, direction, size, value);
			assert(parameter);
			return parameter;
		}

		_ParameterPtr SqlParameter::CreateParameter(const std::string & name, DataTypeEnum type, const _variant_t & value, ParameterDirectionEnum direction)
		{
			long size = 0;
			_CommandPtr command;
			command.CreateInstance(__uuidof(Command));
			assert(command);
			switch (value.vt)
			{
			case VARENUM::VT_I1:
				size = sizeof(char);
				break;
			case VARENUM::VT_I2:
				size = sizeof(short);
				break;
			case VARENUM::VT_I4:
			case VARENUM::VT_INT:
				size = sizeof(int);
				break;
			case VARENUM::VT_I8:
				size = sizeof(int64_t);
				break;
			case VARENUM::VT_UI1:
				size = sizeof(unsigned char);
				break;
			case VARENUM::VT_UI2:
				size = sizeof(unsigned short);
				break;
			case VARENUM::VT_UI4:
			case VARENUM::VT_UINT:
				size = sizeof(unsigned int);
				break;
			case VARENUM::VT_UI8:
				size = sizeof(uint64_t);
				break;
			case VARENUM::VT_R4:
				size = sizeof(float);
				break;
			case VARENUM::VT_R8:
				size = sizeof(double);
				break;
			case VARENUM::VT_BOOL:
				size = sizeof(bool);
				break;
			case VARENUM::VT_BSTR:
				break;
			default:
				break;
			}
			_ParameterPtr parameter = command->CreateParameter(name.data(), type, direction, size, value);
			assert(parameter);
			return parameter;
		}
	}
}