#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "menu.h"
#include "../tools/tools.h"
#include "../niveau/niveau.h"

void menu() {
    afficher_menu();
    int option = selectionne_option();
    switch (option) {
        case 1:
            afficher_regles();
            break;
        case 2:
            nouvelle_partie();
            break;
        case 3:
            charger_partie();
            break;
        case 4:
            charger_niveau();
            break;
        case 5:
            scores();
            break;
        default:
            quitter();
            break;
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
    afficher_fichier("../assets/regles.txt");
    menu();
}
void nouvelle_partie() {
    system("cls");
    afficher_fichier("../assets/nouvelle_partie.txt");
    lire_niveau("../assets/niveaux/1.txt");
}
void charger_partie() {}
void charger_niveau() {}
void scores() {}
void quitter() {
    afficher_fichier("../assets/quitter.txt");
    sleep(2000);
    exit(0);
}