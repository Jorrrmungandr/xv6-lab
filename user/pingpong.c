#include "user/user.h"

#define MAX_BUF 4

int main(int argc, char *argv[])
{
    int p[2];
    pipe(p);

    if(fork() == 0){
        char buf[MAX_BUF];
        if(read(p[0], buf, 1) != 1){
            fprintf(2, "read error in child\n");
            exit(1);
        }
        close(p[0]);
        int pid = getpid();
        fprintf(1, "%d: received ping\n", pid);
        
        if(write(p[1], buf, 1) != 1){
            fprintf(2, "write error in child\n");
            exit(1);
        }
        close(p[1]);
        exit(0);
    }
    else{
        char buf[MAX_BUF];
        buf[1] = '\0';
        if(write(p[1], "a", 1) != 1){
            fprintf(2, "write error in parent\n");
            exit(1);
        }
        close(p[1]);
        wait(0);

        if(read(p[0], buf, 1) != 1){
            fprintf(2, "read error in parent\n");
            exit(1);
        }
        close(p[0]);
        int pid = getpid();
        fprintf(1, "%d: received pong\n", pid);
        exit(0);
    }
}