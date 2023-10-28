//
// Created by mathi on 23/10/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "tools.h"

void afficher_fichier(char *path, int isLevel)
{
    FILE *fichier = fopen(path, "r");
    char* characters[] = {
            "\x20",  // 0 (case vide)
            "\x2660", // 1 (bloc cassable, ♠)
            "\xE2\x86\x92", // 2 (bloc poussable, →)
            "\x2663", // 3 (bloc piégé, ♣)
            "\xE2\x98\xBC", // 4 (bloc invincible, ☼)
            "\xE2\x97\x99", // 5 (bloc disparition/apparition, ◙)
            "\xE2\x96\xAC", // 6 (bloc de tapis roulant, ▬)
            "\xE2\x98\xBA", // 7 (balle, ☺)
            "\xE2\x99\x82", // 8 (Snoopy, ♂)
            "\xE2\x99\xAB"  // 9 (oiseau, ♫)
    };
    if(fichier == NULL) {
        perror("Impossible d'ouvrir le fichier");
    }

    char c = fgetc(fichier);
    while( c != EOF ) {
        if(isLevel) {
            if(c == '\n') {
                printf("\n");
            } else {
                printf("%s", characters[c - '0']);
            }
        }
        else printf("%c", c);
        c = fgetc(fichier);
    };
    fclose(fichier);
}

char *concat(char* chaines[], int taille) {
    char *res = malloc(sizeof(char) * 1000);

    strcpy(res, chaines[0]);

    for (int i = 1; i < taille; i++) {
        strcat(res, chaines[i]);
    };
    return res;
}

void COULEUR(int couleurDuTexte,int couleurDeFond)
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}
