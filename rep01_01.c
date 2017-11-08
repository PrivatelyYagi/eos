#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<fcntl.h>

#define GPIOPATH "/sys/class/gpio/"
#define GPIO2 GPIOPATH "gpio2/value"
#define GPIO3 GPIOPATH "gpio3/value"
#define GPIO4 GPIOPATH "gpio4/value"
#define GPIO5 GPIOPATH "gpio5/value"

int main(void){

  int fdgpio2,fdgpio3,fdgpio4,fdgpio5;
  struct timespec ts;
  int i;

  ts.tv_sec = 0; //sec.
  ts.tv_nsec = 500000000; //nano sec. (500ms)

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

  fdgpio5 = open(GPIO5 , O_WRONLY | O_SYNC);
  if(fdgpio5 < 0){
    perror("cannot open " GPIO5 );
    exit(EXIT_FAILURE);
  }


}