///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_DATA_SQLPARAMETER_H
#define SYSTEM_DATA_SQLPARAMETER_H
#include "System/Data/DbDataParameter.h"
#include "System/Data/Ptrs.h"
#include <string>
namespace System
{
	namespace Data
	{
		class SYSTEM_API SqlParameter : public DbDataParameter
		{
		public:
			SqlParameter();
			template <class T, class = typename std::enable_if<
				std::is_same<T, bool>::value
				|| std::is_same<T, __int8>::value
				|| std::is_same<T, __int16>::value
				|| std::is_same<T, __int32>::value
				|| std::is_same<T, __int64>::value
				|| std::is_same<T, unsigned __int8>::value
				|| std::is_same<T, unsigned __int16>::value
				|| std::is_same<T, unsigned __int32>::value
				|| std::is_same<T, unsigned __int64>::value
				|| std::is_same<T, float>::value
				|| std::is_same<T, double>::value
				|| std::is_same<T, const char*>::value
				|| std::is_same<T, CString>::value>::type>
				SqlParameter(const std::string & name, DataTypeEnum type, T value, ParameterDirectionEnum direction = ParameterDirectionEnum::adParamInput)
			{
				_variant_t var(value);
				m_parameter = CreateParameter(name, type, var, direction);
			}
			SqlParameter(const std::string & name, DataTypeEnum type, _variant_t & value, ParameterDirectionEnum direction = ParameterDirectionEnum::adParamInput);
			SqlParameter(const _ParameterPtr &param);
			virtual ~SqlParameter();
			virtual DataTypeEnum GetDbType() override;
			virtual void SetDbType(DataTypeEnum type) override;
			virtual bool IsNullable() override;
			virtual std::string GetParameterName() override;
			virtual void SetParameterName(const std::string &name) override;
			virtual std::string GetSourceColumn() override;
			virtual void SetSourceColumn() override;
			virtual __int8 GetPrecision() override;
			virtual void SetPrecision(char precision) override;
			virtual __int8 GetScale() override;
			virtual void SetScale(char scale) override;
			virtual _variant_t GetValue() override;
			virtual void SetValue(const _variant_t & value) override;
			virtual ParameterDirectionEnum GetDirection() override;
			virtual void SetDirection(ParameterDirectionEnum direction) override;
			const _ParameterPtr &GetParameter() const;
			static _ParameterPtr CreateParameter(const std::string & name, DataTypeEnum type, _variant_t & value, ParameterDirectionEnum direction);

		private:
			SqlCommandPtr m_command;
			_ParameterPtr m_parameter;
		};
	}
}
#endif // !SYSTEM_DATA_SQLPARAMETER_H
