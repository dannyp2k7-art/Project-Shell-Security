#include "commande.h"
#include "commun.h"
#include "coeur.h"

static struct termios raw;
static struct termios original;


int main(int argc, char **argv)
{
    signal(SIGINT, SIG_IGN);


    history_load();
    tcgetattr(STDIN_FILENO, &original);
    raw = original;
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);



  printf("Mini SHELL - exit pour Quitter \n");
    Str_alias *stralias = recuperation_alias();
    if( stralias == NULL){
        printf("erreur récupération, alias n'est pas disponible\n");
    }

  shell_loop(stralias);

  tcsetattr(STDIN_FILENO, TCSANOW, &original);
  printf("\nFin du Mini SHELL \n");
  return EXIT_SUCCESS;
}
