#ifndef SNOOPY_TOOLS_H
#define SNOOPY_TOOLS_H

struct Coordonnees {
    int x;
    int y;
};

void afficher_fichier(char *path);
char *concat(char* chaines[], int taille);
void COULEUR(int couleurDuTexte,int couleurDeFond);

#endif //SNOOPY_TOOLS_H
