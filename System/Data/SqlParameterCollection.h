///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_DATA_SQLPARAMETERCOLLECTION_H
#define SYSTEM_DATA_SQLPARAMETERCOLLECTION_H
#include "System/Base/DllExport.h"
#include "System/Data/ADO.h"
#include "System/Data/DbParameterCollection.h"
#include <unordered_map>
namespace System
{
	namespace Data
	{
		class SYSTEM_API SqlParameterCollection : public DbParameterCollection
		{
		public:
			SqlParameterCollection();
			virtual ~SqlParameterCollection();
			virtual int GetCount() override;
			virtual void Clear() override;
			virtual int Add(const DbParameterPtr &value) override;
			std::vector<SqlParameterPtr>::iterator begin() {
				return m_parameters.begin();
			}

			std::vector<SqlParameterPtr>::iterator end() {
				return m_parameters.end();
			}
			SqlParameterPtr& Add(SqlParameterPtr &value);
			SqlParameterPtr& Add(const std::string &name, const _variant_t &value);
			SqlParameterPtr& Add(const std::string &name, DataTypeEnum type, const _variant_t &value);
		private:
			std::vector<SqlParameterPtr> m_parameters;
		};
	}
}
#endif // !SYSTEM_DATA_SQLPARAMETERCOLLECTION_H
