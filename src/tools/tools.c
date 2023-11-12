//
// Created by mathi on 23/10/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

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
    }
    printf("\n");
    fclose(fichier);
}

void COULEUR(int couleurDuTexte,int couleurDeFond)
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}
