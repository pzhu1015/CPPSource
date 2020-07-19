///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_IO_PTRS_H
#define SYSTEM_IO_PTRS_H
#include <memory>
namespace System
{
	namespace IO
	{
		class Stream;
		class BufferedStream;
		class FileStream;
		class Encoding;
		class FileInfo;
		class DirectoryInfo;
		typedef std::shared_ptr<Stream> StreamPtr;
		typedef std::shared_ptr<BufferedStream> BufferedStreamPtr;
		typedef std::shared_ptr<FileStream> FileStreamPtr;
		typedef std::shared_ptr<Encoding> EncodingPtr;
		typedef std::shared_ptr<FileInfo> FileInfoPtr;
		typedef std::shared_ptr<DirectoryInfo> DirectoryInfoPtr;	
	}
}
#endif // !SYSTEM_IO_PTRS_H
