#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "menu.h"
#include "../tools/tools.h"
#include "../niveau/niveau.h"
#include "../partie/partie.h"
#include "../sauvegardes/sauvegardes.h"

void menu() {
    afficher_menu();
    int option = selectionne_option();
    switch (option) {
        case 1:
            afficher_regles();
            break;
        case 2:
            nouvelle_partie("1");
            break;
        case 3:
            charger_sauvegarde("", -1);
            break;
        case 4:
            ;char id[10];
            wprintf(L"Quel niveau voulez-vous charger ?\n");
            scanf("%s", id);
            nouvelle_partie(id);
            break;
        case 5:
            scores();
            break;
        case 6:
            quitter();
            break;
        default:
            system("cls");
            menu();
    }
};
void afficher_menu() {
    afficher_fichier("../assets/menu.txt");
}
int selectionne_option() {
    int option;
    scanf("%d", &option);

    return option;
}

void afficher_regles() {
    system("cls");
    afficher_fichier("../assets/ASCII/regles.txt");
    menu();
}

void charger_niveau() {}
void scores() {}
void quitter() {
    afficher_fichier("../assets/ASCII/quitter.txt");
    sleep(1);
    exit(0);
}