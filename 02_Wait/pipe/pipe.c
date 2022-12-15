#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>

int main (void)
{
	pid_t pid;
	int fd[2], ret;
	printf("pbzpbz11\n");
	//char buf[1024] = {0};
	char buf[1024];
	ret = pipe(fd);
	if (-1 == ret)
	{
		perror("fork error");
		exit(1);
	}

	
	pid = fork();
	if (-1 == pid)
	{
		perror("fork error");
		exit(1);
	}
	else if(0 == pid)
	{
		close(fd[1]);
		ret = read(fd[0], buf, sizeof(buf));
		write(STDOUT_FILENO, buf, ret);
	}
	else
	{
		close(fd[0]);
		scanf ("%s",buf);
		printf("fatcher22 strlen:%lu\n", strlen(buf));
		write(fd[1], buf, sizeof(buf));
	}
}

