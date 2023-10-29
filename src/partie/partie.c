#include <stdio.h>
#include <stdlib.h>

#include "../niveau/niveau.h"
#include "../tools/tools.h"

char* NIVEAUX[3] = {
        "../assets/niveaux/1.txt",
        "../assets/niveaux/2.txt",
        "../assets/niveaux/3.txt"
};

void nouvelle_partie() {
    system("cls");
    struct ModeleNiveau niveau = lire_niveau(NIVEAUX[0]);

};