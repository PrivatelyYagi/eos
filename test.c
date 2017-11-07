#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define GPIO_PATH "/sys/class/gpio/"
#define GPIO5 GPIO_PATH "gpio5/value"
#define GPIO2 GPIO_PATH "gpio2/value"
#define INBUF_SIZE 256

int main(void){
  FILE *fpgpio5, *fpgpio2;
  char inbuf[INBUF_SIZE];

  fpgpio5 = fopen(GPIO5, "r");
  if(fpgpio5==NULL){
    perror("fopen error:");
    return 1;
  }
  fpgpio2 = fopen(GPIO2, "w");
  if(fpgpio2 == NULL){
    perror("fopen error:");
    return 1;
  }
  fprintf(fpgpio2,"1");
  fflush(fpgpio2);
  sleep(1);
  fprintf(fpgpio2,"0");
  fflush(fpgpio2);
  sleep(1);

for(;;){
  fseek(fpgpio5, 0L, SEEK_SET);
  fgets(inbuf, INBUF_SIZE, fpgpio5);
  fflush(fpgpio5);
  if(strcmp(inbuf,"0\n")==0){
    printf("input: %s \n", inbuf);
    fprintf(fpgpio2,"0");
    fflush(fpgpio2);
  }else{
    printf("input: %s \n", inbuf);
    fprintf(fpgpio2,"1");
    fflush(fpgpio2);
  }
  sleep(1);
}
  return 0;
}

