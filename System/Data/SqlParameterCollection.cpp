///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Data/SqlParameterCollection.h"
#include "System/Data/SqlParameter.h"
#include "System/Data/DbParameter.h"
#include "System/Exceptions/NullReferenceException.h"
using namespace System::Exceptions;
namespace System
{
	namespace Data
	{
		SqlParameterCollection::SqlParameterCollection()
		{
		}
		SqlParameterCollection::~SqlParameterCollection()
		{
		}
		int SqlParameterCollection::GetCount()
		{
			return m_parameters.size();
		}
		void SqlParameterCollection::Clear()
		{
			m_parameters.clear();
		}
		int SqlParameterCollection::Add(const DbParameterPtr & value)
		{
			m_parameters.push_back(std::dynamic_pointer_cast<SqlParameter>(value));
			return m_parameters.size();
		}
		SqlParameterPtr & SqlParameterCollection::Add(SqlParameterPtr & value)
		{
			m_parameters.push_back(value);
			return *(m_parameters.rbegin());
		}
		SqlParameterPtr& SqlParameterCollection::Add(const std::string & name, const _variant_t & value)
		{
			DataTypeEnum type = DataTypeEnum::adEmpty;
			auto param = std::make_shared<SqlParameter>(name, type, value);
			m_parameters.push_back(param);
			return *(m_parameters.rbegin());
		}
		SqlParameterPtr & SqlParameterCollection::Add(const std::string & name, DataTypeEnum type, const _variant_t & value)
		{
			auto param = std::make_shared<SqlParameter>(name, type, value);
			m_parameters.push_back(param);
			return *(m_parameters.rbegin());
		}
	}
}