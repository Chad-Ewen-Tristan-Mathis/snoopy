#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "partie.h"
#include "../menu/menu.h"
#include "../niveau/niveau.h"
#include "../tools/tools.h"
#include "../chrono/chrono.h"
#include "../deplacements/commandes.h"

void nouvelle_partie(char *id) {
    system("cls");
    struct ModeleNiveau niveau = modele_niveau(id, 0);
    int temps_arrivee = nouveau_chrono();
    int pause = 0;
    int menu_principal = 0;

    while(temps_arrivee - (int) time(NULL) > 0 || pause != 0) {
        handleKeypress(&niveau, &temps_arrivee, &pause, &menu_principal);
        if(menu_principal == 1) break;
        if(pause != 0) continue;
        system("cls");
        afficher_niveau(niveau, temps_arrivee - (int) time(NULL));
        afficher_vies(niveau.vies_restantes);
        usleep(250000); // (0.25s)
    }
    system("cls");
    afficher_fichier("../assets/logo.txt");
    menu();
}

void afficher_vies(int vies) {
//    tableau de 3 fichiers
    FILE *fichiers[3];
    for(int i=0; i<vies; i++) fichiers[i] = fopen("../assets/coeur.txt", "r");

    char ligne[100];
    int fin = 0;
    while(!fin) {
        for(int i=0; i<vies; i++) {
            if(fgets(ligne, sizeof ligne, fichiers[i]) == NULL) {
                fin = 1;
                break;
            }
            if(ligne[strlen(ligne)-1] == '\n') ligne[strlen(ligne)-1] = '\0';
            for(int j=0; j< strlen(ligne); j++) ligne[j] = ligne[j] == 'x' ? ' ' : ligne[j];
            printf("%s", ligne);
            if(i == vies-1) printf("\n");
        }
    }

    printf("\n\n");

    for(int i=0; i<vies; i++) fclose(fichiers[i]);
}