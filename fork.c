#include <stdio.h>
#include <unistd.h>

int main (void)
{
	pid_t pid;
	printf("pbzpbz11\n");

	pid = fork();
	if (-1 == pid)
	{
		perror("fork error");
	}
	else if(0 == pid)
	{
		printf("I'm son. pid:%d, father pid:%d\n", getpid(), getppid());
	}
	else
	{
		printf("I'm father. pid:%d, father pid:%d\n", getpid(), getppid());
		sleep(1);
	}
	
	printf("pbzpbz22 pid:%d\n", getpid());
}