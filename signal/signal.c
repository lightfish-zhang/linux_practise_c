#include <signal.h>
#include <stdio.h>

void signalDeal(int iSignNum)
{
	printf("The signal NO. is:%d\n", iSignNum);
	return;
}

int main(void)
{
	signal(SIGINT, signalDeal);
	while(1){
		sleep(1);
	}
	return 0;
}
