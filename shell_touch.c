#include "commun.h"
#include "commande.h"

int shell_touch(char **args) {

    if (args[1] == NULL) {
        fprintf(stderr, "shell: touch: argument manquant\n");
        return 1;
    }
    int i =1;
    for (i = 1; args[i] != NULL; i++) {
        FILE *f = fopen(args[i], "a");
        if (f == NULL) {
            perror("shell");
        } else {
            fclose(f);
        }
    }

    return 1;
}
