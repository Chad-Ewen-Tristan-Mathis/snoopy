#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../niveau/niveau.h"
#include "../tools/tools.h"
#include "../chrono/chrono.h"

char* NIVEAUX[3] = {
        "../assets/niveaux/1.txt",
        "../assets/niveaux/2.txt",
        "../assets/niveaux/3.txt"
};

void nouvelle_partie() {
    system("cls");
    struct ModeleNiveau niveau = modele_niveau(NIVEAUX[0]);
    int chrono = nouveau_chrono();
    
    while (temps_restant(chrono) > 0) {
        system("cls");
        afficher_fichier("../assets/logo.txt");
        afficher_niveau(niveau, temps_restant(chrono));
        sleep(1);
    }
}