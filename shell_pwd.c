#include "commun.h"
#include "commande.h"

int shell_pwd(char **args) {
    printf("\n");
    char buffer[1024];

    if (getcwd(buffer, sizeof(buffer)) == NULL) {
        perror("shell");
        return 1;
    }

    printf("%s\n", buffer);
    return 1;
}
