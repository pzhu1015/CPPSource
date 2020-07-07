///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_IO_SEEKORIGIN_H
#define SYSTEM_IO_SEEKORIGIN_H
#include <fstream>
namespace System
{
	namespace IO
	{
		enum class SeekOrigin
		{
			Begin = std::ios::beg,
			Current = std::ios::cur,
			End = std::ios::end
		};
	}
}

#endif // !SYSTEM_IO_SEEKORIGIN_H
