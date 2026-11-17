#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* --- Définitions --- */
#define NB_PORTS 5
#define PORT_BLOQUE 0
#define PORT_ACTIF 1

typedef struct {
    const char *nom;
    int id;
    int etat;
    const char *sysfs_lock;
    const char *sysfs_unlock;
    const char *module_cmd; 
} t_port;


t_port ports[NB_PORTS] = {
    {
        "USB", 0, PORT_ACTIF,
        "echo 0 | tee /sys/bus/usb/devices/*/authorized > /dev/null 2>&1",
        "echo 1 | tee /sys/bus/usb/devices/*/authorized > /dev/null 2>&1",
        "modprobe -r usb_storage usbhid"
    },
    {
        "RJ45 (Ethernet)", 1, PORT_ACTIF,
        "ip link set down $(ip -o link show | awk -F': ' '{print $2}' | grep -E '^(eth|en)') 2>/dev/null",
        "ip link set up $(ip -o link show | awk -F': ' '{print $2}' | grep -E '^(eth|en)') 2>/dev/null",
        "modprobe -r e1000e r8169 igb"
    },
    {
        "HDMI / DisplayPort", 2, PORT_ACTIF,
        "echo off | tee /sys/class/drm/card*-HDMI-*/status > /dev/null 2>&1 ; echo off | tee /sys/class/drm/card*-DP-*/status > /dev/null 2>&1",
        "echo on | tee /sys/class/drm/card*-HDMI-*/status > /dev/null 2>&1 ; echo on | tee /sys/class/drm/card*-DP-*/status > /dev/null 2>&1",
        ""
    },
    {
        "Audio", 3, PORT_ACTIF,
        "echo auto | tee /sys/bus/pci/devices/*/power/control > /dev/null 2>&1",
        "echo on | tee /sys/bus/pci/devices/*/power/control > /dev/null 2>&1",
        "modprobe -r snd_hda_intel snd_usb_audio"
    },
    {
        "Bluetooth", 4, PORT_ACTIF,
        "echo 1 | tee /sys/class/rfkill/rfkill*/state > /dev/null 2>&1",
        "echo 0 | tee /sys/class/rfkill/rfkill*/state > /dev/null 2>&1",
        "modprobe -r btusb bluetooth"
    }
};

/* --- Fonctions Internes --- */


static int my_local_strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++; s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

static int executer_commande(const char *cmd) {
    if (cmd == NULL || cmd[0] == '\0') return 0;
    return system(cmd); 
}

/* --- Logique de Contrôle --- */

int port_bloquer(int index) {
    if (index < 0 || index >= NB_PORTS) return -1;

    char msg[128];
    int n = snprintf(msg, sizeof(msg), "  [LOCK] %s...\n", ports[index].nom);
    write(STDOUT_FILENO, msg, n);

    executer_commande(ports[index].sysfs_lock);
    executer_commande(ports[index].module_cmd);

    ports[index].etat = PORT_BLOQUE;
    return 0;
}

int port_debloquer(int index) {
    if (index < 0 || index >= NB_PORTS) return -1;

    /* 1. Recharge les modules (Inversion de modprobe -r) */
    if (ports[index].module_cmd != NULL && ports[index].module_cmd[0] != '\0') {
        const char *prefix = "modprobe -r ";
        size_t prefix_len = strlen(prefix);

        if (strncmp(ports[index].module_cmd, prefix, prefix_len) == 0) {
            char modules[256] = {0};
            strncpy(modules, ports[index].module_cmd + prefix_len, sizeof(modules) - 1);

            char *token = strtok(modules, " ");
            while (token != NULL) {
                char cmd_reload[128];
                snprintf(cmd_reload, sizeof(cmd_reload), "modprobe %s", token);
                executer_commande(cmd_reload);
                token = strtok(NULL, " ");
            }
        }
    }

    /* 2. Restaure l'état matériel via sysfs_unlock */
    executer_commande(ports[index].sysfs_unlock);

    char msg[128];
    int n = snprintf(msg, sizeof(msg), "  [UNLOCK] %s restaure\n", ports[index].nom);
    write(STDOUT_FILENO, msg, n);

    ports[index].etat = PORT_ACTIF;
    return 0;
}

void port_afficher_etat(void) {
    const char *header = "\nPORT                         ETAT\n------------------------------------------\n";
    write(STDOUT_FILENO, header, strlen(header));

    for (int i = 0; i < NB_PORTS; i++) {
        char ligne[128];
        const char *statut = (ports[i].etat == PORT_BLOQUE) ? "[ BLOQUE ]" : "[  ACTIF ]";
        int n = snprintf(ligne, sizeof(ligne), "  %-26s %s\n", ports[i].nom, statut);
        write(STDOUT_FILENO, ligne, n);
    }
}

void shell_secure_ports(void) {
    const char *banniere = "------------------------------------------\n"
                           "|   SECURISATION DES PORTS PHYSIQUES     |\n"
                           "------------------------------------------\n";
    write(STDOUT_FILENO, banniere, strlen(banniere));

    for (int i = 0; i < NB_PORTS; i++) {
        port_bloquer(i);
    }
}

int shell_portctl(char **args) {
    if (args[1] == NULL) {
        const char *usage = "Usage : portctl <commande> [port]\n"
                            "  status           affiche l'etat des ports\n"
                            "  lock   <nom|all> bloque un port\n"
                            "  unlock <nom|all> restaure un port\n";
        write(STDOUT_FILENO, usage, strlen(usage));
        return 1;
    }

    if (my_local_strcmp(args[1], "status") == 0) {
        port_afficher_etat();
        return 1;
    }

    int lock = -1;
    if (my_local_strcmp(args[1], "lock") == 0) lock = 1;
    else if (my_local_strcmp(args[1], "unlock") == 0) lock = 0;

    if (lock == -1) {
        write(STDOUT_FILENO, "portctl : commande inconnue\n", 28);
        return 1;
    }

    if (args[2] == NULL) {
        write(STDOUT_FILENO, "portctl : precisez un port ou 'all'\n", 36);
        return 1;
    }

    if (my_local_strcmp(args[2], "all") == 0) {
        for (int i = 0; i < NB_PORTS; i++) {
            if (lock) port_bloquer(i); else port_debloquer(i);
        }
        return 1;
    }

    static const char *noms_clef[] = {"usb", "reseau", "hdmi", "audio", "bluetooth"};
    for (int i = 0; i < NB_PORTS; i++) {
        if (my_local_strcmp(args[2], (char *)noms_clef[i]) == 0) {
            if (lock) port_bloquer(i); else port_debloquer(i);
            return 1;
        }
    }

    write(STDOUT_FILENO, "portctl : port inconnu\n", 23);
    return 1;
}
