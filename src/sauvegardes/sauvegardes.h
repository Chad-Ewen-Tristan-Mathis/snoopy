//
// Created by mathi on 06/11/2023.
//

#include "../niveau/niveau.h"

#ifndef SNOOPY_SAUVEGARDES_H
#define SNOOPY_SAUVEGARDES_H

int sauvegarde_id_valide(char *id);
struct ModeleNiveau charger_sauvegarde(char *id, int code);
void sauvegarder_partie(struct ModeleNiveau modele, int chrono, int *menu_principal);

#endif //SNOOPY_SAUVEGARDES_H