#include <stdio.h>
#include <stdlib.h>
#define SIZE 512

void stdinCheckBuffer()
{
	printf("stdin is ");
	if(stdin->_flags & _IO_UNBUFFERED)
	{
		printf("unbuffered\n");
	}else if(stdin->_flags & _IO_LINE_BUF){
		printf("line-buffered\n");
	}else{
		printf("fully-buffered\n");
	}
	
	printf("buffer size is %d\n", stdin->_IO_buf_end - stdin->_IO_buf_base);

	printf("file discriptor is %d\n", fileno(stdin));
}

int main(int argc, char *argv[])
{
	char buf[SIZE];
	if(setvbuf(stdin, buf, _IONBF, NULL) != 0)
	{
		perror("set stdin for no buffer error!\n");
		exit(1);	
	}

	printf("Set stdin for no buffer successful!\n");

	stdinCheckBuffer();

	if(setvbuf(stdin, buf, _IOLBF, SIZE) != 0)
	{
		perror("set stdin for line buffer error!\n");
		exit(1);	
	}
	printf("Set stdin for line buffer successful!\n");

	stdinCheckBuffer();

	if(setvbuf(stdin, buf, _IOFBF, BUFSIZ) != 0)
	{
		perror("set stdin for full buffer error!\n");
		exit(1);	
	}
	printf("Set stdin for full buffer successful!\n");

	stdinCheckBuffer();

	return 0;
}

