#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <conio.h>

#include "commandes.h"
#include "../menu/menu.h"
#include "deplacements.h"
#include "../niveau/niveau.h"
#include "../sauvegardes/sauvegardes.h"
#include "../tools/tools.h"

void handleKeypress(struct ModeleNiveau *modele, int *temps_arrivee, int *pause, int *menu_principal) {
    if(kbhit()) {
        switch(getch()) {
            case 'p':
                if(*pause == 0) {
                    *pause = (int) time(NULL);
                    printf("Pause\n");
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
                sauvegarder_partie(*modele, *temps_arrivee - pause_timestamp, nom);
                break;
            case 224:
                if(*pause != 0) break;
                switch (getch()) {
                    case 72: // Haut
                        deplacer(modele, 'z');
                        break;
                    case 80: // Bas
                        deplacer(modele, 's');
                        break;
                    case 75: // Gauche
                        deplacer(modele, 'q');
                        break;
                    case 77: // Droite
                        deplacer(modele, 'd');
                        break;
                }
                break;
        }
    }
}