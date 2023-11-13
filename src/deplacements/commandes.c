#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <conio.h>

#include "commandes.h"
#include "../menu/menu.h"
#include "../chrono/chrono.h"
#include "deplacements.h"
#include "../niveau/niveau.h"
#include "../sauvegardes/sauvegardes.h"
#include "../tools/tools.h"

void handleKeypress(struct ModeleNiveau *modele, int *temps_arrivee, int *pause, int *menu_principal, char *derniere_direction) {
    if(kbhit()) {
        switch(getch()) {
            case 'p':
                if(*pause == 0) {
                    *pause = (int) time(NULL);
                    wprintf(L"Pause\n");
                } else {
                    *temps_arrivee += (int) time(NULL) - *pause;
                    *pause = 0;
                }
                break;
            case 's':
                ;int pause_timestamp = (int) time(NULL);
                *menu_principal = 1;
                system("cls");

                char *nom = demande_sauvegarde_id();
                char chemin[200];
                sprintf(chemin, "../assets/sauvegardes/%s.txt", nom);
                sauvegarder_partie(*modele, *temps_arrivee - pause_timestamp, chemin);
                break;
            case 'q': // Abandonner
                if(*pause != 0) break;
                *menu_principal = 1;
                break;
            case 'r': // Recommencer
                if(*pause != 0) break;
                if(modele->vies_restantes <= 1) {
                    system("cls");
                    wprintf(L"Vous n'avez plus qu'une vies restantes ! Vous ne pouvez donc pas réessayer\n");
                    sleep(1);
                    break;
                }
                *derniere_direction = ' ';
                int score = modele->score;
                int vies = --modele->vies_restantes;
                char niveau[10];
                sprintf(niveau, "%d", modele->niveau);
                *modele = modele_niveau(niveau, 0);
                *temps_arrivee = nouveau_chrono();
                modele->score = score;
                modele->vies_restantes = vies;
                system("cls");
                afficher_fichier("../assets/ASCII/recommence.txt");
                sleep(1);
            case 32: // Espace
                if(*pause != 0) break;
                casse_bloc(modele, derniere_direction);
                break;
            case 224:
                if(*pause != 0) break;
                switch (getch()) {
                    case 72: // Haut
                        deplacer(modele, 'z', derniere_direction);
                        break;
                    case 80: // Bas
                        deplacer(modele, 's', derniere_direction);
                        break;
                    case 75: // Gauche
                        deplacer(modele, 'q', derniere_direction);
                        break;
                    case 77: // Droite
                        deplacer(modele, 'd', derniere_direction);
                        break;
                }
                break;
        }
    }
}