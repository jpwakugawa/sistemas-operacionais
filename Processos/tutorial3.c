#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    int variavel;
    pid_t pid = fork();

    if(pid == 0)
        execlp("/bin/ls", "ls", NULL);
    else {
        printf("My son is so different! \n");
        wait(NULL);
    }

    return 0;
}