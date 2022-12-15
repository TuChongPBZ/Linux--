#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#define M_SLEEP100 1000*100

int main (void)
{
	int i, n = 5;
	pid_t pid, wpid;
	int stats;
	printf("pbzpbz11\n");
	for(i = 0; i < n; i++)
	{
		pid = fork();
		if (-1 == pid)
		{
			perror("fork error");
		}
		else if(0 == pid)
		{
			break;
		}		
	}
	if (n == i)//循环到5表示父进程for结束
	{
		//usleep(i * M_SLEEP100);
		printf("I'm fatcher[%d]. pid:%d, father pid:%d\n",i ,getpid(), getppid());
		while(waitpid(-1, NULL, WNOHANG) >= 0)
		{
			usleep(5 * M_SLEEP100);
		};	
		printf("End fatcher\n");
	}else{
		usleep(i * M_SLEEP100);
		printf("I'm son[%d]. pid:%d, father pid:%d\n",i ,getpid(), getppid());
	}
}
