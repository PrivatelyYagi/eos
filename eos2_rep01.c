/*
   福永祐真
   R15E1004
   スイッチでLEDの点灯パターンを切り替える
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <poll.h>
#include <time.h>
#include <sys/mman.h>

#define GPIO_PATH "/sys/class/gpio/"
#define GPIO2 GPIO_PATH "gpio2/value"
#define GPIO3 GPIO_PATH "gpio3/value"
#define GPIO4 GPIO_PATH "gpio4/value"
#define GPIO5 GPIO_PATH "gpio5/value"

#define TIMEOUT_MS (5000)
#define INBUF_SIZE (80)
#define PFD_SIZE (1)

void ChildProcess(int*);
void showPollRevents(int fd, short revents);

int main(void){
    int fd5;
    int pret, len;
    char inbuf[INBUF_SIZE];
    struct pollfd pfd[PFD_SIZE];
    fd5 = open(GPIO5, O_RDWR);
    if(fd5 < 0){
        perror("Cannot open GPIO5");
        exit(-1);
    }

    pfd[0].fd = fd5;
    pfd[0].events = POLLPRI | POLLERR;

    // Map pages of memory
    int *count = (int*)mmap(0, 1, PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);

    pid_t pid = fork();
    if(pid < 0){
        perror("fork");
        exit(-1);
    }else if(pid == 0){
        // --------------------------------
        // Child process
        // --------------------------------
        ChildProcess(count);
        return 0;
    }else{
        // --------------------------------
        // Parent process
        // --------------------------------
        const char *message = "waiting for interrupt...\n";
        write(STDOUT_FILENO, message, strlen(message));

        while(1){
            pret = poll(pfd, PFD_SIZE, TIMEOUT_MS);
            usleep(700);
            showPollRevents(STDOUT_FILENO, pfd[0].revents);

            if(pret == 0){
                write(STDOUT_FILENO, "timeout.\n", strlen("timeout.\n"));
                *count = -1;
                close(fd5);
                return 0;
            }else{
                write(STDOUT_FILENO, "sw\n", strlen("sw\n"));
                lseek(fd5, 0, SEEK_SET);
                len=read(fd5, inbuf, INBUF_SIZE);
                write(STDOUT_FILENO, inbuf, len);
                if(9 <= *count)
                    *count = 0;
                else
                    *count = *count + 1;
            }
        }
    }
    return 0;
}

void ChildProcess(int *count){
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = 100000000; // 100ms

    int fd2, fd3, fd4;
    fd2 = open(GPIO2, O_RDWR);
    if(fd2 < 0){
        perror("Cannot open GPIO2");
        exit(-1);
    }
    fd3 = open(GPIO3, O_RDWR);
    if(fd3 < 0){
        perror("Cannot open GPIO3");
        exit(-1);
    }
    fd4 = open(GPIO4, O_RDWR);
    if(fd4 < 0){
        perror("Cannot open GPIO4");
        exit(-1);
    }

    while(1){
        switch(*count){
            case 0:
                // off
                write(fd2, "0", 1);
                write(fd3, "0", 1);
                write(fd4, "0", 1);
                break;
            case 1:
                // GPIO2 30%
                write(fd4, "0", 1);
                ts.tv_nsec = 10000000;
                write(fd2, "1", 1);
                nanosleep(&ts, NULL);
                ts.tv_nsec = 10000000;
                write(fd2, "0", 1);
                nanosleep(&ts, NULL);
                break;
            case 2:
                // GPIO2 50%
                ts.tv_nsec = 10000000;
                write(fd2, "1", 1);
                nanosleep(&ts, NULL);
                ts.tv_nsec = 5000000;
                write(fd2, "0", 1);
                nanosleep(&ts, NULL);
                break;
            case 3:
                // GPIO2 100%
                write(fd2, "1", 1);
                break;
            case 4:
                // GPIO3 30%
                write(fd2, "0", 1);
                ts.tv_nsec = 10000000;
                write(fd3, "1", 1);
                nanosleep(&ts, NULL);
                ts.tv_nsec = 10000000;
                write(fd3, "0", 1);
                nanosleep(&ts, NULL);
                break;
            case 5:
                // GPIO3 50%
                ts.tv_nsec = 10000000;
                write(fd3, "1", 1);
                nanosleep(&ts, NULL);
                ts.tv_nsec = 5000000;
                write(fd3, "0", 1);
                nanosleep(&ts, NULL);
                break;
            case 6:
                // GPIO3 100%
                write(fd3, "1", 1);
                break;
            case 7:
                // GPIO4 30%
                write(fd3, "0", 1);
                ts.tv_nsec = 10000000;
                write(fd4, "1", 1);
                nanosleep(&ts, NULL);
                ts.tv_nsec = 10000000;
                write(fd4, "0", 1);
                nanosleep(&ts, NULL);
                break;
            case 8:
                // GPIO4 50%
                ts.tv_nsec = 10000000;
                write(fd4, "1", 1);
                nanosleep(&ts, NULL);
                ts.tv_nsec = 5000000;
                write(fd4, "0", 1);
                nanosleep(&ts, NULL);
                break;
            case 9:
                // GPIO4 100%
                write(fd4, "1", 1);
                break;
            default:
                close(fd2);
                close(fd3);
                close(fd4);
                return;
                break;
        }
    }
}

void showPollRevents(int fd, short revents){
    if(revents & POLLIN)
        write(fd, "POLLIN¥n", strlen("POLLIN¥n"));
    if(revents & POLLPRI)
        write(fd, "POLLPRI¥n", strlen("POLLPRI¥n"));
    if(revents & POLLOUT)
        write(fd, "POLLOUT¥n", strlen("POLLOUT¥n"));
    if(revents & POLLERR)
        write(fd, "POLLERR¥n", strlen("POLLERR¥n"));
    if(revents & POLLHUP)
        write(fd, "POLLHUP¥n", strlen("POLLHUP¥n"));
    if(revents & POLLNVAL)
        write(fd, "POLLNVAL¥n", strlen("POLLNVAL¥n"));
}

