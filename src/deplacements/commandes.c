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

void handleKeypress(struct ModeleNiveau *modele, int *chrono, int *pause, int *menu_principal) {
    if(kbhit()) {
        switch(getch()) {
            case 'p':
                if(*pause == 0) {
                    *pause = (int) time(NULL);
                    printf("Pause\n");
                } else {
                    *chrono += (int) time(NULL) - *pause;
                    *pause = 0;
                }
                break;
            case 's':
                sauvegarder_partie(*modele, *chrono, menu_principal);
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