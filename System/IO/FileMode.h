///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_IO_FILEMODE_H
#define SYSTEM_IO_FILEMODE_H

namespace System
{
	namespace IO
	{
		enum class FileMode
		{
			CreateNew = 1,
			Create = 2,
			Open = 3,
			OpenOrCreate = 4,
			Truncate = 5,
			Append = 6
		};
	}
}

#endif //!SYSTEM_IO_FILEMODE_H