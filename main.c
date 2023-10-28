#include <stdio.h>
#include <unistd.h>
#include <locale.h>
#include "menu.h"
#include "tools.h"
#include "niveau.h"

int main() {
    COULEUR(3, 0);
    afficher_fichier("../assets/logo.txt");
    menu();

    sleep(5000);
    return 0;
}