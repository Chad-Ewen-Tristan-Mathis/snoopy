#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include <unistd.h>
#include "string.h"
#include "sauvegardes.h"
#include "../niveau/niveau.h"
#include "../chrono/chrono.h"
#include "../menu/menu.h"
#include "../deplacements/commandes.h"
#include "../partie/partie.h"

int sauvegarde_id_valide(char *id) {
    char chemin[100];
    sprintf(chemin, "../assets/sauvegardes/%s.txt", id);

    return access(chemin, F_OK) != -1;
}

struct ModeleNiveau charger_sauvegarde(char *id, int code) {
    char nouvel_id[50];
    if(code == -1) {
        system("cls");
        afficher_fichier("../assets/ASCII/charger_partie.txt");
        wprintf(L"Veuillez entrer l'id de la sauvegarde : \n");
        scanf("%s", nouvel_id);
        return charger_sauvegarde(nouvel_id, 0);
    } else if(code == -2) {
        wprintf(L"Sauvegarde invalide, Veuillez reessayer : \n");
        scanf("%s", nouvel_id);
        return charger_sauvegarde(nouvel_id, 0);
    } else {
        wprintf(L"Chargement de la sauvegarde \"%s\"\n", id);
        if(!sauvegarde_id_valide(id))
            return charger_sauvegarde(nouvel_id, -2);
        else {
            struct ModeleNiveau sauvegarde = modele_niveau(id, 1);
            jeu(sauvegarde);
        }
    }
}


void sauvegarder_partie(struct ModeleNiveau modele, int temps_restant, char* chemin) {
    FILE *fichier = fopen(chemin, "w");
    fprintf(fichier, "%d\n", temps_restant);
    fprintf(fichier, "%d\n", modele.niveau);
    fprintf(fichier, "%d\n", modele.vies_restantes);
    fprintf(fichier, "%d\n", modele.score);
    fprintf(fichier, "%d\n", modele.sous_case);
    fprintf(fichier, "%d\n", modele.balle.x);
    fprintf(fichier, "%d\n", modele.balle.y);
    fprintf(fichier, "%d", modele.balle.direction);
//    Ajout de la matrice
    for (int i = 0; i < modele.hauteur; i++) {
        fprintf(fichier, "\n");
        for (int j = 0; j < modele.largeur; j++) {
            fprintf(fichier, "%d", modele.modele[i][j]);
        }
    }
    fclose(fichier);
}

char *demande_sauvegarde_id() {
    char *nom = malloc(50 * sizeof(char));
    wprintf(L"Veuillez entrer le nom de la sauvegarde :");
    scanf("%s", nom);

    char chemin[100];
    sprintf(chemin, "../assets/sauvegardes/%s.txt", nom);

    if(access(chemin, F_OK) != -1) {
        wprintf(L"Une sauvegarde avec ce nom existe deja, voulez vous l'ecraser ? (o/n)\n");
        char reponse;
        scanf("%c", &reponse);
        if(reponse == 'n') return demande_sauvegarde_id();
    }

    return nom;
}