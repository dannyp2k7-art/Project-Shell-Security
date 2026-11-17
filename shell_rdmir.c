#include "commun.h"
#include "commande.h"

int shell_rmdir(char **args) {

    if (args[1] == NULL) {
        fprintf(stderr, "shell: rmdir: argument manquant\n");
        return 1;
    }
    int i =1;
    for (i = 1; args[i] != NULL; i++) {
        if (rmdir(args[i]) != 0) {
            perror("shell");
        }
    }

    return 1;
}

