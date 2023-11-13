#include "../niveau/niveau.h"

#ifndef SNOOPY_DEPLACEMENTS_H
#define SNOOPY_DEPLACEMENTS_H

void deplacer(struct ModeleNiveau *modele, char direction, char *derniere_direction, int *ancienne_case);
void casse_bloc(struct ModeleNiveau *modele, const char *direction);

#endif //SNOOPY_DEPLACEMENTS_H
