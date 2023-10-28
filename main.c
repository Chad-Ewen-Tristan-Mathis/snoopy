#include <stdio.h>
#include <unistd.h>
#include <locale.h>
#include "menu/menu.h"
#include "tools/tools.h"
#include "niveau/niveau.h"

int main() {
    COULEUR(3, 0);
    afficher_fichier("../assets/logo.txt");
    menu();

    sleep(5000);
    return 0;
}