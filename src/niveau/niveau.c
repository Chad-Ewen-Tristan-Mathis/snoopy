#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
#include <unistd.h>

#include "niveau.h"
#include "../menu/menu.h"
#include "../tools/tools.h"

int niveau_existe(char *niveau) {
    char path[100];
    sprintf(path, "../assets/niveaux/%s.txt", niveau);
    return access(path, F_OK) != -1;
}

int affiche_unite(int indice, int unites_rouges) {
    if(indice < unites_rouges) {
        COULEUR(4, 0);
        wprintf(L"█");
        COULEUR(3, 0);
        return 1;
    } else {
        COULEUR(2, 0);
        wprintf(L"█");
        COULEUR(3, 0);
        return 0;
    }
}

struct Dimensions dimensions_niveau(int niveau) {
    char path[100];
    sprintf(path, "../assets/niveaux/%d.txt", niveau);

    FILE *fichier = fopen(path, "r");
    if(fichier == NULL) {
        perror("Impossible d'ouvrir le fichier");
    }

    char ligne[100];

    fgets(ligne, sizeof ligne, fichier);

    struct Dimensions dimensions;

    dimensions.largeur = strlen(ligne)-1;
    dimensions.hauteur = 1;

    while(fgets(ligne, sizeof ligne, fichier) != NULL) {
        dimensions.hauteur++;
    }

    return dimensions;
}

struct ModeleNiveau modele_niveau(char *id, int sauvegarde) {
    char path[100];
    if(sauvegarde) {
        sprintf(path, "../assets/sauvegardes/%s.txt", id);
    } else {
        sprintf(path, "../assets/niveaux/%s.txt", id);
        if(!niveau_existe(id)) {
            system("cls");
            wprintf(L"Votre partie est terminee !");
            sleep(3);
            system("cls");
            afficher_fichier("../assets/ASCII/logo.txt");
            menu();
        }
    }

    struct Coordonnees snoopy = {0, 0};
    struct Balle balle = {1, 1, 0}; // 0 = Sud Est, 1 = Sud Ouest, 2 = Nord Ouest, 3 = Nord Est
    struct Coordonnees *oiseaux = malloc(4 * sizeof(struct Coordonnees));

    int nb_oiseaux = 0;
    int nb_teleporteurs = 0;

    int temps_restant = 0;
    int niveau = atoi(id);
    int nb_vies = 3;
    int score = 0;
    int sous_case = 0;

    FILE *fichier = fopen(path, "r");
    if(fichier == NULL)
        perror("Impossible d'ouvrir le fichier");

    if(sauvegarde) {
        // TEMPS\n
        // NIVEAU\n
        // NB_VIES\n
        // SCORE\n

        char ligne[100];
        fgets(ligne, sizeof ligne, fichier);
        temps_restant = atoi(ligne);

        fgets(ligne, sizeof ligne, fichier);
        niveau = atoi(ligne);

        fgets(ligne, sizeof ligne, fichier);
        nb_vies = atoi(ligne);

        fgets(ligne, sizeof ligne, fichier);
        score = atoi(ligne);

        fgets(ligne, sizeof ligne, fichier);
        sous_case = atoi(ligne);

        fgets(ligne, sizeof ligne, fichier);
        balle.x = atoi(ligne);
        fgets(ligne, sizeof ligne, fichier);
        balle.y = atoi(ligne);
        fgets(ligne, sizeof ligne, fichier);
        balle.direction = atoi(ligne);

    } else id = (char *)time(NULL);

    struct Dimensions dimensions = dimensions_niveau(niveau);

    int **modele = malloc(dimensions.hauteur * sizeof(int *));

