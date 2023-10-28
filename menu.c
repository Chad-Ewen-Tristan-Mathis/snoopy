#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "menu.h"
#include "tools.h"

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
    afficher_fichier("../assets/menu.txt", 0);
}
int selectionne_option() {
    int option;
    scanf("%d", &option);
    return option;
}

void afficher_regles() {
    system("cls");
    afficher_fichier("../assets/regles.txt", 0);
}
void nouvelle_partie() {}
void charger_partie() {}
void charger_niveau() {}
void scores() {}
void quitter() {
    afficher_fichier("../assets/quitter.txt", 0);
    sleep(2000);
    exit(0);
}