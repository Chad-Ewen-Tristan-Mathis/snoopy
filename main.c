#include <stdio.h>
#include <unistd.h>

#include "src/menu/menu.h"
#include "src/tools/tools.h"
#include "src/niveau/niveau.h"
#include "src/chrono/chrono.h"


int main() {
    COULEUR(3, 0);
    afficher_fichier("../assets/logo.txt");

    menu();
}