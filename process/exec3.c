/*
 * when watchfile changed, backup
 */
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char * argv[])
{
	int fd;
	int stat,pid;
	struct stat stbuf;
	time_t old_time = 0;

	if(3 != argc){
		fprintf(stderr, "usage: %s watchfile copyfile \n", argv[0]);
		return 1;
	}

	if((fd = open(argv[1], O_RDONLY)) == -1){
		fprintf(stderr, "Watchfile: %s can't open \n", argv[1]);
		return 2;
	}

	fstat(fd, &stbuf);
	old_time = stbuf.st_mtime;

	while(1)
	{
		fstat(fd, &stbuf);
		if(old_time != stbuf.st_mtime)
		{
			while((pid = fork()) == -1);

			if(0 == pid)
			{
				execl("/bin/cp", "/bin/cp", argv[1], argv[2], (char *)0);
				return 3;
			}

			wait(&stat);
			old_time = stbuf.st_mtime;
		}else{
			sleep(1);
		}
	}

	return 0;
}
