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
int main(void)
{
	int ret;
	char *p = NULL;
	char *tmp;
	char buf[32] = "pbzpbz0\n"; 
	/*1.打开文件*/
	int fd = open("pbz", O_RDWR|O_CREAT|O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open error");
		exit(1);
	}
	
	/*2.扩展文件内容*/
	ret = ftruncate(fd, MMAP_LEN);
	if (ret < 0)
	{
		perror("ftruncate error");
		exit(1);
	}
	
	/*3.将2文件映射出缓冲区，并给p*/
	p = mmap(NULL, MMAP_LEN, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	tmp = p;
	if (MAP_FAILED == p)
	{
		perror("mmap error");
		exit(1);
	}
	for (int i=0; i < MMAP_LEN; i++)
	{
		printf("I'm i:%d\n",i);
		/*4.写入内容*/
		strncpy(tmp, buf, strlen(buf));
		//tmp[strlen(buf) - 2] = i+48;
		tmp += strlen(buf);
		usleep(1000 * 50);
	}

	/*5.释放缓冲区*/
	ret = munmap(p, 4);
	if (ret < 0)
	{
		perror("mumpa error");
		exit(1);
	}
	close(fd);
}
