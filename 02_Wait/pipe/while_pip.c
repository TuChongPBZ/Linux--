#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
/*单次操作
 * 子写，父读
 * pipefd[0] 读端口
 * pipefd[1] 写端口
 * */
int main (void)
{
	int ret;		//接受子进程pid
	int pipefd[2];		//无名管道变量
	int pipefd2[2];		//无名管道变量
	char tbuf[20]={0};	//发送缓冲区
	char rbuf[20]={0};	//接收缓冲区
	pipe (pipefd);		//创建管道
	pipe (pipefd2);
	ret = fork();		//创建子进程
	if (ret == 0)		//child
	{
		while(1)
		{
			//写管道1
			printf("child write\n");
			scanf ("%s",tbuf);
			write (pipefd[1],tbuf,sizeof(tbuf));//child 
			//读管道2
			memset(rbuf,0,sizeof(rbuf));
			read (pipefd2[0],rbuf,sizeof(rbuf));//parent read 阻塞
			printf("rbuf = %s\n",rbuf);
			if (strncmp(rbuf,"QUIT",4) == 0)
			{
				printf("child EDN");
				break;
			}
		}
	}
	else			//parent
	{	
		while(1)
		{
			//读管道1
			printf("father read\n");
			memset(rbuf,0,sizeof(rbuf));
			read (pipefd[0],rbuf,sizeof(rbuf));//parent read 阻塞
			printf("rbuf = %s\n",rbuf);
			if (strncmp(rbuf,"QUIT",4) == 0)
			{
				printf("parent EDN");
				break;
			}
			//写管道2
			printf("parent write\n");
			scanf ("%s",tbuf);
			write (pipefd2[1],tbuf,sizeof(tbuf));//child 
		}
		wait(NULL);
	}
	exit(0);
}
