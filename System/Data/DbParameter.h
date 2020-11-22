///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_DATA_DBPARAMETER_H
#define SYSTEM_DATA_DBPARAMETER_H
#include "System/Data/ADO.h"
#include "System/Base/DllExport.h"
#include "System/Base/Ptrs.h"
#include <string>
namespace System
{
	namespace Data
	{
		class SYSTEM_API DbParameter
		{
		public:
			virtual DataTypeEnum GetDbType() = 0;
			virtual void SetDbType(DataTypeEnum type) = 0;
			virtual bool IsNullable() = 0;
			virtual std::string GetParameterName() = 0;
			virtual void SetParameterName(const std::string &name) = 0;
			virtual std::string GetSourceColumn() = 0;
			virtual void SetSourceColumn() = 0;
			virtual __int8 GetPrecision() = 0;
			virtual void SetPrecision(char precision) = 0;
			virtual __int8 GetScale() = 0;
			virtual void SetScale(char scale) = 0;
			virtual _variant_t GetValue() = 0;
			virtual void SetValue(const _variant_t & value) = 0;
			virtual ParameterDirectionEnum GetDirection() = 0;
			virtual void SetDirection(ParameterDirectionEnum direction) = 0;
		};
	}
}
#endif // !SYSTEM_DATA_DBPARAMETER_H
