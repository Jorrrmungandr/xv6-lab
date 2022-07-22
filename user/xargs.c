#include "user.h"
#include "../kernel/param.h"

int main(int argc, char *argv[])
{
    // buf is the char buffer for read()
    char buf[256];
    // exec_argv is arguments vector for exec()
    char *exec_argv[MAXARG];
    // p_argv is string pointer for arg copy
    char **p_argv = exec_argv;
    // p, q are char pointer for string read
    char *p = buf, *q = buf;

    // copy initial argv
    for(int i=1; i<argc; ++i) {
        *p_argv = argv[i];
        p_argv++;
    }

    // read 1 byte every time until whitespace, and add the string as an arg
    while(read(0, p, 1)) {
        if(*p == ' ' || *p == '\n') {
            *p = '\0';
            *p_argv = q;
            p_argv++;
            q = p + 1;
        }
        p++;
    }

    // set a flag for exec_argv
    *p_argv = 0;

    int fd = fork();
    if (fd == 0) {
        exec(argv[1], exec_argv);
        printf("exec failed!\n");
        exit(1);
    }
    else {
        wait(0);
    }

    exit(0);
}