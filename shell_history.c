#define HISTORY_FILE ".myshell_history"





///////////////Historique////////////

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

    // écriture dans le fichier
    FILE *f = fopen(HISTORY_FILE, "a");
    if (f != NULL) {
        fprintf(f, "%d %s\n", history_count, line);
        fclose(f);
    }
}

void history_clear(void) {
    history_count = 0;
    // vide le fichier en l'écrasant
    FILE *f = fopen(HISTORY_FILE, "w");
    if (f != NULL) {
        fclose(f);
    }
}

int shell_history(char **args) {
  printf("\n");
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





