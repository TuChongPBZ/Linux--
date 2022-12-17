#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <signal.h>

void sys_error(const char *str)
{
	printf("%s error\n", str);
	exit(-1);
}
void pending(sigset_t *ped)
{
	int i;
	for(i = 1; i < 64; i++)
	{
		if (sigismember(ped, i))	//5.判断信号是否在信号集中
		{
			printf("%c",'1');
		}else
		{
			printf("%c", '0');
		}
	}
	printf("%c",'\n');
}

#define M_SLEEP100 1000*100
#define CHILE_NUM 5
#if 0 //注释
/*
 1) SIGHUP	 2) SIGINT	 3) SIGQUIT	 4) SIGILL	 5) SIGTRAP
 6) SIGABRT	 7) SIGBUS	 8) SIGFPE	 9) SIGKILL	10) SIGUSR1
11) SIGSEGV	12) SIGUSR2	13) SIGPIPE	14) SIGALRM	15) SIGTERM
16) SIGSTKFLT	17) SIGCHLD	18) SIGCONT	19) SIGSTOP	20) SIGTSTP
21) SIGTTIN	22) SIGTTOU	23) SIGURG	24) SIGXCPU	25) SIGXFSZ
26) SIGVTALRM	27) SIGPROF	28) SIGWINCH	29) SIGIO	30) SIGPWR
31) SIGSYS	34) SIGRTMIN	35) SIGRTMIN+1	36) SIGRTMIN+2	37) SIGRTMIN+3
38) SIGRTMIN+4	39) SIGRTMIN+5	40) SIGRTMIN+6	41) SIGRTMIN+7	42) SIGRTMIN+8
43) SIGRTMIN+9	44) SIGRTMIN+10	45) SIGRTMIN+11	46) SIGRTMIN+12	47) SIGRTMIN+13
48) SIGRTMIN+14	49) SIGRTMIN+15	50) SIGRTMAX-14	51) SIGRTMAX-13	52) SIGRTMAX-12
53) SIGRTMAX-11	54) SIGRTMAX-10	55) SIGRTMAX-9	56) SIGRTMAX-8	57) SIGRTMAX-7
58) SIGRTMAX-6	59) SIGRTMAX-5	60) SIGRTMAX-4	61) SIGRTMAX-3	62) SIGRTMAX-2
63) SIGRTMAX-1	64) SIGRTMAX	

#include <signal.h>
typedef void (*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler);

int sigaction(int signum, const struct sigaction *act,
					struct sigaction *oldact);
struct sigaction {
	void     (*sa_handler)(int);
	void     (*sa_sigaction)(int, siginfo_t *, void *);
	sigset_t   sa_mask;
	int        sa_flags;
	void     (*sa_restorer)(void);
};
*/
#endif
typedef void (*sighandler_t)(int);
void my_sigaction(int temp_sit)
{
	sigset_t ped;
	printf("my_sigaction:%d\n", temp_sit);
	sleep(1);
	sigpending(&ped);		//4.读取未决信号集
	pending(&ped);
	printf("my_sigaction end\n");
}
int main(void)
{
	int ret;
	struct sigaction sig, old_sig;

	sig.sa_handler = my_sigaction;				//信号处理函数
	sigemptyset(&sig.sa_mask);
	sigaddset(&sig.sa_mask, SIGTSTP);			//sa_mask信号集设置
	sig.sa_flags = 0;
	ret = sigaction(SIGINT, &sig, &old_sig);	//注册信号捕捉
	if(ret < 0)
		sys_error("sigaction");
	while(1);
	
}
