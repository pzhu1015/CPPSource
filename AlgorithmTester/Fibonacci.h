///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef ALGORITHMTESTER_FIBONACCI_H
#define ALGORITHMTESTER_FIBONACCI_H

//Find the nth term of fiboracci series
int GetFibonacdci_1(int n)
{
	if (1 == n || 2 == n)
	{
		return 1;
	}

	if (3 == n)
	{
		return 2;
	}
	int a = 2;
	int b = 3;
	int c = 5;
	for (int i = 0; i < n - 4; ++i)
	{
		c = a + b;
		a = b;
		b = c;
	}
	return c;
}

//Recursively finding the nth term of fibolacci sequence
int GetFibonacdci_2(int n)
{
	if (1 == n || 2 == n)
	{
		return 1;
	}
	return GetFibonacdci_2(n - 1) + GetFibonacdci_2(n - 2);
}

#endif // !ALGORITHMTESTER_FIBONACCIL_H
