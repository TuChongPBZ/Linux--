#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/time.h>
/*
 	int getitimer(int which, struct itimerval *curr_value);
	int setitimer(int which, const struct itimerval *new_value,	struct itimerval *old_value);
 	struct itimerval {
				struct timeval it_interval;  Interval for periodic timer 
				struct timeval it_value;	 Time until next expiration };
	struct timeval {
				time_t		tv_sec; 		 seconds 
				suseconds_t tv_usec;		 microseconds };
 */
void sys_error(const char *str)
{
	printf("%s error\n", str);
	exit(-1);
}
#define M_SLEEP100 1000*100
#define CHILE_NUM 5

long my_alarm(long sec)
{
	int ret = 0;
	struct itimerval new_time, ole_time;

	new_time.it_value.tv_sec = sec; //设置定时时长
	new_time.it_value.tv_usec = 0;

	new_time.it_interval.tv_sec = 0; //周期0 ，表示没有循环
	new_time.it_interval.tv_usec = 0;

	ret = setitimer(ITIMER_REAL, &new_time, &ole_time);
		if(ret < 0)
			sys_error("setitimer");
		printf("ole_time:%ld\n", ole_time.it_value.tv_sec);
	return ole_time.it_interval.tv_sec;
}

void hello(int a)
{
	printf("-%s-\n", "hhhhhhh");
}
int main(void)
{
	int i = 0;
	int ret = 0;
#if 1 // 

	signal(SIGALRM, hello);				//信号捕捉函数

	struct itimerval new_time, ole_time;

	new_time.it_value.tv_sec = 3; 		//设置第一次定时时长
	new_time.it_value.tv_usec = 0;

	new_time.it_interval.tv_sec = 1; 	//周期1 信号间隔时间
	new_time.it_interval.tv_usec = 0;

	ret = setitimer(ITIMER_REAL, &new_time, &ole_time);
		if(ret < 0)
			sys_error("setitimer");
	printf("ole_time:%ld, next:%ld\n", ole_time.it_value.tv_sec, ole_time.it_interval.tv_sec);
	//sleep(1);
	while(1);
#else
	my_alarm(1);

	for(i = 0;; i++)
	{
		printf("%d\n", i);
	}
#endif
}
