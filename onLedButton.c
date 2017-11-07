#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define GPIO_PAHT "/sys/class/gpio/"
#define GPIO5 GPIO_PAHT "gpio5/value"
#define GPIO5_DIRECTION GPIO_PAHT "gpio5/direction"
#define GPIO5_EDGE GPIO_PAHT "GPIO5/edge"
#define INBUF_SIZE 256
#define GPIOPATH "/sys/class/gpio/"
#define GPIO2 GPIOPATH "gpio2/value"

int main(void){
  FILE *fp;
  int fdgpio2;
  char inbuf[INBUF_SIZE];

  fp= fopen(GPIO5, "r");
  if(fp==NULL){
    perror("fopen error:");
    return 1;
  }
  fdgpio2 = open(GPIO2 , O_WRONLY | O_SYNC);
  if(fdgpio2 < 0){
    perror("cannot open " GPIO2 );
    exit(EXIT_FAILURE);
  }
for(;;){
  fseek(fp, 0L, SEEK_SET);
  fgets(inbuf, INBUF_SIZE, fp);
  fflush(fp);
  if(strcmp(inbuf,"0¥n")==0){
    printf("input: %s ¥n", inbuf);
    write(fdgpio2, "1", 1);
  }else{
    printf("input: %s ¥n", inbuf);
    write(fdgpio2, "0", 1);
  }
  sleep(1);
}
  return 0;
}
