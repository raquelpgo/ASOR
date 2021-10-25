#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <iostream>
using namespace std;

int main()
{
	if (setuid(0) == -1)
	{
		cout << "ERROR " << errno << " " << strerror(errno) << endl;
	}
	return 0;
}
