#include <sys/types.h>
#include <sys/wait.h>
#include <sys/times.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

static void pr_times(clock_t, struct tms * , struct tms *);
static void do_cmd(char *);
void pr_exit(int status);

int main(int argc, char * argv[])
{
	int i;

	setbuf(stdout, NULL);
	for(i = 1; i<argc; i++)
	{
		do_cmd(argv[i]);
	}
	exit(0);
}


static void do_cmd(char * cmd)
{
	struct tms tmsstart, tmsend;
	clock_t start, end;
	int status;

	printf("\ncomamd:%s\n", cmd);

	if( (start = times(&tmsstart)) == -1 )
	{
		perror("times error");
	}
	if( (status = system(cmd)) < 0 )
	{
		perror("system() error");
	}
	if( (end = times(&tmsend)) == -1 )
	{
		perror("times error");
	}

	pr_times(end - start, &tmsstart, &tmsend);
	pr_exit(status);
}


void pr_exit(int status)
{
	if(WIFEXITED(status))
		printf("normal termination, exit status = %d\n",
				WEXITSTATUS(status));
	else if(WIFSIGNALED(status))
		printf("abnormal termination, signal number = %d%s\n",
				WTERMSIG(status),
#ifdef WCOREDUMP
				WCOREDUMP(status) ? "(core file generate)" : "");
#else
				"");
#endif
	else if(WIFSTOPPED(status))
		printf("child stopped, signal number = %d\n",
				WSTOPSIG(status));
}


static void pr_times(clock_t real, struct tms * tmsstart, struct tms * tmsend)
{
	static long clktck = 0;

	if( 0 == clktck && (clktck = sysconf(_SC_CLK_TCK)) < 0 )
		perror("sysconf error");

	printf("  real: %7.2f\n", real / (double)clktck);
	printf("  user: %7.2f\n", (tmsend->tms_utime - tmsstart->tms_utime) / (double)clktck);
	printf("  sys: %7.2f\n", (tmsend->tms_stime - tmsstart->tms_stime) / (double)clktck);
	printf("  child user: %7.2f\n", (tmsend->tms_cutime - tmsstart->tms_cutime) / (double)clktck);
	printf("  child sys: %7.2f\n", (tmsend->tms_cstime - tmsstart->tms_cstime) / (double)clktck);

}
