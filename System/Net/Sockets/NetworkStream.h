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
#include "System/IO/FileAccess.h"

using namespace System::IO;

namespace System
{
	namespace Net
	{
		namespace Sockets
		{
			class Socket;
			class SYSTEM_API NetworkStream : public Stream
			{
			public:
				NetworkStream(Socket* socket);
				NetworkStream(Socket* socket, bool ownsSocket);
				NetworkStream(Socket* socket, FileAccess access);
				NetworkStream(Socket* socket, FileAccess access, bool ownsSocket);
				virtual ~NetworkStream();
				virtual bool GetCanRead() const override;
				virtual bool GetCanWrite() const override;
				virtual bool GetDataAvailable() const;
				virtual int GetReadTimeout() const override;
				virtual void SetReadTimeout(int timeout) override;
				virtual int GetWriteTimeout() const override;
				virtual void SetWriteTimeout(int timeout) override;
				virtual int Read(char* buffer, int offset, int count) override;
				virtual void Write(char* buffer, int offset, int count) override;
				void Close(int timeout);

				virtual bool GetCanSeek() const override;//Not Support
				virtual int64_t GetLength() const override;//Not Support
				virtual int64_t GetPosition() const override;//Not Support
				virtual void Flush() override;//Not Support
				virtual int64_t Seek(int64_t offset, SeekOrigin origin) override;//Not Support
				virtual void SetLength(int64_t value) override;//Not Support

				
			protected:
				bool GetWriteable() const;
				void SetWriteable(bool writeable);
				bool GetReadable() const;
				void SetReadable(bool readable);
				Socket* GetSocket() const;
				virtual void Dispose(bool disposing) override;
			private:
				Socket* m_socket = nullptr;
				bool m_ownsocket = false;
				FileAccess m_access = FileAccess::ReadWrite;
			};
		}
	}
}

#endif // !SYSTEM_NET_SOCKETS_NETWORKSTREAM_H
