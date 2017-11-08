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

#define TIMEOUT_MS (1) // 1ms
#define INBUF_SIZE (80)
#define PFD_SIZE (1)

int main(void){

  int fdgpio2,fdgpio3,fdgpio4,fdgpio5;
  int i, j, pret, count, offCount;
  char inbuf[INBUF_SIZE];
  struct timespec ts;
  struct pollfd pfd[PFD_SIZE];

  ts.tv_sec = 0;
  ts.tv_nsec = 1000000; // 1ms
  count = 0;
  offCount = 7;

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
  for(;;){

    pret=poll(pfd, PFD_SIZE, TIMEOUT_MS);

    if(pret==0){

    }else{
      lseek(fdgpio5, 0, SEEK_SET);
      printf("pushed!\n");

    }
  }

  system("bash end.sh 2 3 4 5");  // GPIOを開放

  return (EXIT_SUCCESS);
}
