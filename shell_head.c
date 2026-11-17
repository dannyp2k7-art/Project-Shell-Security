#include "commun.h"
#include "commande.h"

int shell_head(char **args) {

if (args[1] == NULL) {
    fprintf(stderr, "head: argument manquant\n");
    return 1;
}




FILE *fichier = fopen(args[1],"r");

if (fichier == NULL){
    fprintf(stderr, "erreur fichier inexistant\n");
    return 1;
}


int compteur =10;
char buffer[1000];
int i =0;                                            /*sécurité si buffer trop petit ? malloc ?*/
for(i=0; i < compteur; i++ ){

    fgets(buffer, 1000, fichier);
    printf("%s",buffer);

}




return 1;
}
