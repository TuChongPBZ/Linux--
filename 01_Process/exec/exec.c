#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main (void)
{
	int fd_ls, fd_hello;
	pid_t pid;
	printf("pbzpbz11\n");
	fd_ls = open("ls.txt", O_WRONLY|O_CREAT, 0666);
	lseek(fd_ls, 0, SEEK_END);
	fd_hello = open("hello.txt", O_WRONLY|O_CREAT, 0666);
	lseek(fd_hello, 0, SEEK_END);
	pid = fork();
	if (-1 == pid)
	{
		perror("fork error");
	}
	else if(0 == pid)
	{
		dup2(fd_ls, STDOUT_FILENO);
		printf("I'm son. pid:%d, father pid:%d\n", getpid(), getppid());
		execlp("ls", "ls", "-l", "-a", NULL);
		printf("son end\n");
	}
	else
	{
		sleep(1);
		dup2(fd_hello, STDOUT_FILENO);
		printf("I'm father. pid:%d, father pid:%d\n", getpid(), getppid());
		execl("/home/samba/work/11-Linux系统编程/01_Process/exec/hello", "hello"    , NULL);
		printf("father end\n");
	}
}
