#include "commun.h"
#include "commande.h"

char *my_strcpy(char *dest, const char *src)
{
int i = 0;
while (src[i] != '\0') {
 dest[i] = src[i];
  i++;
}
dest[i] = '\0';
    return dest;
}


char *my_strdup(const char *s) {
    int i = 0;
    char *dup;

    while (s[i])
        i++;

    dup = (char *)malloc(sizeof(char) * (i + 1));
    if (!dup)
        return NULL;

    i = 0;
    while (s[i]) {
        dup[i] = s[i];
        i++;
    }
    dup[i] = '\0';
    return dup;
}

int my_strcmp(char s1[], char s2[])
{
    int i = 0;
    while (s1[i] == s2[i] && s1[i] != '\0')
    {
        i++;
    }
    return s1[i] - s2[i];
}

char *my_strconcat(char *dest, const char *src) {
int i = 0;
int j = 0;

while(dest[i] != '\0'){
    i++;
}

while(src[j] != '\0'){
    dest[i] = src[j];
    i++;
    j++;
}

dest[i] = '\0';
return dest;
}

char * my_strncpy(char *dest, const char *src, unsigned int n) {
    unsigned int i = 0;
    while (i < n && src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    while (i < n) {
        dest[i] = '\0';
        i++;
    }
    return dest;
}

int my_strncmp(const char *s1, const char *s2, int n) {
    int i = 0;
    while (i < n && s1[i] && s2[i]) {
        if (s1[i] != s2[i]) {
            return (unsigned char)s1[i] - (unsigned char)s2[i];
        }
        i++;
    }
    if (i == n) {
        return 0;
    }
    return (unsigned char)s1[i] - (unsigned char)s2[i];
}

int my_strlen(char *buffer){

int i =0;
for( i =0; buffer[i] != '\0'; i++) {}
return i;
}
