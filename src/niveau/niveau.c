//
// Created by mathi on 24/10/2023.
//
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "niveau.h"
#include "../tools/tools.h"


int affiche_unite(int indice, int unites_rouges) {
    if(indice < unites_rouges) {
        COULEUR(4, 0);
        printf("#");
        COULEUR(3, 0);
        return 1;
    } else {
        COULEUR(2, 0);
        printf("#");
        COULEUR(3, 0);
        return 0;
    }
}

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

    struct Coordonnees snoopy = {0, 0};
    struct Coordonnees *oiseaux = malloc(4 * sizeof(struct Coordonnees));
    int nb_oiseaux = 0;

    FILE *fichier = fopen(path, "r");
    if(fichier == NULL) {
        perror("Impossible d'ouvrir le fichier");
    }
    for(int i = 0; i < dimensions[1]; i++) {
        modele[i] = malloc(dimensions[0] * sizeof(int));
        for(int j = 0; j < dimensions[0]; j++) {
            char c = fgetc(fichier);
            switch (c) {
                case '\n':
                    c = fgetc(fichier);
                    break;
                case '8':
                    snoopy.x = j;
                    snoopy.y = i;
                    break;
                case '9':
                    oiseaux[nb_oiseaux].x = j;
                    oiseaux[nb_oiseaux].y = i;
                    nb_oiseaux++;
                    break;
            }
            modele[i][j] = (c-'0');
        }
    }

    struct ModeleNiveau result = {modele, dimensions[0], dimensions[1], snoopy, oiseaux};
    return result;
}

void afficher_niveau(struct ModeleNiveau modele, int temps_restant)
{
//    Affichage niveau + chrono
    float temps_restant_prct = (float)(temps_restant * 100) / (float)120;
    int unites_rouges = (modele.hauteur-1)*2+(modele.largeur-1)*2 - unite_chrono_restant(temps_restant_prct, modele.hauteur, modele.largeur);
    int indice_unite = 0;

    for(int k = 0; k < modele.largeur; k++) {
        int z = affiche_unite(indice_unite, unites_rouges);
        if(z) indice_unite++;
    }
    printf("\n");



    for(int i = 1; i < modele.hauteur-1; i++) {
        for(int j = 0; j < modele.largeur; j++) {
            if(j == 0) {
                affiche_unite(2*(modele.hauteur + modele.largeur - 2) - i, unites_rouges);
            } else if(j == modele.largeur-1) {
                int z = affiche_unite(indice_unite, unites_rouges);
                if(z) indice_unite++;
            } else {
                char symboles[10] = {
                        ' ', '~', '+', '~', '#', '@', '=', 'O', 'X', '^'
                };
                printf("%c", symboles[modele.modele[i][j]]);
            }
        }
        printf("\n");
    }
    for(int k = 0; k<modele.largeur; k++) {
        int z = affiche_unite(indice_unite+modele.largeur-k, unites_rouges);
        if(z) indice_unite++;
    }
    printf("\n");
}

int unite_chrono_restant(int prct_restant, int hauteur, int largeur) {
    int unites = (largeur-1)*2 + (hauteur-1)*2;
    return (unites * prct_restant) / 100;
}

