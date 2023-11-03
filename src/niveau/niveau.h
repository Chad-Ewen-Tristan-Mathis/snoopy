#include "../tools/tools.h"

#ifndef SNOOPY_NIVEAU_H
#define SNOOPY_NIVEAU_H

struct ModeleNiveau {
    int **modele;
    int largeur;
    int hauteur;
    struct Coordonnees snoopy;
    struct Coordonnees *oiseaux;
};

void afficher_niveau(struct ModeleNiveau modele, int temps_restant);
struct ModeleNiveau modele_niveau(char *path);
int *dimensions_niveau(char *path);

int unite_chrono_restant(int prct_restant, int hauteur, int largeur);

#endif //SNOOPY_NIVEAU_H
