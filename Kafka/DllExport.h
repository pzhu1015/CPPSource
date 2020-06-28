///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifdef _WIN32

#ifdef KAFKA_EXPORTS
#define KAFKA_API __declspec(dllexport)
#else
#define KAFKA_API __declspec(dllimport)
#endif

#pragma warning(disable: 4251)
#pragma warning(disable: 4996)
#endif