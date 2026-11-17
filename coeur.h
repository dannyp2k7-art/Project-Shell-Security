#ifndef COEUR_H_INCLUDED
#define COEUR_H_INCLUDED

#include "commun.h"

char  *shell_read_line(void);
char **shell_split_line(char *line);
int    is_delim(char c);
void   shell_loop(Str_alias *stralias);

#endif
