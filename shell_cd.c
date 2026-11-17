#include "commun.h"
#include "commande.h"

int shell_cd(char **args) {

char *home =NULL;

if (args[1] == NULL){
    /* si aucun argument, on recupère le chemin du home de l'utilisateur */
    home = getenv("HOME");
    if (home == NULL){
        fprintf(stderr,"erreur home");
        printf("\n");
        return 1;
    }

    if(chdir(home) != 0){
        perror("shell");
    }
}

else
{
if(chdir(args[1]) != 0) {
    perror("shell");

}
}
printf("\n");
return 1;
}
