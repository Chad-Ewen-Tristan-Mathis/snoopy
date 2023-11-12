#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <io.h>

#include "src/menu/menu.h"
#include "src/tools/tools.h"
#include "src/niveau/niveau.h"
#include "src/chrono/chrono.h"
#include "src/sauvegardes/sauvegardes.h"


int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);
    COULEUR(3, 0);

    afficher_fichier("../assets/ASCII/logo.txt");

    menu();
}