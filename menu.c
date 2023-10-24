#include <stdio.h>
#include "menu.h"
#include "tools.h"

void afficher_menu() {
    afficher_fichier("../assets/menu.txt");
}
int selectionne_option() {
    afficher_menu();
    int option;
    scanf("%d", &option);
    return option;
}