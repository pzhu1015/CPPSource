///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Data/MySqlParameter.h"
#include "System/Base/Object.h"
namespace System
{
	namespace Data
	{
		MySqlParameter::MySqlParameter()
		{
			m_parameter = CreateParameter("");
		}

		MySqlParameter::MySqlParameter(const char *& name, const _variant_t & value)
		{
			m_parameter = CreateParameter(name, value);
		}

		MySqlParameter::MySqlParameter(const std::string & name, const _variant_t & value)
		{
			m_parameter = CreateParameter(name, value);
		}

		MySqlParameter::MySqlParameter(const _ParameterPtr &param)
		{
			m_parameter = param;
		}

		MySqlParameter::~MySqlParameter()
		{
		}

		DataTypeEnum MySqlParameter::GetDbType()
		{
			assert(m_parameter);
			return m_parameter->GetType();
		}

		void MySqlParameter::SetDbType(DataTypeEnum type)
		{
			assert(m_parameter);
			m_parameter->PutType(type);
		}

		bool MySqlParameter::IsNullable()
		{
			assert(m_parameter);
			return false;
		}

		std::string MySqlParameter::GetParameterName()
		{
			assert(m_parameter);
			return (const char*)m_parameter->GetName();
		}

		void MySqlParameter::SetParameterName(const std::string & name)
		{
			assert(m_parameter);
			m_parameter->PutName(name.data());
		}

		std::string MySqlParameter::GetSourceColumn()
		{
			assert(m_parameter);
			return "";
		}

		void MySqlParameter::SetSourceColumn()
		{
			assert(m_parameter);
		}

		char MySqlParameter::GetPrecision()
		{
			assert(m_parameter);
			return m_parameter->GetPrecision();
		}

		void MySqlParameter::SetPrecision(char precision)
		{
			assert(m_parameter);
			m_parameter->PutPrecision(precision);
		}

		char MySqlParameter::GetScale()
		{
			assert(m_parameter);
			return m_parameter->GetNumericScale();
		}

		void MySqlParameter::SetScale(char scale)
		{
			assert(m_parameter);
			return m_parameter->PutNumericScale(scale);
		}

		_variant_t MySqlParameter::GetValue()
		{
			assert(m_parameter);
			return m_parameter->GetValue();
		}

		void MySqlParameter::SetValue(const _variant_t & value)
		{
			assert(m_parameter);
			m_parameter->PutValue(value);
		}

		ParameterDirectionEnum MySqlParameter::GetDirection()
		{
			assert(m_parameter);
			return m_parameter->GetDirection();
		}

		void MySqlParameter::SetDirection(ParameterDirectionEnum direction)
		{
			assert(m_parameter);
			m_parameter->PutDirection(direction);
		}

		const _ParameterPtr & MySqlParameter::GetParameter() const
		{
			return m_parameter;
		}

		_ParameterPtr MySqlParameter::CreateParameter(const std::string & name, const _variant_t & value)
		{
			_CommandPtr command;
			command.CreateInstance(__uuidof(Command));
			assert(command);
			DataTypeEnum type = DataTypeEnum::adEmpty;
			switch (value.vt)
			{
			case VARENUM::VT_I1:
				type = DataTypeEnum::adChar;
				break;
			case VARENUM::VT_I2:
				type = DataTypeEnum::adSmallInt;
				break;
			case VARENUM::VT_I4:
				type = DataTypeEnum::adInteger;
				break;
			case VARENUM::VT_I8:
				type = DataTypeEnum::adBigInt;
				break;
			case VARENUM::VT_R4:
				type = DataTypeEnum::adDecimal;
				break;
			case VARENUM::VT_R8:
				type = DataTypeEnum::adDouble;
				break;
			case VARENUM::VT_BOOL:
				type = DataTypeEnum::adBoolean;
				break;
			case VARENUM::VT_BSTR:
				type = DataTypeEnum::adBSTR;
				break;
			default:
				type = DataTypeEnum::adEmpty;
				break;
			}
			_ParameterPtr parameter = command->CreateParameter(name.data(), type, ParameterDirectionEnum::adParamInput, 0, value);
			assert(parameter);
			return parameter;
		}

	}
}