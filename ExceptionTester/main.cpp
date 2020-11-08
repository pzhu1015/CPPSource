///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Exceptions/Exception.h"
#include "System/Exceptions/ArgumentException.h"
#include "System/Exceptions/ArgumentNullException.h"
#include "System/Exceptions/ArgumentOutOfRangeException.h"
#include "System/Exceptions/ArrayTypeMismatchException.h"
#include "System/Exceptions/IndexOutOfRangeException.h"
#include "System/Exceptions/InvalidOperationException.h"
#include "System/Exceptions/IOException.h"
#include "System/Exceptions/NotSupportedException.h"
#include "System/Exceptions/NullReferenceException.h"
#include "System/Exceptions/OverflowException.h"
#include "System/Exceptions/RedisException.h"
#include "System/Exceptions/SocketException.h"
#include "System/Exceptions/SqlException.h"
#include <iostream>
using namespace System::Exceptions;
void TestArgumentException()
{
	throw ArgumentException("arg error");
}

void TestArgumentNullException()
{
	throw ArgumentNullException("arg is nullptr");
}

void TestArgumentOutOfRangeException()
{
	throw ArgumentOutOfRangeException("arg out of range");
}

void TestArrayTypeMismatchException()
{
	throw ArrayTypeMismatchException("array type miss match");
}

void TestException()
{
	throw Exception("Exception");
}

void TestIndexOutOfRangeException()
{
	throw IndexOutOfRangeException("index out of range");
}

void TestInvalidOperationException()
{
	throw InvalidOperationException("invalid operation");
}

void TestIOException()
{
	throw IOException("io error");
}

void TestNotSupportedException()
{
	throw NotSupportedException(__func__);
}

void TestNullReferenceException()
{
	throw NullReferenceException("is nullptr");
}

void TestOverflowException()
{
	throw OverflowException("over flow");
}

void TestRedisException()
{
	throw RedisException("redis error");
}

void TestSocketException()
{
	throw SocketException("socket error");
}

void TestSqlException()
{
	throw SqlException("sql error");
}
int main(int argc, char** argv)
{
	try
	{
		TestArgumentException();
	}
	catch (ArgumentException &ex)
	{
		std::cout << ex.what() << std::endl;
	}

	try
	{
		TestArgumentNullException();
	}
	catch (ArgumentNullException &ex)
	{
		std::cout << ex.what() << std::endl;
	}

	try
	{
		TestArgumentOutOfRangeException();
	}
	catch (ArgumentOutOfRangeException &ex)
	{
		std::cout << ex.what() << std::endl;
	}

	try
	{
		TestArrayTypeMismatchException();
	}
	catch (ArrayTypeMismatchException &ex)
	{
		std::cout << ex.what() << std::endl;
	}
	
	try
	{
		TestIndexOutOfRangeException();
	}
	catch (IndexOutOfRangeException &ex)
	{
		std::cout << ex.what() << std::endl;
	}
	
	try
	{
		TestInvalidOperationException();
	}
	catch (InvalidOperationException &ex)
	{
		std::cout << ex.what() << std::endl;
	}
	
	try
	{
		TestIOException();
	}
	catch (IOException &ex)
	{
		std::cout << ex.what() << std::endl;
	}
	
	try
	{
		TestNotSupportedException();
	}
	catch (NotSupportedException &ex)
	{
		std::cout << ex.what() << std::endl;
	}
	
	try
	{
		TestNullReferenceException();
	}
	catch (NullReferenceException &ex)
	{
		std::cout << ex.what() << std::endl;
	}
	
	try
	{
		TestOverflowException();
	}
	catch (OverflowException &ex)
	{
		std::cout << ex.what() << std::endl;
	}
	
	try
	{
		TestRedisException();
	}
	catch (RedisException &ex)
	{
		std::cout << ex.what() << std::endl;
	}
	
	try
	{
		TestSocketException();
	}
	catch (SocketException &ex)
	{
		std::cout << ex.what() << std::endl;
	}
	
	try
	{
		TestSqlException();
	}
	catch (SqlException &ex)
	{
		std::cout << ex.what() << std::endl;
	}

	try
	{
		TestException();
	}
	catch (Exception &ex)
	{
		std::cout << ex.what() << std::endl;
	}

	getchar();
	return 1;
}