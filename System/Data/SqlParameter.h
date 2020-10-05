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
namespace System
{
	namespace Data
	{
		class SYSTEM_API SqlParameter : public DbDataParameter
		{
		public:
			SqlParameter();
			SqlParameter(const std::string & name, DataTypeEnum type, const _variant_t & value, ParameterDirectionEnum direction = ParameterDirectionEnum::adParamInput);
			SqlParameter(const char* &name, const _variant_t &value);
			SqlParameter(const std::string &name, const _variant_t &value);
			SqlParameter(const _ParameterPtr &param);
			virtual ~SqlParameter();
			virtual DataTypeEnum GetDbType() override;
			virtual void SetDbType(DataTypeEnum type) override;
			virtual bool IsNullable() override;
			virtual std::string GetParameterName() override;
			virtual void SetParameterName(const std::string &name) override;
			virtual std::string GetSourceColumn() override;
			virtual void SetSourceColumn() override;
			virtual char GetPrecision() override;
			virtual void SetPrecision(char precision) override;
			virtual char GetScale() override;
			virtual void SetScale(char scale) override;
			virtual _variant_t GetValue() override;
			virtual void SetValue(const _variant_t & value) override;
			virtual ParameterDirectionEnum GetDirection() override;
			virtual void SetDirection(ParameterDirectionEnum direction) override;
			const _ParameterPtr &GetParameter() const;
			static _ParameterPtr CreateParameter(const std::string &name, const _variant_t &value, ParameterDirectionEnum direction);
			static _ParameterPtr CreateParameter(const std::string & name, DataTypeEnum type, const _variant_t & value, ParameterDirectionEnum direction);

		private:
			SqlCommandPtr m_command;
			_ParameterPtr m_parameter;
		};
	}
}
#endif // !SYSTEM_DATA_SQLPARAMETER_H
