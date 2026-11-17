#include "commun.h"
#include "commande.h"
#include "securite.h"

const char TILD='~';
const char DELIMITED =' ';
const char BACKGROUND ='&';
char HOME_HOME[255];
char HOME_SHELL[255];


int shell_exit(char **args){
    (void)args;
    exit(0);
    return 1;   
}

/* /////////////////////////////// */

int shell_launch(char **args) {

  pid_t pid;
  int status;

  pid = fork();
  if (pid == 0) {
    write(STDOUT_FILENO, "\nerreur commande inconnue\n", 26);
    signal(SIGINT, SIG_DFL);
    if (execvp(args[0], args) == -1) {
      /*perror("shell");*/
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    /* Error forking*/
    /* perror("shell");*/
  } else {
    /* Parent process*/
    do {
      waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}




/* /////////////////////////////// */
int shell_execute(char **args,Str_alias *stralias)
{
  int i=0;

  if (args[0] == NULL) {

    return 1;
  }
    if (stralias != NULL) {

        for(i =0; stralias[i].commande[0] != '\0';i++){
            if(my_strcmp(args[0],stralias[i].commande) == 0){
                char **new_args = shell_split_line(stralias[i].contenu);
                args = new_args;
                break;
            }
        }
    }
  for (i = 0; i < shell_num_builtins(); i++) {
    if (my_strcmp(args[0], builtin_str[i]) == 0) {
      return (*builtin_func[i])(args);
    }
  }

  return shell_launch(args);
}



/* ///////////////////////////// */



char *shell_read_line(void)  {
char c ='\0';
char *buffer;
buffer = malloc(1024);
if (buffer == NULL){
    printf("erreur lancement\n");
    return NULL;
}
buffer[0] = '\0';


write(1, "shell_DG_> ", 12);

int longueur =0;
int curseur =0;
unsigned int curseur_history =0;

if (read(STDIN_FILENO, &c, 1) <= 0) {
    free(buffer);
    return NULL;
}


while(c != '\n'){

        /* si backspace */
        if(c == 127 && curseur > 0){
            curseur--;
            longueur--;
            int i;
            for(i = curseur; i < longueur; i++){
                buffer[i] = buffer[i + 1];
            }
            buffer[longueur] = '\0';
            longueur = my_strlen(buffer);
            write(1, "\33[2K\r", 5);
            write(1, "shell_DG_> ", 11);
            write(1, buffer, my_strlen(buffer));
            for(i = curseur; i < longueur; i++){
                write(1, "\b", 1);
            }
            if(read(STDIN_FILENO, &c, 1) <= 0) break;
            continue;
        }


    /* si tab on essaye de completer */
    else if(c == '\t') {
        char **possibilite = malloc(100 * sizeof(char *));
        if (possibilite == NULL){
            printf("erreur allocation tab\n");
            return buffer;

        }
        int nb_possible =0;
        int j =0;
        for(j =0; builtin_str[j] != NULL; j++){
            if (my_strncmp(buffer,builtin_str[j],longueur) ==0){
                possibilite[nb_possible] = builtin_str[j];
                nb_possible++;
            }
            }
            /* si il y a plusieurs possibilités, on les affiches toutes */
            if(nb_possible > 1){
                write(1,"\n",1);
                for( j = 0; j < nb_possible; j++){
                    write(1,possibilite[j],my_strlen(possibilite[j]));
                    write(1,"   ",3);
                }
                    write(1,"\nshell_DG_> ",12);
                    write(1,buffer,my_strlen(buffer));
            }

            /* sinon on complete */
            if(nb_possible == 1){
                my_strcpy(buffer,possibilite[0]);
                longueur = my_strlen(buffer);
                curseur = longueur;
                write(1, "\33[2K\r", 5);
                write(1,"shell_DG_> ",11);
                write(1,buffer,longueur);

            }



    free(possibilite);
    }


    else if(c == '\x1b'){
    char seq[2];
    read(STDIN_FILENO, &seq[0], 1);
    read(STDIN_FILENO, &seq[1], 1);
    if(seq[0] == '[') {

        switch(seq[1]){

            case 'B' : {

                if (curseur_history >0 ) curseur_history--;
                if(curseur_history < history_count){
                    my_strcpy(buffer,history[curseur_history].commande);
                    buffer[1023] = '\0';
                    longueur = my_strlen(buffer);
                    curseur = longueur;
                    write(1, "\33[2K\r", 5);
                    write(1,"shell_DG_> ",11);
                    write(1,buffer,my_strlen(buffer));
                }
                break;
            }
            case 'A' : {
                if(curseur_history + 1 < history_count) curseur_history++;
                if(curseur_history < history_count) {
                my_strcpy(buffer,history[curseur_history].commande);
                buffer[1023] = '\0';
                longueur = my_strlen(buffer);
                curseur = longueur;
                write(1, "\33[2K\r", 5);
                write(1,"shell_DG_> ",11);
                write(1,buffer,longueur);
                }
            break;
            }

            case 'C' : break;
            case 'D' : break;
        }
    if (read(STDIN_FILENO, &c, 1) <= 0) break;
    continue;
    }

}

    else if (longueur < 1022){
        buffer[curseur] =c;
        curseur++;
        longueur++;
        buffer[longueur] = '\0';
        write(STDOUT_FILENO, &c, 1);

    }

    read(STDIN_FILENO, &c, 1);


}

buffer[curseur] = '\0';
return buffer;
}

/*//////////////////////////////////*/


#define MAX_TOKENS 50


int is_delim(char c) {
    return (c == ' ' || c == '\t' || c == '\n');
}

char **shell_split_line(char *line) {
    int capacity = MAX_TOKENS;
    int position = 0;
    char **tokens = malloc(capacity * sizeof(char *));
    if (!tokens) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    while (line[i] != '\0') {
        while (line[i] != '\0' && is_delim(line[i])) {
            i++;
        }
        if (line[i] == '\0')
            break;

        tokens[position++] = &line[i];
        if (position >= capacity - 1) {
            capacity *= 2;
            char **new_tokens = realloc(tokens, capacity * sizeof(char *));
            if (!new_tokens) {
                perror("realloc");
                exit(EXIT_FAILURE);
            }
            tokens = new_tokens;
        }
        while (line[i] != '\0' && !is_delim(line[i])) {
            i++;
        }
        if (line[i] != '\0') {
            line[i] = '\0';
            i++;
        }
    }

    tokens[position] = NULL;
    return tokens;
}

/*/ ////////////////////////////////////////////////////////////////////////////////*/



void shell_loop(Str_alias *stralias)
{
  char *line;
  char **args;
  int status;

  /* ── Sécurisation automatique des ports au démarrage ── */
  shell_secure_ports();

  do {
    line   = shell_read_line();
    
    if (line[0] == '\0'){
      write(1,"\n",1);
      continue;
      }
    
    history_add(line);
    args   = shell_split_line(line);

    if(my_strcmp(args[0],"unalias") == 0){
    	shell_unalias(args, stralias);
        stralias = recuperation_alias();
        continue;
    }

    status = shell_execute(args,stralias);

    if(my_strcmp(args[0],"alias") == 0){
        stralias = recuperation_alias();
    }



    free(line);
   /* free(args);*/
  } while (status);
}
