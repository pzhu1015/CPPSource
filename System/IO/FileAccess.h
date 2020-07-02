///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_IO_FILEACCESS_H
#define SYSTEM_IO_FILEACCESS_H
#include <fstream>

namespace System
{
	namespace IO
	{
		enum class FileAccess
		{
			Read = std::ios::in,
			Write = std::ios::out,
			ReadWrite = std::ios::in | std::ios::out
		};
	}
}

#endif //!SYSTEM_IO_FILEACCESS_H