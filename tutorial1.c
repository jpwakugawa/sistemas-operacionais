#include <stdio.h>
#include <unistd.h>

// Utilize em conjunto com o htop para monitorar os recursos em tempo real
int main(int argc, char const *argv[]) {
    int var = 10;
    var += 20;

    pid_t id = fork(); // Chamada de sistema para criar processo filho

    while(1) {
        var++;
        printf("PID (Process ID): %d | Var: %d\n\n", id, var);
	    sleep(5); // Comente essa linha :)
    }

    return 0;
}
