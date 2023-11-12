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

int sauvegarde_id_valide(char *id) {
    char chemin[100];
    sprintf(chemin, "../assets/sauvegardes/%s.txt", id);

    return access(chemin, F_OK) != -1;
}

struct ModeleNiveau charger_sauvegarde(char *id, int code) {
    char nouvel_id[50];
    if(code == -1) {
        system("cls");
        afficher_fichier("../assets/charger_partie.txt");
        printf("Veuillez entrer l'id de la sauvegarde : \n");
        scanf("%s", nouvel_id);
        return charger_sauvegarde(nouvel_id, 0);
    } else if(code == -2) {
        printf("Sauvegarde invalide, Veuillez reessayer : \n");
        scanf("%s", nouvel_id);
        return charger_sauvegarde(nouvel_id, 0);
    } else {
        printf("Chargement de la sauvegarde \"%s\"\n", id);
        if(!sauvegarde_id_valide(id))
            return charger_sauvegarde(nouvel_id, -2);
        else {
            system("cls");
            struct ModeleNiveau sauvegarde = modele_niveau(id, 1);

            int temps_arrivee = nouveau_chrono() - 120 + sauvegarde.temps_restant;
            int pause = 0;
            int menu_principal = 0;

            while(temps_arrivee - (int) time(NULL) > 0 || pause != 0) {
                handleKeypress(&sauvegarde, &temps_arrivee, &pause, &menu_principal);
                if(menu_principal == 1) break;
                if(pause != 0) continue;
                system("cls");
                afficher_fichier("../assets/logo.txt");
                afficher_niveau(sauvegarde, temps_arrivee - (int) time(NULL));
                usleep(250000); // (0.25s)
            }
            system("cls");
            afficher_fichier("../assets/logo.txt");
            menu();
        }
    }
}

void sauvegarder_partie(struct ModeleNiveau modele, int temps_arrivee, int *menu_principal) {
    int pause_timestamp = (int) time(NULL);
    *menu_principal = 1;
    system("cls");
    char nom[50];
    printf("Veuillez entrer le nom de la sauvegarde :");
    scanf("%s", nom);

    char chemin[100];
    sprintf(chemin, "../assets/sauvegardes/%s.txt", nom);

    if(access(chemin, F_OK) != -1) {
        printf("Une sauvegarde avec ce nom existe deja, voulez vous l'ecraser ? (o/n)\n");
        char reponse;
        scanf("%c", &reponse);
        if(reponse == 'n') {
            sauvegarder_partie(modele, temps_arrivee, menu_principal);
            return;
        }
    }

    FILE *fichier = fopen(chemin, "w");
    fprintf(fichier, "%d\n", temps_arrivee - pause_timestamp);
    fprintf(fichier, "%d\n", modele.niveau);
    fprintf(fichier, "%d\n", modele.vies_restantes);
    fprintf(fichier, "%d", modele.score);
//    Ajout de la matrice
    for (int i = 0; i < modele.hauteur; i++) {
        fprintf(fichier, "\n");
        for (int j = 0; j < modele.largeur; j++) {
            fprintf(fichier, "%d", modele.modele[i][j]);
        }
    }
    fclose(fichier);
}