#include "commun.h"
#include "commande.h"


Str_alias *recuperation_alias(){

FILE *fichier = fopen("liste_alias.txt","r");
if (fichier == NULL){
    printf("erreur fichier alias non trouvé");
    return NULL;
}

char buffer[ALIAS_LONGUEUR_MAX];
Str_alias *stralias = NULL;
int i =0;

fseek(fichier,0,SEEK_SET);
while (fgets(buffer,sizeof(buffer),fichier) != NULL){

    stralias = realloc(stralias,sizeof(Str_alias)*(i+1));
    if(stralias == NULL){
    free(stralias);
    return NULL;
    }

    int y =0;
    while(buffer[y] != '='){
        stralias[i].commande[y] = buffer[y];
        y++;
    }
    y++;
    int j =0;
    while(buffer[y] != '\0'){
        stralias[i].contenu[j] = buffer[y];
        j++;
        y++;
    }
    stralias[i].contenu[j-1] = '\0';   /*verifficer ça*/
i++;
}
fclose(fichier);
return stralias;
}


int shell_alias(char **args) {
        printf("\n");

FILE *fichier = fopen("liste_alias.txt","a+");   /* resoudre pas possible de faire alias 2f a la suite*/
if (fichier == NULL){
    printf("erreur fichier alias non trouvé");
    return 1;
}

char buffer[ALIAS_LONGUEUR_MAX];
buffer[0] = '\0';

/* si il y a uniquement alias : on affiche la liste des alias dispo*/
fseek(fichier,0,SEEK_SET);
if(args[1] == NULL){
    while (fgets(buffer,sizeof(buffer),fichier) != NULL){
        printf("%s",buffer);
    }
printf("\n");
fclose(fichier);
return 1;
}


int i =1;
for(i=1; args[i] != NULL; i++){
    my_strconcat(buffer,args[i]);
    my_strconcat(buffer," ");
}
my_strconcat(buffer,"\n");


fseek(fichier,0,SEEK_END);
fprintf(fichier,"%s",buffer);




fclose(fichier);
return 1;
}


/* /////////////unalias////////////////// */


int shell_unalias(char **args, Str_alias *stralias) {

FILE *fichier = fopen("liste_alias.txt","r");
if (fichier == NULL){
    printf("erreur ouverture fichier alias\n");
    return 1;
}


char buffer[ALIAS_LONGUEUR_MAX];

int trouve =0;

fseek(fichier,0,SEEK_SET);
while(fscanf(fichier,"%255[^=]",buffer) == 1) {
    fgetc(fichier);
    if(my_strcmp(buffer,args[1]) == 0) {
        trouve =1;
        break;
    }
fgets(buffer, sizeof(buffer), fichier);  /* (pour lire le reste de la ligne)*/
}


if (trouve == 1){
    fseek(fichier,0,SEEK_SET);
    FILE *fichier_temp = fopen("liste_alias_temp.txt","w");
    if (fichier_temp == NULL){
        printf("erreur ouverture nouveau fichier alias\n");
        return 1;
}

    char ligne_complete[512];
    int len_alias = my_strlen(args[1]);

while (fgets(ligne_complete, sizeof(ligne_complete), fichier)) {
            if (my_strncmp(ligne_complete, args[1], len_alias) == 0 && ligne_complete[len_alias] == '=') {
                continue;
            }
            fputs(ligne_complete, fichier_temp);
        }

fclose(fichier);
fclose(fichier_temp);
remove("liste_alias.txt");
rename("liste_alias_temp.txt","liste_alias.txt");
printf("\nsupression réussi\n");
return 1;
}
printf("\ncommande introuvable\n");

fclose(fichier);
return 1;
}




