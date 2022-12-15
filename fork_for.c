#include <stdio.h>
#include <unistd.h>

int main (void)
{
	int i;
	pid_t pid;
	printf("pbzpbz11\n");
	for(i = 0; i<5; i++)
	{
		pid = fork();
		if (-1 == pid)
		{
			perror("fork error");
		}
		else if(0 == pid)
		{
			printf("I'm son. pid:%d, father pid:%d\n", getpid(), getppid());
			break;
		}
		else
		{
			printf("I'm father. pid:%d, father pid:%d\n", getpid(), getppid());
			sleep(1);
		}
	}
	//sleep(i);
	printf("pbzpbz22 pid:%d, i:%d\n", getpid(), i);
}