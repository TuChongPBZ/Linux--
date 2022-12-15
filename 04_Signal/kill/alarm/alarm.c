#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/mman.h>
void sys_error(const char *str)
{
	printf("%s error\n", str);
	exit(-1);
}
#define M_SLEEP100 1000*100
#define CHILE_NUM 5
int main(void)
{
	int i = 0;
	alarm(1);
	for(i = 0;; i++)
	{
		printf("%d\n", i);
	}
}
