#include <stdio.h>
#include <unistd.h>
#include "menu.h"
#include "tools.h"
#include "niveau.h"

int main() {
    COULEUR(3, 0);
    lire_niveau("../assets/niveaux/1.txt");

    sleep(5000);
    return 0;
}