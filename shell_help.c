#include "commun.h"
#include "commande.h"
typedef struct Commande  {
    char *nom;
    char *description;
} Commande;

struct Commande commande[] = {
    {"cd", "\nChange le répertoire courant vers le chemin spécifié.\n cd <chemin>\n <..> pour revenir en arrière\n"},

    {"mkdir", "\nCrée un nouveau répertoire avec le nom donné."},

    {"rmdir", "\nSupprime un répertoire vide."},

    {"echo", "\nAffiche un message ou la valeur d'une variable dans le terminal."},

    {"ls", "\nListe les fichiers et répertoires du dossier courant."},

    {"alias", "\nCrée ou affiche des alias pour remplacer des commandes par des raccourcis."},

    {"unalias", "Supprime un alias précédemment défini."},

    {"cat", "\nAffiche le contenu d'un fichier texte ou concatène plusieurs fichiers."},

    {"touch", "\nCrée un fichier vide ou met à jour la date de modification d’un fichier."},

    {"exit", "\nQuitte le shell ou termine la session du terminal."},

    {"pwd", "\nAffiche le chemin absolu du répertoire courant."},

    {"history", "\nAffiche la liste des commandes précédemment exécutées."},

    {"date", "\nAffiche ou modifie la date et l’heure du système."},

    {"head", "\nAffiche les premières lignes d’un fichier."},

    {"fdump", "\nCommande non standard : dépend du système, généralement utilisée pour afficher le contenu brut ou mémoire d’un fichier."},

    {"wait", "\nAttend la fin de l’exécution d’un ou plusieurs processus en arrière-plan."}
};

int shell_help(char **args) {

int i =0;

if (args[1] == NULL) {
    printf("\n");
    printf(" bienvenue sur le shell de grégoire et danny : voici la liste des commandes disponibles : \n");
    for(i =0; builtin_str[i] != NULL; i++){
        printf("%s\n", builtin_str[i]);
    }
}
else {
        for(i =0; commande[i].nom != NULL; i++){
            if(my_strcmp(commande[i].nom,args[1]) == 0){
                printf("%s\n",commande[i].description);

            }
    }

}

return 1;

}

