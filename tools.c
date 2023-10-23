//
// Created by mathi on 23/10/2023.
//
#include <stdio.h>

#include "tools.h"

char *lire_fichier_texte(char *path)
{
    FILE *fichier = fopen(path, "r");

    char *texte[2000];
    char c;
    int i = 0;

    while( (c = fgetc(fichier)) != EOF ) {
        *texte[i] = c;
        i++;
    };

    fclose(fichier);
    return texte;
}
