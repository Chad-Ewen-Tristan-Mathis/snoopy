//
// Created by mathi on 23/10/2023.
//
#include <stdio.h>

#include "tools.h"

void afficher_fichier(char *path)
{
    FILE *fichier = fopen(path, "r");

    if(fichier == NULL) {
        perror("Impossible d'ouvrir le fichier");
    }

    char c = fgetc(fichier);
    while( c != EOF ) {
        printf("%c", c);
        c = fgetc(fichier);
    };
    fclose(fichier);
}
