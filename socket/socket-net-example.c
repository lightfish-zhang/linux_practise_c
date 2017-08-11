#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAXLINE 4096

int main(int argc, char **argv) {
  int listenfd, connfd;
  struct sockaddr_in servaddr;
  char buff[4096];
  int n;
  int pid;

  if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    printf("create socket error: %s(errno: %d)\n", strerror(errno), errno);
    exit(1);
  }

  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(6666);

  if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1) {
    printf("bind socket error: %s(errno: %d)\n", strerror(errno), errno);
    exit(1);
  }

  if (listen(listenfd, 10) == -1) {
    printf("listen socket error: %s(errno: %d)\n", strerror(errno), errno);
    exit(1);
  }

  printf("======waiting for client's request======\n");
  while (1) {
    if ((connfd = accept(listenfd, (struct sockaddr *)NULL, NULL)) == -1) {
      printf("accept socket error: %s(errno: %d)", strerror(errno), errno);
      continue;
    }
    // n = read(connfd, buff, MAXLINE, 0);
    // n = recv(connfd, buff, MAXLINE, 0);
    // buff[n] = '\0';
    // printf("recv msg from client: %s\n", buff);
    // close(connfd);

    if((pid = fork()) < 0){
      printf("fork error: %s(errno: %d)\n", strerror(errno), errno);
      exit(1);
    }
    if(0 == pid){
      pid = getpid();
      while(1){
        n = recv(connfd, buff, MAXLINE, 0);
        buff[n] = '\0';
        if(*buff == '0'){
          printf("work(pid=%d) close(%d) and exit(0) by client msg: %s\n", pid, connfd, buff);
          close(connfd);
          exit(0);
        }else{
          printf("recv msg from client: %s\n", buff);
        }
      }
    }else{
      printf("fork, pid is: %d\n", pid);
      close(connfd);
    }

  }

  close(listenfd);
}