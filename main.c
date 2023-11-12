#include <stdio.h>
#include <unistd.h>

#include "src/menu/menu.h"
#include "src/tools/tools.h"
#include "src/niveau/niveau.h"
#include "src/chrono/chrono.h"
#include "src/sauvegardes/sauvegardes.h"


int main() {
    COULEUR(3, 0);
    afficher_fichier("../assets/logo.txt");

    menu();
//    struct Sauvegarde sauvegarde = charger_sauvegarde(1);
//    Affichage du modele de la sauvegarde
    /*for(int i = 0; i < sauvegarde.hauteur; i++) {
        for(int j = 0; j < sauvegarde.largeur; j++) {
            printf("%d", sauvegarde.modele[i][j]);
        }
        printf("\n");
    }*/
}