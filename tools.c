//
// Created by mathi on 23/10/2023.
//
#include <stdio.h>

#include "tools.h"

void afficher_fichier(char *path)
{
    FILE *fichier = fopen(path, "r");

    char c;
    printf("Lecture fichier %s", path);
    while( (c = fgetc(fichier)) != EOF ) {
        printf("%c", c);
    };
    fclose(fichier);
}
