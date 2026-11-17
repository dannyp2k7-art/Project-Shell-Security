#include "commun.h"
#include "commande.h"

int shell_mkdir(char **args) {

if (args[1] == NULL) {
    fprintf(stderr, "shell: mkdir: argument manquant\n");
    return 1;
}
int i =0;
for (i = 1; args[i] != NULL; i++) {
    if (mkdir(args[i], 0755) != 0) {
        perror("shell");
    }
}
return 1;
}
