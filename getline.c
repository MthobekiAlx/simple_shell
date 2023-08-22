#include <stdio.h>
#include <stdlib.h>

/*
 * main getline function
 * return 0 on success
*/

int main(void)
{
	size_t n = 10;
	char *buf = NULL;

	getline(&buf, &n, stdin);

	return 0;
}

