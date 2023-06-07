// implemente aqui!
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    char *args[] = {argv[1], NULL};

    while(1) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            return 1;
        }

        if (pid == 0) {
            printf("starting %s with pid=%d\n", args[0], getpid());
            execvp(args[0], args);
            return 0;
        }
        else {
            int status;
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}