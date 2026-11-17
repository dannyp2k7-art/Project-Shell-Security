#include "commun.h"
#include "commande.h"

int shell_date(char **args) {

    time_t t = time(NULL);
    if (t == -1) {
        perror("shell");
        return 1;
    }

    struct tm *tm_info = localtime(&t);
    if (tm_info == NULL) {
        perror("shell");
        return 1;
    }

    char buffer[64];
    strftime(buffer, sizeof(buffer), "%A %d %B %Y %H:%M:%S", tm_info);
    printf("%s\n", buffer);

    return 1;
}

