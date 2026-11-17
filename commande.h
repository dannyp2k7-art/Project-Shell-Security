#ifndef COMMANDE_H_INCLUDED
#define COMMANDE_H_INCLUDED

#include "commun.h"
#include "securite.h"

int shell_exit(char **args);
int shell_num_builtins();
int shell_launch(char **args);
int shell_execute(char **args,Str_alias *stralias);
char *shell_read_line(void);
char **shell_split_line(char *line);
void shell_loop(Str_alias *stralias);
int shell_cd(char **args);
int shell_echo(char **args);
int shell_help(char **args);
int shell_mkdir(char **args);
int shell_head(char **args);
int shell_ls(char **args);
int shell_history(char **args);
int shell_pwd(char **args);
int shell_touch(char **args);
int shell_date(char **args);
int shell_rmdir(char **args);
int shell_wait(char **args);
int shell_alias(char **args);
int shell_fdump(char **args);
int shell_history(char **args);
int shell_cat(char **args);

int shell_unalias(char **args, Str_alias *stralias);
int shell_sortez_une_feuille(char **args);
int shell_portctl(char **args);   /* Gestion des ports physiques */

extern char *builtin_str[];
extern int (*builtin_func[]) (char **);
int shell_num_builtins();



#endif /*COMMANDE_H_INCLUDED*/
