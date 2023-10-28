//
// Created by mathi on 24/10/2023.
//
#include <stdio.h>
#include <string.h>
#include "niveau.h"
#include "tools.h"

void afficher_niveau(char *niveau) {
    char* tab[] = {"../assets/niveaux/", niveau, ".txt"};
    char* path = concat(tab, sizeof tab / sizeof tab[0]);

    afficher_fichier(path, 1);
}