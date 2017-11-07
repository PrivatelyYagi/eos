#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

#define GPIOPATH "/sys/class/gpio/"
#define GPIO2 GPIOPATH "gpio2/value"
#define GPIOPATH "/sys/class/gpio/"
#define GPIO3 GPIOPATH "gpio3/value"
#define GPIOPATH "/sys/class/gpio/"
#define GPIO4 GPIOPATH "gpio4/value"


int main(void){

int fdgpio2,fdgpio3,fdgpio4;
struct timespec ts;
int i;

ts.tv_sec = 0; //sec.
ts.tv_nsec = 500000000; //nano sec. (500ms)

printf("led chika chika ¥n");

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
// gpio3,4のopen

for(i=0; i<10; i++){
write(fdgpio2, "1", 1);
nanosleep(&ts, NULL);
write(fdgpio3, "1", 1);
nanosleep(&ts, NULL);
write(fdgpio4, "1", 1);
nanosleep(&ts, NULL);
write(fdgpio2, "0", 1);
nanosleep(&ts, NULL);
write(fdgpio3, "0", 1);
nanosleep(&ts, NULL);
write(fdgpio4, "0", 1);
nanosleep(&ts, NULL);
} //end of for
close(fdgpio2);
close(fdgpio3);
close(fdgpio4);
return 0;
} //end of main
