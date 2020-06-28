///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef ALGORITHMTESTER_SEARCH_H
#define ALGORITHMTESTER_SEARCH_H

#include <assert.h>

int BinarySearch(int *array, int count, int value)
{
	assert(nullptr != array);
	int left = 0;
	int right = count - 1;
	int mid = 0;
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (value < array[mid])
		{
			right = mid - 1;
		}
		else if (value > array[mid])
		{
			left = mid + 1;
		}
		else
		{
			return mid;
		}
	}
	return -1;
}

int FindSec(int *p, int length)
{
	assert(nullptr != p);
	int maxv = p[0];
	int secv = p[0];
	for (int i = 1; i < length; ++i)
	{
		if (maxv < p[i])
		{
			secv = maxv;
			maxv = p[i];
		}
	}
	return secv;
}

#endif // !ALGORITHMTESTER_SEARCH_H
