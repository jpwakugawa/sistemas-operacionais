#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

// Resultou na saída 10100?
int main(void) {
    int var;
    pid_t pid = fork();

    if(pid == 0)
        var = 10;

    else {
        var = 100;
        wait(NULL);
    }

    printf("%d", var);
    return 0;
}
