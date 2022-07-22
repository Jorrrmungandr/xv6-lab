#include "user/user.h"

int main(int argc, char *argv[])
{
    if(argc <= 1){
        fprintf(2, "sleep: missing argument\n");
        exit(1);
    }
    else if(argc > 2){
        fprintf(2, "sleep: too many arguments\n");
        exit(1);
    }
    else{
        sleep(atoi(argv[1]));
        exit(0);
    }

}