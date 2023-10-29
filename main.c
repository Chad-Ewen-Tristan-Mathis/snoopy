#include <stdio.h>
#include <unistd.h>

#include "src/menu/menu.h"
#include "src/tools/tools.h"
#include "src/niveau/niveau.h"

int main() {
    COULEUR(3, 0);
    afficher_fichier("../assets/logo.txt");
    menu();

    sleep(5000);
    return 0;
}