///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;

int fun(int a)
{
	int num = 0;
	while (a) {
		a &= (a - 1);
		num++;
	}
	return num;
}

int main(int args, char** argv)
{
	int a = fun(21);
	cout << a << endl;
	system("pause");
	return 1;
}