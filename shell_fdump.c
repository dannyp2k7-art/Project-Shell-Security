#include "commun.h"
#include "commande.h"


int shell_fdump(char **args){


if(args[1] == NULL){
	printf("merci de mettre un fichier en paramètre\n");
	return 1;
}

FILE *fichier = fopen(args[1],"rb");
if (fichier == NULL){
	printf("erreur impossible d'ouvrir le fichier %s\n",args[1]);
	return 1;
}


if (fseek(fichier, 0, SEEK_SET) != 0) {
    fclose(fichier);
    printf("erreur fseek");
    return 1;
}

printf("\n nom du fichier : \n");

int ret;
unsigned char octet;
int octetlu = 0;
unsigned int compteur =0;
unsigned long compteurligne =0;
int nbOctet = 16;
char tab[nbOctet+1];



while ((ret = getc(fichier)) != EOF) {


    octet = (unsigned char )ret;
    printf("%02X ", octet);
    tab[compteur] = octet;

    compteur++;
    octetlu++;

    if(compteur == nbOctet){
        compteur =0;
        compteurligne++;
        printf(" : ");
        int i =0;
        for(i=0; i < nbOctet;i++){
            if (tab[i] >= 32 && tab[i] <= 126) {
                printf("%c", tab[i]);
            } else {
                printf(".");
            }
    }
    printf("\n");
    printf("%08lu: ",compteurligne*nbOctet);
    }
    }
    printf("\n");
fclose(fichier);
return 1;
}
