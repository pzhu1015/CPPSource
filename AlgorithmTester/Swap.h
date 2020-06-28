///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef ALGORITHMTESTER_SWAP_H
#define ALGORITHMTESTER_SWAP_H

void SwapA(int &A, int &B)
{
	if (A == B)
	{
		return;
	}

	A = A + B;
	B = A - B;
	A = A - B;
}

void SwapB(unsigned int &A, unsigned int &B)
{
	if (A == B)
	{
		return;
	}

	A = A ^ B;
	B = A ^ B;
	A = A ^ B;
}

#endif // !ALGORITHMTESTER_SWAP_H
