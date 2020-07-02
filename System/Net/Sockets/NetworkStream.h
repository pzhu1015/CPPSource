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
			};
		}
	}
}

#endif // !SYSTEM_NET_SOCKETS_NETWORKSTREAM_H
