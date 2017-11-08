#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <poll.h>

#define TIMEOUT_MS (3000) // 3秒
#define TIMEOUT_NONE (-1) //
#define PFD_SIZE (1)

void showPollRevents(int fd, short revents);

int main(void) {
int ready, len;
struct pollfd pfd[PFD_SIZE];
pfd[0].fd = STDIN_FILENO; // STDIN_FILENO=0
pfd[0].events = POLLIN; //読込準備OK
write(STDOUT_FILENO, "waiting for interrupt...¥n", strlen("waiting for interrupt...¥n"));
ready=poll(pfd, PFD_SIZE, TIMEOUT_MS);
showPollRevents(STDOUT_FILENO, pfd[0].revents);
if(ready==0){
len=write(STDOUT_FILENO, "timeout.¥n", strlen("timeout.¥n"));
}else{
len=write(STDOUT_FILENO, "keyin.¥n", strlen("keyin.¥n"));
}
return (EXIT_SUCCESS);
}
void showPollRevents(int fd, short revents) {
if(revents & POLLIN){
write(fd, "POLLIN¥n", strlen("POLLIN¥n"));
}
if(revents & POLLPRI){
write(fd, "POLLPRI¥n", strlen("POLLPRI¥n")); }
if(revents & POLLOUT){
write(fd, "POLLOUT¥n", strlen("POLLOUT¥n"));
}
if(revents & POLLERR){
write(fd, "POLLERR¥n", strlen("POLLERR¥n")); }
if(revents & POLLHUP){
write(fd, "POLLHUP¥n", strlen("POLLHUP¥n"));
}
if(revents & POLLNVAL){
write(fd, "POLLNVAL¥n", strlen("POLLNVAL¥n")); }
}