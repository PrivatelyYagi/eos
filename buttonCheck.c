#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define GPIO_PAHT "/sys/class/gpio/"
#define GPIO5 GPIO_PAHT "gpio5/value"
#define GPIO5_DIRECTION GPIO_PAHT "gpio5/direction"
#define GPIO5_EDGE GPIO_PAHT "GPIO5/edge"
#define INBUF_SIZE 256

int main(void) {

FILE *fp;
char inbuf[INBUF_SIZE];
fp= fopen(GPIO5, "r"); if(fp==NULL){
perror("fopen error:");
return 1; }
for(;;){
fseek(fp, 0L, SEEK_SET); fgets(inbuf, INBUF_SIZE, fp); fflush(fp);
printf("input: %s ¥n", inbuf); if(strcmp(inbuf,"0¥n")==0){
break; }
sleep(1); }
return 0; }
