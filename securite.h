#ifndef SECURITE_H_INCLUDED
#define SECURITE_H_INCLUDED

#include <unistd.h>   /* write(), STDOUT_FILENO */
#include <stdlib.h>   /* system()               */

/* ─── États possibles d'un port ─────────────────────────────────────── */
#define PORT_BLOQUE  0
#define PORT_ACTIF   1

/* ─── Catégories de ports ───────────────────────────────────────────── */
#define PORT_USB       0
#define PORT_RESEAU    1
#define PORT_HDMI      2
#define PORT_AUDIO     3
#define PORT_BLUETOOTH 4

#define NB_PORTS 5

/* ─── Structure décrivant un port physique ──────────────────────────── */
typedef struct {
    char nom[32];           /* Nom affiché à l'utilisateur              */
    int  categorie;         /* Constante PORT_xxx                       */
    int  etat;              /* PORT_BLOQUE ou PORT_ACTIF                */
    char sysfs_cmd[256];    /* Commande sysfs de désactivation          */
    char module_cmd[128];   /* Commande modprobe de déchargement        */
} t_port;

/* ─── Table globale des ports ───────────────────────────────────────── */
extern t_port ports[NB_PORTS];

/* ─── Fonctions publiques ───────────────────────────────────────────── */
void shell_secure_ports(void);          /* Appelée au démarrage         */
int  shell_portctl(char **args);        /* Builtin "portctl"            */
void port_afficher_etat(void);          /* Affiche le tableau d'état    */
int  port_bloquer(int index);           /* Bloque un port par index     */
int  port_debloquer(int index);         /* Débloque un port par index   */

#endif /* SECURITE_H_INCLUDED */
