#include "commun.h"
#include "commande.h"

int shell_wait(char **args) {

    int status;
    pid_t pid = wait(&status);

    if (pid == -1) {
        perror("shell");
        return 1;
    }

    printf("processus %d terminé", pid);

    if (WIFEXITED(status)) {
        printf(" avec le code %d", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        printf(" par le signal %d", WTERMSIG(status));
    }

    printf("\n");
    return 1;
}
