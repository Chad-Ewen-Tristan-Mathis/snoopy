//
// Created by mathi on 24/10/2023.
//
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "niveau.h"
#include "../tools/tools.h"

int *dimensions_niveau(char *path) {
    FILE *fichier = fopen(path, "r");
    if(fichier == NULL) {
        perror("Impossible d'ouvrir le fichier");
    }

    char ligne[100];
    int *dimensions = malloc(2 * sizeof(int));

    fgets(ligne, sizeof ligne, fichier);
    dimensions[0] = strlen(ligne)-1;
    dimensions[1] = 1;

    while(fgets(ligne, sizeof ligne, fichier) != NULL) {
        dimensions[1]++;
    }

    return dimensions;
}

struct ModeleNiveau modele_niveau(char *path) {
    int *dimensions = dimensions_niveau(path);

    int **modele = malloc(dimensions[1] * sizeof(int *));

    FILE *fichier = fopen(path, "r");
    if(fichier == NULL) {
        perror("Impossible d'ouvrir le fichier");
    }
    for(int i = 0; i < dimensions[1]; i++) {
        modele[i] = malloc(dimensions[0] * sizeof(int));
        for(int j = 0; j < dimensions[0]; j++) {
            char c = fgetc(fichier);
            if(c == '\n') {
                c = fgetc(fichier);
            }
            modele[i][j] = (c-'0');
        }
    }

    struct ModeleNiveau result = {modele, dimensions[0], dimensions[1]};
    return result;
}

void afficher_niveau(struct ModeleNiveau modele)
{
    for(int i = 0; i < modele.hauteur; i++) {
        for(int j = 0; j < modele.largeur; j++) {
            switch(modele.modele[i][j]) {
                case 0:
                    printf(" ");
                    break;
                case 1:
                    printf("%c", 176);
                    break;
                case 4:
                    printf("%c", 219);
                    break;
                default:
                    printf("%d", modele.modele[i][j]);
                    break;
            }
        }
        printf("\n");
    }
}

struct ModeleNiveau lire_niveau(char *path) {
    struct ModeleNiveau modele = modele_niveau(path);
    afficher_niveau(modele);
    return modele;
}