#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "../menu/menu.h"
#include "../niveau/niveau.h"
#include "../tools/tools.h"
#include "../chrono/chrono.h"
#include "../deplacements/commandes.h"

void nouvelle_partie() {
    system("cls");
    struct ModeleNiveau niveau = modele_niveau("1", 0);
    int temps_arrivee = nouveau_chrono();
    int pause = 0;
    int menu_principal = 0;

    while(temps_arrivee - (int) time(NULL) > 0 || pause != 0) {
        handleKeypress(&niveau, &temps_arrivee, &pause, &menu_principal);
        if(menu_principal == 1) break;
        if(pause != 0) continue;
        system("cls");
        afficher_fichier("../assets/logo.txt");
        afficher_niveau(niveau, temps_arrivee - (int) time(NULL));
        usleep(250000); // (0.25s)
    }
    system("cls");
    afficher_fichier("../assets/logo.txt");
    menu();
}