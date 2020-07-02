///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_IO_FILESTREAM_H
#define SYSTEM_IO_FILESTREAM_H

#include "System/DllExport.h"
#include "System/Object.h"
#include "System/IDisposable.h"
#include "System/IO/Stream.h"
#include "System/IO/FileMode.h"
#include "System/IO/FileAccess.h"
#include <fstream>

namespace System
{
	namespace IO
	{
		class SYSTEM_API FileStream : public Stream
		{
		public:
			FileStream(const std::string &filename, FileMode mode);
			FileStream(const std::string &filename, FileMode mode, FileAccess access);
			~FileStream();

			virtual bool GetCanRead() const override;
			virtual bool GetCanSeek() const override;
			virtual bool GetCanWrite() const override;
			virtual int64_t GetLength() const override;
			virtual int64_t GetPosition() const override;
			virtual void Flush() override;
			virtual int Read(char* buffer, int offset, int count) override;
			virtual int64_t Seek(int64_t offset, SeekOrigin origin) override;
			virtual void SetLength(int64_t value) override;
			virtual void Write(char* buffer, int offset, int count) override;
			virtual void Dispose() override;
		private:
			std::fstream* m_stream;
			FileMode m_mode;
			FileAccess m_access;
		};
	}
}

#endif

