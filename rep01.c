#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <poll.h>

#define GPIOPATH "/sys/class/gpio/"
#define GPIO2 GPIOPATH "gpio2/value"
#define GPIO3 GPIOPATH "gpio3/value"
#define GPIO4 GPIOPATH "gpio4/value"
#define GPIO5 GPIOPATH "gpio5/value"

#define TIMEOUT_MS (10) // 10ms
#define INBUF_SIZE (80)
#define PFD_SIZE (1)
void showPollRevents(int fd, short revents);

int main(void){

  int fdgpio2,fdgpio3,fdgpio4,fdgpio5;
  int i, pret, len;
  char inbuf[INBUF_SIZE];
  struct timespec ts_on;
  struct timespec ts_off;
  struct pollfd pfd[PFD_SIZE];

  ts_on.tv_sec = 0; //sec.
  ts_on.tv_nsec = 5000000; //nano sec. (5ms)

  ts_off.tv_sec = 0; //sec.
  ts_off.tv_nsec = 5000000; //nano sec. (5ms)

  system("bash all.sh 2 3 4 5"); // GPIOの設定

  fdgpio2 = open(GPIO2 , O_WRONLY | O_SYNC);
  if(fdgpio2 < 0){
    perror("cannot open " GPIO2 );
    exit(EXIT_FAILURE);
  }

  fdgpio3 = open(GPIO3 , O_WRONLY | O_SYNC);
  if(fdgpio3 < 0){
    perror("cannot open " GPIO3 );
    exit(EXIT_FAILURE);
  }

  fdgpio4 = open(GPIO4 , O_WRONLY | O_SYNC);
  if(fdgpio4 < 0){
    perror("cannot open " GPIO4 );
    exit(EXIT_FAILURE);
  }

  fdgpio5 = open(GPIO5, O_RDWR);
  if(fdgpio5 < 0){
    perror("cannot open " GPIO5 );
    exit(EXIT_FAILURE);
  }

  pfd[0].fd = fdgpio5;
  pfd[0].events = POLLPRI | POLLERR;

  write(STDOUT_FILENO, "waiting for interrupt...¥n", strlen("waiting for interrupt...¥n"));

  for(;;){
    pret=poll(pfd, PFD_SIZE, TIMEOUT_MS);
    showPollRevents(STDOUT_FILENO, pfd[0].revents);
      write(fdgpio2, "1", 1);
      nanosleep(&ts_on,NULL);
    if(pret==0){
      write(fdgpio2, "0", 1);
    }else{
      write(STDOUT_FILENO, "sw¥n", strlen("sw¥n"));
      lseek(fdgpio5, 0, SEEK_SET);
      len=read(fdgpio5, inbuf, INBUF_SIZE);
      write(STDOUT_FILENO, inbuf, len);
      ts_on.tv_nsec = 100000000; //nano sec.
    }
  }

  system("bash end.sh 2 3 4 5");  // GPIOを開放

  return (EXIT_SUCCESS);
}

void showPollRevents(int fd, short revents) {
  if(revents & POLLIN){
    write(fd, "POLLIN¥n", strlen("POLLIN¥n"));
  }
  if(revents & POLLPRI){
    write(fd, "POLLPRI¥n", strlen("POLLPRI¥n"));
  }
  if(revents & POLLOUT){
    write(fd, "POLLOUT¥n", strlen("POLLOUT¥n"));
  }
  if(revents & POLLERR){
    write(fd, "POLLERR¥n", strlen("POLLERR¥n"));
  }
  if(revents & POLLHUP){
    write(fd, "POLLHUP¥n", strlen("POLLHUP¥n"));
  }
  if(revents & POLLNVAL){
    write(fd, "POLLNVAL¥n", strlen("POLLNVAL¥n"));
  }
}
