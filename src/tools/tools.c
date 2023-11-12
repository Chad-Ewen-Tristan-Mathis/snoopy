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
        wprintf(L"%c", c);
        c = fgetc(fichier);
    }
    wprintf(L"\n");
    fclose(fichier);
}

void COULEUR(int couleurDuTexte,int couleurDeFond)
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}
