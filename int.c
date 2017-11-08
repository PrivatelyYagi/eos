#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

#define GPIOPATH "/sys/class/gpio/"
#define GPIO2 GPIOPATH "gpio2/value"
#define GPIO3 GPIOPATH "gpio3/value"
#define GPIO4 GPIOPATH "gpio4/value"
#define GPIO5 GPIOPATH "gpio5/value"

int main(void){

  struct timespec ts;
  int pipefd[2];
  int num;
  if (pipe(pipefd) < 0) {
    perror("pipe");
    exit(-1);
  }
  ts.tv_sec = 0;
  ts.tv_nsec = 100000000;

  pid_t pid = fork();

  if (pid < 0) {

    perror("fork");
    exit(-1);

  } else if (pid == 0) { // 子プロセス

    close(pipefd[1]); //書き込みをクローズ
    char buf[256];
//
    while(1){
    read(pipefd[0], buf, sizeof buf);
    printf("buf : %s\n",buf );
      switch(num){
          case '1':
            printf("1¥n");
            break;

          case '2':
            printf("2¥n");
            break;

          case '3':
            printf("3¥n");
            break;

          case '4':
            printf("4¥n");
            break;

          default:
            break;
      }
    }
    close(pipefd[0]);
    return 0;

  } else {
    // 親プロセス
    close(pipefd[0]); //読み込みをクローズ
    char *s = "1";
/*
    while(1){
      write(pipefd[1], s, 1);
      nanosleep(&ts,NULL);
      write(pipefd[1], s, 1);
      nanosleep(&ts,NULL);
      write(pipefd[1], s, 1);
      nanosleep(&ts,NULL);
    }
*/
    write(pipefd[1], s, 1);
    close(pipefd[1]);
    return 0;
  }
}

