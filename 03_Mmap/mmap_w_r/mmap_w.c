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
typedef struct
{
	int		num;
	char	name[32];
	int		sex;
}STU;

int main(int arg, char *argv[])
{
	int ret;
	int fd;
	STU student = {10, "pbz", 26};
	STU *p_stu;

	if (arg < 2)
	{
		perror("arg error");
		exit(1);
	}
	/*1.打开文件*/
	fd = open("pbz", O_RDWR|O_CREAT|O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open error");
		exit(1);
	}
	/*2.扩展文件内容*/
	ret = ftruncate(fd, sizeof(STU));
	if (ret < 0)
	{
		perror("ftruncate error");
		exit(1);
	}
	
	/*3.将2文件映射出缓冲区，并给p*/
	p_stu = mmap(NULL, sizeof(STU), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if (MAP_FAILED == p_stu)
	{
		perror("mmap error");
		exit(1);
	}
	
	while (1)
	{
		student.num++;
		memcpy(p_stu, &student, sizeof(STU));
		sleep(1);
	}
	/*5.释放缓冲区*/
	ret = munmap(p_stu, sizeof(STU));
	if (ret < 0)
	{
		perror("mumpa error");
		exit(1);
	}
	close(fd);
}
