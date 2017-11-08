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

#define TIMEOUT_MS (0)
#define INBUF_SIZE (80)
#define PFD_SIZE (1)

int turnLed(int currentGpio,int time);

int main(void){

  int fdgpio2,fdgpio3,fdgpio4,fdgpio5;
  int pret, len, count;
  char inbuf[INBUF_SIZE];
  struct timespec ts;
  struct timespec offTs;
  struct pollfd pfd[PFD_SIZE];

  ts.tv_sec = 0;
  ts.tv_nsec = 10000000; // 10ms
  offTs.tv_sec = 0;
  offTs.tv_nsec = 10000000; // 10ms
  count = 0;


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

    pret = poll(pfd, PFD_SIZE, TIMEOUT_MS);
    usleep(300);

    if(pret==0){
      write(fdgpio2, "0", 1);
      write(fdgpio3, "0", 1);
      write(fdgpio4, "0", 1);
      switch(count){
        case 0:
          offTs.tv_nsec = 2500000;
          write(fdgpio2, "1", 1);
          nanosleep(&ts,NULL);
          write(fdgpio2, "0", 1);
          nanosleep(&offTs,NULL);
          break;

        case 1:
          offTs.tv_nsec = 1500000;
          write(fdgpio2, "1", 1);
          nanosleep(&ts,NULL);
          write(fdgpio2, "0", 1);
          nanosleep(&offTs,NULL);
          break;

        case 2:
          offTs.tv_nsec = 0;
          write(fdgpio2, "1", 1);
          nanosleep(&ts,NULL);
          write(fdgpio2, "0", 1);
          nanosleep(&offTs,NULL);
          break;

        case 3:
          offTs.tv_nsec = 1000000;
          write(fdgpio3, "1", 1);
          nanosleep(&ts,NULL);
          write(fdgpio3, "0", 1);
          nanosleep(&offTs,NULL);
          break;

        case 4:
          offTs.tv_nsec = 300000;
          write(fdgpio3, "1", 1);
          nanosleep(&ts,NULL);
          write(fdgpio3, "0", 1);
          nanosleep(&offTs,NULL);
          break;

        case 5:
          offTs.tv_nsec = 0;
          write(fdgpio3, "1", 1);
          nanosleep(&ts,NULL);
          write(fdgpio3, "0", 1);
          nanosleep(&offTs,NULL);
          break;

        case 6:
          offTs.tv_nsec = 1000000;
          write(fdgpio4, "1", 1);
          nanosleep(&ts,NULL);
          write(fdgpio4, "0", 1);
          nanosleep(&offTs,NULL);
          break;

        case 7:
          offTs.tv_nsec = 300000;
          write(fdgpio4, "1", 1);
          nanosleep(&ts,NULL);
          write(fdgpio4, "0", 1);
          nanosleep(&offTs,NULL);
          break;

        case 8:
          offTs.tv_nsec = 0;
          write(fdgpio4, "1", 1);
          nanosleep(&ts,NULL);
          write(fdgpio4, "0", 1);
          nanosleep(&offTs,NULL);
          break;

        default:
          break;
      }
    }else{
      lseek(fdgpio5, 0, SEEK_SET);
      len = read(fdgpio5, inbuf, INBUF_SIZE);
      write(STDOUT_FILENO, inbuf, len);

      if(count > 8){
        count = 0;
      }else{
        count++;
      }

    }
  }
  return (EXIT_SUCCESS);
}
