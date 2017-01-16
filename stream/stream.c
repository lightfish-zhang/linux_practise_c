#include <stdio.h>

int main(int argc, char *argv[])
{
  FILE *fp;
  int iflag;

  if(argc <= 1)
  {
    printf("useage: %s filename\n", argv[0]);
    return 1;
  }

  fp = fopen(argv[1], "a+b");

  if(NULL == fp)
  {
    printf("Open file %s failed!", argv[1]);
    return 2;
  }

  printf("Open file %s succeed!\n", argv[1]);
  iflag = fclose(fp);

  if(0 == iflag)
  {
    printf("Close file %s succeed!\n", argv[1]);
    return 0;
  }else{
    printf("Close file %s failed!", argv[1]);
    return 3;
  }
}
