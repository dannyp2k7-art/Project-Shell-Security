#include "commun.h"
#include "commande.h"

int shell_cat(char **args) {

    if (args[1] == NULL) {
        fprintf(stderr, "shell: cat: argument manquant\n");
        return 1;
    }

    int i = 1;
    for (i = 1; args[i] != NULL; i++) {

        FILE *fichier = fopen(args[i], "r");
        if (fichier == NULL) {
            perror("shell");
            continue;
        }

        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), fichier) != NULL) {
            printf("%s", buffer);
        }

        fclose(fichier);
    }

    return 1;
}
