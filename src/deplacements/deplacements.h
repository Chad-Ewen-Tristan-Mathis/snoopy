#include "../niveau/niveau.h"

#ifndef SNOOPY_DEPLACEMENTS_H
#define SNOOPY_DEPLACEMENTS_H

void deplacer(struct ModeleNiveau *modele, char direction, char *derniere_direction);
void casse_bloc(struct ModeleNiveau *modele, char *direction);

#endif //SNOOPY_DEPLACEMENTS_H
