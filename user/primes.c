#include "user/user.h"


// filter the multiple of number in the pipe passed in
void filter(int p[2]){
    int prime;
    read(p[0], &prime, 4);
    if(prime == -1){
        exit(0);
    }
    printf("prime %d\n", prime);

    int pNext[2];
    pipe(pNext);

    if(fork() == 0){
        close(p[0]);
        filter(pNext);
        exit(0);
    }
    else{
        int num;
        close(pNext[0]);
        while(read(p[0], &num, 4) && num != -1){
            if(num % prime != 0){
                write(pNext[1], &num, 4);
            }
        }
        num = -1;
        write(pNext[1], &num, 4);
        wait(0);
        exit(0);
    }

}


int main(int argc, char *argv[])
{
    int p[2];
    pipe(p);

    if(fork() == 0){
        close(p[1]);
        filter(p);
    }
    else{
        close(p[0]);
        for(int i = 2; i <= 35; ++i){
            write(p[1], &i, 4);
        }
    }
    int i = -1;
    write(p[1], &i, 4);
    wait(0);
    exit(0);
}