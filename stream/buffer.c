#include <stdio.h>
#include <stdlib.h>
#if defined(MACOS)
#define _IO_UNBUFFERED __SNBF
#define _IO_LINE_BUF __SLBF
#define _IO_file_flags _flags
#define BUFFERSZ(fp) (fp)->_bf._size
#else
#define BUFFERSZ(fp) ((fp)->_IO_buf_end - (fp)->_IO_buf_base)
#endif

void pr_stdio(const char *, FILE *);

int main(int argc, char * argv[])
{
  FILE *fp;

  printf("pls enter some str\n");

  if(EOF == getchar())
    perror("getchar error");

  fputs("one line to standard error\n", stderr);

  pr_stdio("stdin", stdin);
  pr_stdio("stdout", stdout);
  pr_stdio("stderr", stderr);

  fp = fopen(argv[1], "a+b");

  if(NULL == fp)
    perror("fopen error");

  if(EOF == getc(fp))
    perror("getc error");

  pr_stdio(argv[1], fp);

  exit(0);
}


void pr_stdio(const char *name, FILE *fp)
{
  printf("stream = %s, ", name);

  if(fp->_IO_file_flags & _IO_UNBUFFERED )
    printf("unbuffered");
  else if(fp->_IO_file_flags & _IO_LINE_BUF)
    printf("line buffered");
  else
    printf("fully buffered");
 
  printf(", buffer size = %ld\n", BUFFERSZ(fp));
}
