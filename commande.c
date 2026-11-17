#include "commun.h"
#include "commande.h"

char *builtin_str[] = {
  "cd",
  "exit",
  "echo",
  "mkdir",
  "head",
  "ls",
  "pwd",
  "touch",
  "date",
  "rmdir",
  "wait",
  "alias",
  "fdump",
  "history",
  "help",
  "cat",
  "sortezunefeuille",
  "portctl"
};

int (*builtin_func[]) (char **) = {
  &shell_cd,
  &shell_exit,
  &shell_echo,      /*help et history*/
  &shell_mkdir,
  &shell_head,
  &shell_ls,
  &shell_pwd,
  &shell_touch,
  &shell_date,
  &shell_rmdir,
  &shell_wait,
  &shell_alias,
  &shell_fdump,
  &shell_history,
  &shell_help,
  &shell_cat,
  &shell_sortez_une_feuille,
  &shell_portctl
};

int shell_num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
}
