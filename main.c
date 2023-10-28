#include <stdio.h>
#include <unistd.h>
#include "menu.h"
#include "tools.h"
#include "niveau.h"

int main() {
    COULEUR(3, 0);
    afficher_niveau("1");
    sleep(5000);
    return 0;
}
