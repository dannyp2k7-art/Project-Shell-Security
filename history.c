#include "commun.h"
#include "commande.h"

t_history history[HISTORY_SIZE];
int history_count = 0;


void history_add(const char *line) {
    if (line == NULL || line[0] == '\0') return;

    if (history_count < HISTORY_SIZE) {
        history[history_count].numero = history_count + 1;
        my_strncpy(history[history_count].commande, line, 255);
        history[history_count].commande[255] = '\0';
        history_count++;
    } else {
        int i = 0;
        for (i = 0; i < HISTORY_SIZE - 1; i++) {
            history[i] = history[i + 1];
            history[i].numero = i + 1;
        }
        history[HISTORY_SIZE - 1].numero = HISTORY_SIZE;
        my_strncpy(history[HISTORY_SIZE - 1].commande, line, 255);
        history[HISTORY_SIZE - 1].commande[255] = '\0';
    }

    FILE *f = fopen(HISTORY_FILE, "w");
    if (f != NULL) {
        int i = 0;
        for (i = 0; i < history_count; i++) {
            fprintf(f, "%d %s\n", history[i].numero, history[i].commande);
        }
        fclose(f);
    }
}


void history_load(void) {
    history_count = 0;
    FILE *f = fopen(HISTORY_FILE, "r");
    if (f == NULL) return;

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), f) != NULL) {


        int len = 0;
        while (buffer[len] != '\0') len++;
        if (len > 0 && buffer[len-1] == '\n') buffer[len-1] = '\0';


        int i = 0;
        while (buffer[i] >= '0' && buffer[i] <= '9') i++;
        if (buffer[i] == ' ') i++;

        if (buffer[i] == '\0') continue;

        if (history_count < HISTORY_SIZE) {
            history[history_count].numero = history_count + 1;
            my_strncpy(history[history_count].commande, buffer + i, 255);
            history[history_count].commande[255] = '\0';
            history_count++;
        }
    }

    fclose(f);
}



int shell_history(char **args) {
    int nb = history_count;

    if (args[1] != NULL) {
        nb = atoi(args[1]);
        if (nb <= 0 || nb > history_count) {
            nb = history_count;
        }
    }

    int debut = history_count - nb;
    int i = debut;
    for (i = debut; i < history_count; i++) {
        printf("%4d  %s\n", history[i].numero, history[i].commande);
    }

    return 1;
}
