#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>

int main (void)
{
	pid_t pid, wpid;
	int stats;
	printf("pbzpbz11\n");
	int a=10;
	pid =fork();
	if (-1 == pid)
	{
		perror("fork error");
	}
	else if(0 == pid)
	{
		
		printf("I'm son. pid:%d, father pid:%d\n", getpid(), getppid());
		//printf("a:%s\n", a);
		a = a / 0;
		sleep(60);
		printf("son end\n");
		return 50;
		//exit(10);
	}
	else
	{
		wpid = wait(&stats);
		if (-1 == wpid)
		{
			perror("fork error");
			exit(1);
		}
		if(WIFEXITED(stats))
		{
			printf("son. exit:%d\n", WEXITSTATUS(stats));
		}
		if (WIFSIGNALED(stats))
		{
			printf("son. sig:%d\n", WTERMSIG(stats));
		}
		while (1)
		{
			printf("I'm fatcher. pid:%d, father pid:%d\n", getpid(), getppid());
			sleep(1);
		}
	}
}
