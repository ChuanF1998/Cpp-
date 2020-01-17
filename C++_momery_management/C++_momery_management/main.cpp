#if 0

#include <malloc.h>
#include <stdio.h>

int main()
{
	int *ptr = NULL;
	ptr = (int*)realloc(ptr, sizeof(int)*4);
	ptr[0] = 0;
	ptr[1] = 1;
	ptr[2] = 2;
	ptr[3] = 3;;
	int k = sizeof(ptr);
	return 0;
}

#endif

#include <iostream>
using namespace std;

int main()
{
	int* k = new int(8);
	cout << *k << endl;
	delete k;
	return 0;
}