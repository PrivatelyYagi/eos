#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <poll.h>

int main(){
int i;
int fd;
int ret;
struct pollfd pfd;
char c;

//Enable gpio25
fd = open(“/sys/class/gpio/export”, O_WRONLY);
write(fd, “25”, 2);
close(fd);

//Set gpio25 as input
fd = open(“/sys/class/gpio/gpio25/direction”, O_WRONLY);
write(fd, “in”, 2);
close(fd);

//Set gpio25 interrupt
fd = open(“/sys/class/gpio/gpio25/edge”, O_WRONLY);
//write(fd, “falling”, 7);
write(fd, “both”, 4);
close(fd);

//Wait for interrupt, repeat 10 times.
fd = open(“/sys/class/gpio/gpio25/value”, O_RDONLY);
pfd.fd = fd;
pfd.events = POLLPRI;
for(i = 0; i < 10; i++){
lseek(fd, 0, SEEK_SET);
ret = poll(&pfd, 1, 3000);
read(fd, &c, 1);
if(ret == 0)
printf(“Timeout\n”);
else
printf(“%d=%c\n”, i, c);
}
close(fd);

//Disable gpio25
fd = open(“/sys/class/gpio/unexport”, O_WRONLY);
write(fd, “25”, 2);
close(fd);

return(0);
}