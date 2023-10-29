

#ifndef SNOOPY_NIVEAU_H
#define SNOOPY_NIVEAU_H

struct ModeleNiveau {
    int **modele;
    int largeur;
    int hauteur;
};

struct ModeleNiveau lire_niveau(char *path);
void afficher_niveau(struct ModeleNiveau modele);
struct ModeleNiveau modele_niveau(char *path);
int *dimensions_niveau(char *path);

#endif //SNOOPY_NIVEAU_H
