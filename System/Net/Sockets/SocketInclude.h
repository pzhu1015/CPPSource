///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_NET_SOCKETS_SOCKETINCLUDE_H
#define SYSTEM_NET_SOCKETS_SOCKETINCLUDE_H

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define FD_SETSIZE 10240
#include <Windows.h>
#include <WinSock2.h>
#else
#include <unistd.h>
#include <arpa/net.h>
#include <string.h>
#define SOCKET int
#define INVALID_SOCKET	(SOCKET)(~0)
#define SOCK_ERROR				(-1)
#endif

#endif // !SYSTEM_NET_SOCKETS_SOCKETINCLUDE_H