///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef ALGORITHMTESTER_RANDOM_H
#define ALGORITHMTESTER_RANDOM_H

#include <random>

//A random method for generating [N-M] interval numbers
int GetRandomRange(int n, int m)
{
	if (n == m)
	{
		return n;
	}
	if (n > m)
	{
		n = n + m;
		m = n - m;
		n = n - m;
	}
	return n + (rand() % (m - n + 1));
}

//Implement a random floating - point number between[0 ~1]
double GetRangeRange()
{
	return rand() / static_cast<double>(RAND_MAX);
}

#endif // !ALGORITHMTESTER_RANDOM_H
