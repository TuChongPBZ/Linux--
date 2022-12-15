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
	STU student;
	STU *p_stu;

	if (arg < 2)
	{
		perror("arg error");
		exit(1);
	}
	/*1.打开文件*/
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("open error");
		exit(1);
	}
	/*2.将2文件映射出缓冲区，并给p_stu*/
	p_stu = mmap(NULL, sizeof(STU), PROT_READ, MAP_PRIVATE, fd, 0);
	if (MAP_FAILED == p_stu)
	{
		perror("mmap error");
		exit(1);
	}
	/*3.读内容	 */
	while (1)
	{
		printf("stu--- int:%d, name:%s, sex:%d\n", p_stu->num, p_stu->name, p_stu->sex);
		sleep(1);
	}

	/*4.释放缓冲区*/
	ret = munmap(p_stu, MMAP_LEN);
	if (ret < 0)
	{
		perror("mumpa error");
		exit(1);
	}

	close(fd);
}
