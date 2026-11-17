#include "commun.h"
#include "commande.h"

int shell_echo(char **args){

if(args[1] == NULL){
    return 1;
}
char variable[300];
int option_format =0;
printf("\n");
int i =0;
for(i = 1; args[i] != NULL; i++){

   						 /* vérification options -e ( qui dit de prendre en compte les   \n \t ect...*/
    if(my_strcmp(args[i],"-e") == 0) {
    option_format = 1;
    continue;
    }

   int j =0;
    for(j=0; args[i][j] != '\0'; j++){

        					/* vérification variable d'environement (en détectant le $)*/
        if (args[i][j] == '$'){

            int f = 0;
            int k =0;
            for( k=j+1; ((args[i][k] != '\0') && (args[i][k] != '$')); k++){
            variable[f++] = args[i][k];
            }
            variable[f] = '\0';
            j = k-1;
            char *variable1 = getenv(variable);
            if( variable1 != NULL){
                printf("%s",variable1);
                continue;
            }
        }
        /* vérification des formats \n */
        if (option_format == 1 && args[i][j] == '\\') {

            char lettre = args[i][j+1];

            switch(lettre){

            case 'n': printf("\n"); break;
            case 't': printf("\t"); break;
            case 'a': printf("\a"); break;
            case 'r': printf("\r"); break;
            default : printf("%c",lettre);

            }
            j+=2;
        }
        printf("%c",args[i][j]);
    }
    printf(" ");
}
printf("\n");
return 1;
}

/* ////////////////// bunny */
int shell_sortez_une_feuille(char **args){
FILE *fichier = fopen(".bunny.txt", "r");
if (fichier == NULL) {
    return 1;
}

fseek(fichier, 0, SEEK_SET);

int c;
while ((c = fgetc(fichier)) != EOF) {
    printf("%c", c);
}

fclose(fichier);
return 1;


}

