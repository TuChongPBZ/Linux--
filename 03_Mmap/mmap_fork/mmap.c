#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/mman.h>
/*O_RDONLY 只读模式
O_WRONLY 只写模式
O_RDWR 读写模式*/
#define MMAP_LEN 1024
int var = 100;
int main(void)
{
	int ret;
	pid_t pid;
	char *p = NULL;
	char buf[32] = "pbzpbz mmap-fork"; 
	/*1.打开文件*/
	int fd = open("pbz", O_RDWR|O_CREAT|O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open error");
		exit(1);
	}
	//unlink("pbz");
	/*2.扩展文件内容*/
	ret = ftruncate(fd, MMAP_LEN);
	if (ret < 0)
	{
		perror("ftruncate error");
		exit(1);
	}
	
	/*3.将2文件映射出缓冲区，并给p*/
	//p = mmap(NULL, MMAP_LEN, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	p = mmap(NULL, MMAP_LEN, PROT_READ|PROT_WRITE, MAP_PRIVATE, fd, 0);
	if (MAP_FAILED == p)
	{
		perror("mmap error");
		exit(1);
	}
	
	pid = fork();
	if (pid < 0)
	{
		perror("fork error");
		exit(1);
	}
	else if (0 == pid)
	{
		printf("I'm child. pid:%d, father pid:%d\n",getpid(), getppid());
		/*4.写入内容
		 * 共享内存和全局变量中写入内容
		 */
		strncpy(p, buf, strlen(buf) + 1);
		var = 1000;
		printf("I'm child. p:%s, var:%d\n",p ,var);
	}
	else
	{
		/* 读内容	 */
		sleep(1);
		printf("I'm fatcher. p:%s, var:%d\n",p ,var);
		wait(NULL);
		/*5.释放缓冲区*/
		ret = munmap(p, MMAP_LEN);
		if (ret < 0)
		{
			perror("mumpa error");
			exit(1);
		}
	}
	close(fd);
}
