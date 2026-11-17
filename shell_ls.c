#include "commun.h"
#include "commande.h"

int shell_ls(char **args) {
    printf("\n");
    char *chemin = ".";
    int option_all = 0;
    int option_long = 0;
    int i = 1;

    for (i = 1; args[i] != NULL; i++) {
        if (my_strcmp(args[i], "-a") == 0)       option_all = 1;
        else if (my_strcmp(args[i], "-l") == 0)  option_long = 1;
        else if (my_strcmp(args[i], "-al") == 0 || my_strcmp(args[i], "-la") == 0) {
            option_all = 1;
            option_long = 1;
        } else {
            chemin = args[i];
        }
    }

    DIR *dir = opendir(chemin);
    if (dir == NULL) {
        perror("shell");
        return 1;
    }

    struct dirent *entree;
    struct stat st;
    char chemin_complet[512];

    while ((entree = readdir(dir)) != NULL) {

        if (!option_all && entree->d_name[0] == '.')
            continue;

        if (option_long) {
            my_strcpy(chemin_complet, chemin);
            my_strconcat(chemin_complet, "/");
            my_strconcat(chemin_complet, entree->d_name);
            stat(chemin_complet, &st);

            printf("%c", S_ISDIR(st.st_mode) ? 'd' : '-');
            printf("%c", (st.st_mode & S_IRUSR) ? 'r' : '-');
            printf("%c", (st.st_mode & S_IWUSR) ? 'w' : '-');
            printf("%c", (st.st_mode & S_IXUSR) ? 'x' : '-');
            printf("%c", (st.st_mode & S_IRGRP) ? 'r' : '-');
            printf("%c", (st.st_mode & S_IWGRP) ? 'w' : '-');
            printf("%c", (st.st_mode & S_IXGRP) ? 'x' : '-');
            printf("%c", (st.st_mode & S_IROTH) ? 'r' : '-');
            printf("%c", (st.st_mode & S_IWOTH) ? 'w' : '-');
            printf("%c", (st.st_mode & S_IXOTH) ? 'x' : '-');
            printf(" %6ld %s\n", (long)st.st_size, entree->d_name);
        } else {
            printf("%s\n", entree->d_name);
        }
    }

    closedir(dir);
    return 1;
}
