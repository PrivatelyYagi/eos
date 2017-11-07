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

  int pipefd[2];
  if (pipe(pipefd) < 0) {
    perror("pipe");
    exit(-1);
  }

  pid_t pid = fork();

  if (pid < 0) {

    perror("fork");
    exit(-1);

  } else if (pid == 0) { // 子プロセス

    close(pipefd[1]); //書き込みをクローズ
    int buf;
    read(pipefd[0], buf, sizeof buf);
    printf("child=[%d]\n", buf);
    close(pipefd[0]);

    return 0;

  } else {
    // 親プロセス
    close(pipefd[0]); //読み込みをクローズ
    int *s = 1;
    write(pipefd[1], s, 1);
    close(pipefd[1]);
    return 0;
  }

}