    for(int i = 0; i < dimensions.hauteur; i++) {
        modele[i] = malloc(dimensions.largeur * sizeof(int));
        for(int j = 0; j < dimensions.largeur; j++) {
            char c = fgetc(fichier);
            switch (c) {
                case '\n':
                    c = fgetc(fichier);
                    break;
                case '5':
                    modele[i][j] = 5;
                    nb_teleporteurs++;
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

    struct Coordonnees *teleporteurs = malloc(nb_teleporteurs * sizeof(struct Coordonnees));

    nb_teleporteurs = 0;
    for(int i = 1; i < dimensions.hauteur-1; i++)
        for(int j = 1; j < dimensions.largeur-1; j++)
            if(modele[i][j] == 5) teleporteurs[nb_teleporteurs++] = (struct Coordonnees) {j, i};

    char message[500];

    struct ModeleNiveau result = {
            id,
            modele,
            dimensions.hauteur,
            dimensions.largeur,
            niveau,
            temps_restant,
            nb_vies,
            nb_oiseaux,
            nb_teleporteurs,
            message,
            score,
            sous_case,
            snoopy,
            balle,
            oiseaux,
            teleporteurs
    };
    return result;
}

void afficher_niveau(struct ModeleNiveau modele, int temps_restant, char derniere_direction)
{
//    Affichage niveau + chrono
    float temps_restant_prct = (float)(temps_restant * 100) / (float)120;
    int unites_rouges = (modele.hauteur-1)*2+(modele.largeur-1)*2 - unite_chrono_restant(temps_restant_prct, modele.hauteur, modele.largeur);
    int indice_unite = 0;

    for(int k = 0; k < modele.largeur; k++) {
        int z = affiche_unite(indice_unite, unites_rouges);
        if(z) indice_unite++;
    }
    wprintf(L"\n");



    for(int i = 1; i < modele.hauteur-1; i++) {
        for(int j = 0; j < modele.largeur; j++) {
            if(j == 0) {
                affiche_unite(2*(modele.hauteur + modele.largeur - 2) - i, unites_rouges);
            } else if(j == modele.largeur-1) {
                int z = affiche_unite(indice_unite, unites_rouges);
                if(z) indice_unite++;
            } else {
                if(modele.balle.y == i && modele.balle.x == j) {
                    COULEUR(15, 0);
                    wprintf(L"●");
                    COULEUR(3, 0);
                } else switch(modele.modele[i][j]) {
                    case 0:
                        wprintf(L" ");
                        break;
                    case 1:
                        wprintf(L"▨");
                        break;
                    case 2:
                        wprintf(L"▢");
                        break;
                    case 3:
                        wprintf(L"▨");
                        break;
                    case 4:
                        wprintf(L"█");
                        break;
                    case 5:
                        wprintf(L"⏏");
                        break;
                    case 6:
                        wprintf(L"☰");
                        break;
                    case 8:
                        COULEUR(14, 0);
                        switch (derniere_direction) {
                            case 'z':
                                wprintf(L"▲");
                                break;
                            case 'q':
                                wprintf(L"◀");
                                break;
                            case 's':
                                wprintf(L"▼");
                                break;
                            case 'd':
                                wprintf(L"▶");
                                break;
                            default:
                                wprintf(L"X");
                                break;
                        }
                        COULEUR(3, 0);
                        break;
                    case 9:
                        COULEUR(5, 0);
                        wprintf(L"★");
                        COULEUR(3, 0);
                        break;
                }
            }
        }
        wprintf(L"\n");
    }
    for(int k = 0; k<modele.largeur; k++) {
        int z = affiche_unite(indice_unite+modele.largeur-k, unites_rouges);
        if(z) indice_unite++;
    }
    wprintf(L"\n");
}

int unite_chrono_restant(int prct_restant, int hauteur, int largeur) {
    int unites = (largeur-1)*2 + (hauteur-1)*2;
    return (unites * prct_restant) / 100;
}

int nombre_oiseaux(struct ModeleNiveau modele) {
    int nb_oiseaux = 0;
    for(int i = 0; i < modele.nb_oiseaux; i++) {
        if(modele.oiseaux[i].x != modele.largeur && modele.oiseaux[i].y != modele.hauteur) nb_oiseaux++;
    }

    return nb_oiseaux;
}