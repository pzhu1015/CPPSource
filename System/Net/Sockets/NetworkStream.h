///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_NET_SOCKETS_NETWORKSTREAM_H
#define SYSTEM_NET_SOCKETS_NETWORKSTREAM_H
#include "System/DllExport.h"
#include "System/IO/Stream.h"

using namespace System::IO;

namespace System
{
	namespace Net
	{
		namespace Sockets
		{
			class SYSTEM_API NetworkStream : public Stream
			{
			public:
				NetworkStream();
				virtual ~NetworkStream();
				virtual bool GetCanRead() const;
				virtual bool GetCanSeek() const;
				virtual bool GetCanWrite() const;
				virtual int64_t GetLength() const;
				virtual int64_t GetPosition() const;
				virtual void Flush();
				virtual int Read(char* buffer, int offset, int count);
				virtual int64_t Seek(int64_t offset, SeekOrigin origin);
				virtual void SetLength(int64_t value);
				virtual void Write(char* buffer, int offset, int count);
			};
		}
	}
}

#endif // !SYSTEM_NET_SOCKETS_NETWORKSTREAM_H
