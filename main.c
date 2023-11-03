#include <stdio.h>
#include <unistd.h>

#include "src/menu/menu.h"
#include "src/tools/tools.h"
#include "src/niveau/niveau.h"
#include "src/chrono/chrono.h"

int main() {
    COULEUR(3, 0);
    afficher_fichier("../assets/logo.txt");

    struct ModeleNiveau modele = modele_niveau("../assets/niveaux/1.txt");

    int chrono = nouveau_chrono() - 100;
    while (temps_restant(chrono) > 0) {
        system("cls");
        afficher_niveau(modele, temps_restant(chrono));
        sleep(1);
    }
}