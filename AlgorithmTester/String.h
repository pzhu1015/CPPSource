///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////

#ifndef ALGORITHMTESTER_STRING_H
#define ALGORITHMTESTER_STRING_H

#include <string>
#include <assert.h>

char* StrCpy(char* dest, const char* src)
{
	if (nullptr == dest || nullptr == src)
	{
		return nullptr;
	}

	if (dest == src)
	{
		return dest;
	}

	char* itr = dest;
	while ((*itr++ = *src++) != '\0');
	return dest;
}

char* StrCat(char* dest, const char* src)
{
	if (nullptr == dest || nullptr == src)
	{
		return nullptr;
	}

	char* itr = dest + strlen(dest);
	while ((*itr++ = *src++) != '\0');
	return dest;
}

char* Strncpy(char* dest, const char* src, int count)
{
	assert(nullptr != dest && nullptr != src);
	if (dest == src)
	{
		return dest;
	}
	if (count <= 0)
	{
		return dest;
	}
	char* start = dest;
	while ((count--) > 0 && (*start++ = *src++));
	*start = '\0';
	return dest;
}

int Atoi(const char* str)
{
	assert(nullptr != str);

	const int length = strlen(str);
	int value = 0;
	int times = 1;
	for (int i = length - 1; i >= 0; times *= 10)
	{
		value += (str[i] - '0') * times;
	}
	return value;
}

char* Itoa(char* dest, int value, int radix)
{
	assert(nullptr != dest);
	assert(radix > 1);
	const bool is_minu = value < 0;
	char buffer[16] = {};
	int count = 0;
	do
	{
		buffer[count++] = abs(value) % radix;
		value /= radix;
	} while (value);
	if (is_minu)
	{
		dest[0] = '-';
		for (int i = 0; i < count; ++i)
		{
			dest[i + 1] = '0' + buffer[count - i - 1];
		}
		dest[count + 1] = '\0';
	}
	else
	{
		for (int i = 0; i < count; ++i)
		{
			dest[i] = '0' + buffer[count - i - 1];
		}
		dest[count] = '\0';
	}
	return dest;
}

char* Reverse(char* dest)
{
	assert(nullptr != dest);
	const int length = strlen(dest);
	char t = 0;
	for (int i = 0; i < length / 2; ++i)
	{
		t = dest[i];
		dest[i] = dest[length - i - 1];
		dest[length - i - 1] = t;
	}
	return dest;
}

char* Upper(char* dest)
{
	assert(nullptr != dest);
	for (char* i = dest; *i != '\0'; ++i)
	{
		if (*i < 'a' || *i > 'z')
		{
			continue;
		}
		*i -= 'a' - 'A';
	}
	return dest;
}

void CountLetter(const char* src)
{
	int count[256] = {};
	for (; *src != '\0'; ++src)
	{
		const char &c = *src;
		if ((c < 'A' || c > 'z') || (c < 'a' || c > 'z'))
		{
			continue;
		}
		++count[c];
	}
}

#endif // !ALGORITHMTESTER_STRING_H
