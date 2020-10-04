///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_CONFIGURATIONS_PTRS_H
#define SYSTEM_CONFIGURATIONS_PTRS_H
#include <memory>
namespace System
{
	namespace Configurations
	{
		class Configuration;
		typedef std::shared_ptr<Configuration> ConfigurationPtr;
	}
}
#endif // !SYSTEM_CONFIGURATIONS_PTRS_H
