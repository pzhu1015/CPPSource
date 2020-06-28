///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "Logger/Logger.h"
#include "System/FileInfo.h"

using namespace System;
using namespace System::Logger;
using namespace System::IO;
int main(int argc, char** argv)
{
	FileInfo info(argv[0]);
	std::string config_path = info.DirectoryName();
	config_path.append("log.properties");
	System::Logger::Logger::Init(config_path);

	for (int i = 0; i < 1000; i++)
	{
		LOGDEBUG("this is debug %d", i);
		LOGINFO("this is info %d", i);
		LOGERROR("this is error %d", i);
		LOGFATAL("this is fatal %d", i);
		LOGWARN("this is warn %d", i);
	}
	system("pause");
	return 0;
}