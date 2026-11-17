#ifndef COMMUN_H_INCLUDED
#define COMMUN_H_INCLUDED

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include<signal.h>
#include<sys/resource.h>
#include <dirent.h>
#include <time.h>
#include <termios.h>

#define HISTORY_SIZE 100
#define shell_BUFSIZE 1024
#define EXIT_FAILURE_SHELL 0
#define EXIT_SUCCESS_SHELL 1
#define EXIT_ERROR_SHELL 2

#define ALIAS_LONGUEUR_MAX 256

#define MAX_TOKENS 50

#define HISTORY_FILE ".myshell_history"


/* historique. */
typedef struct {
    int  numero;
    char commande[256];
} t_history;

extern t_history history[HISTORY_SIZE];
extern int history_count;

/* help */
typedef struct {
    char name[15];
    char description[200];
} Commandes;



/*termios*/



extern const char TILD;
extern const char DELIMITED;
extern const char BACKGROUND;
extern char HOME_HOME[255];
extern char HOME_SHELL[255];



void history_add(const char *line);
void history_load(void);

typedef struct Str_alias{
    char commande[100];
    char contenu[100];
} Str_alias;






char *my_strcpy(char *dest, const char *src);
char *my_strdup(const char *s);
int my_strcmp(char s1[], char s2[]);
char *my_strconcat(char *dest, const char *src);
int my_strlen(char *buffer);
char  *my_strncpy(char *dest, const char *src, unsigned int n);
Str_alias *recuperation_alias();
char **shell_split_line(char *line);
int my_strncmp(const char *s1, const char *s2, int n);
#endif /* COMMUN_H_INCLUDED */
