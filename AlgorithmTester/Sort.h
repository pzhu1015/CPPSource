///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef ALGORITHMTESTER_SORT_H
#define ALGORITHMTESTER_SORT_H
#include <assert.h>

void Quicksort(int *a, int low, int high)
{
	if (low>high)
	{
		return;
	}
	int i = low;
	int j = high;
	int key = a[i];
	while (i<j)
	{
		while (i<j&&a[j] >= key)
		{
			j--;
		}
		a[i] = a[j];
		while (i<j&&a[i] <= key)
		{
			i++;
		}
		a[j] = a[i];
	}
	a[i] = key;
	Quicksort(a, low, i - 1);
	Quicksort(a, i + 1, high);
}

void SelectSort(int* array, int count)
{
	for (int i = 0; i < count; ++i)
	{
		int min_value = array[i];
		int min_index = i;
		for (int j = i + 1; j < count; ++j)
		{
			if (array[j] < min_value)
			{
				min_value = array[j];
				min_index = j;
			}
		}
		const int temp = array[i];
		array[i] = min_value;
		array[min_index] = temp;
	}
}

void BubleSort(int* array, int count)
{
	for (int i = 0; i < count; ++i)
	{
		for (int j = 0; j < count - i - 1; ++j)
		{
			if (array[j] > array[j + 1])
			{
				const int temp = array[j + 1];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}
	}
}

void MergeSort(int* merge, int *p1, int len1, int* p2, int len2)
{
	assert(nullptr != merge && nullptr != p1 && nullptr != p2);
	int i = 0;
	int j = 0;
	int k = 0;
	while (i < len1 && j < len2)
	{
		if (p1[i] < p2[j])
		{
			merge[k] = p1[i];
			++k;
			++i;
		}
		else
		{
			merge[k] = p2[j];
			++k;
			++j;
		}
	}
	while (i < len1)
	{
		merge[k] = p1[i];
		++k;
		++i;
	}
	while (j < len2)
	{
		merge[k] = p2[j];
		++k;
		++j;
	}
}


#endif // !ALGORITHMTESTER_SORT_H
