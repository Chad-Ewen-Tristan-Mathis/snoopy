#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <unistd.h>

#include "deplacements.h"
#include "commandes.h"
#include "../niveau/niveau.h"
#include "../tools/tools.h"

int pousse_bloc(struct ModeleNiveau *modele, int x, int y, int direction);
void teleportation(struct ModeleNiveau *modele, int x, int y);
void oiseau(struct ModeleNiveau *modele);
void tapis_roulant(struct ModeleNiveau *modele, int x, int y, int direction);

int getCaseValue(struct ModeleNiveau modele, int x, int y) {
    return modele.modele[y][x];
}

void deplacer(struct ModeleNiveau *modele, char direction, char *derniere_direction) {
    *derniere_direction = direction;
    int add_x = 0;
    int add_y = 0;
    switch (direction) {
        case 'z':
            add_y = -1;
            break;
        case 'q':
            add_x = -1;
            break;
        case 's':
            add_y = 1;
            break;
        case 'd':
            add_x = 1;
            break;
    }
    struct Coordonnees ancien_snoopy = (struct Coordonnees) { modele->snoopy.x, modele->snoopy.y };
    int nouvelle_case = getCaseValue(*modele, modele->snoopy.x+add_x, modele->snoopy.y+add_y);
    if(nouvelle_case == 0 || nouvelle_case == 2 && pousse_bloc(modele, modele->snoopy.x+add_x, modele->snoopy.y+add_y, direction)) {
        modele->modele[modele->snoopy.y][modele->snoopy.x] = modele->sous_case;
        modele->sous_case = 0;
        modele->snoopy.y += add_y;
        modele->snoopy.x += add_x;
        modele->sous_case = modele->modele[modele->snoopy.y][modele->snoopy.x];
        modele->modele[modele->snoopy.y][modele->snoopy.x] = 8;
    } else if(nouvelle_case == 5) { // Bloc apparition/disparition
        modele->modele[modele->snoopy.y][modele->snoopy.x] = modele->sous_case;
        modele->sous_case = 5;
        teleportation(modele, modele->snoopy.x+add_x, modele->snoopy.y+add_y);
    } else if(nouvelle_case == 6) { // Tapis roulant
        modele->modele[modele->snoopy.y][modele->snoopy.x] = modele->sous_case;
        modele->sous_case = 0;
        tapis_roulant(modele, modele->snoopy.x+add_x, modele->snoopy.y+add_y, direction);
    } else if(nouvelle_case == 9) { // Oiseau
        modele->modele[modele->snoopy.y][modele->snoopy.x] = modele->sous_case;
        modele->sous_case = 0;
        modele->snoopy.y += add_y;
        modele->snoopy.x += add_x;
        modele->modele[modele->snoopy.y][modele->snoopy.x] = 8;
        modele->sous_case = 0;
        oiseau(modele);
    }
    if((modele->snoopy.x != ancien_snoopy.x || modele->snoopy.y != ancien_snoopy.y) && modele->balle.x == modele->snoopy.x && modele->balle.y == modele->snoopy.y) {
        modele->vies_restantes--;
        modele->message = "La balle vous a touche, vous avez perdu une vie !";
    }
}
void deplacer_balle(struct ModeleNiveau *modele) {
    int add_x = 0;
    int add_y = 0;
    if(modele->balle.y == modele->hauteur-2 && modele->balle.direction <= 1) {
        modele->balle.direction = modele->balle.direction == 0 ? 3 : 2;
        return deplacer_balle(modele);
    }
    if(modele->balle.y == 1 && modele->balle.direction > 1) {
        modele->balle.direction = modele->balle.direction == 2 ? 1 : 0;
        return deplacer_balle(modele);
    }
    if(modele->balle.x == modele->largeur-2 && modele->balle.direction%3 == 0) {
        modele->balle.direction = modele->balle.direction == 3 ? 2 : 1;
        return deplacer_balle(modele);
    }
    if(modele->balle.x == 1  && modele->balle.direction%3 != 0) {
        modele->balle.direction = modele->balle.direction == 1 ? 0 : 3;
        return deplacer_balle(modele);
    }
    switch (modele->balle.direction) {
        case 0: // Sud Est
            add_y = 1;
            add_x = 1;
            break;
        case 1: // Sud Ouest
            add_y = 1;
            add_x = -1;
            break;
        case 2: // Nord Ouest
            add_y = -1;
            add_x = -1;
            break;
        case 3: // Nord Est
            add_y = -1;
            add_x = 1;
            break;
    }
    modele->balle.y += add_y;
    modele->balle.x += add_x;
}

void casse_bloc(struct ModeleNiveau *modele, const char *direction) {
    int add_x = 0;
    int add_y = 0;
    switch (*direction) {
        case 'z':
            add_y = -1;
            break;
        case 'q':
            add_x = -1;
            break;
        case 's':
            add_y = 1;
            break;
        case 'd':
            add_x = 1;
            break;
    }
    int nouvelle_case = getCaseValue(*modele, modele->snoopy.x+add_x, modele->snoopy.y+add_y);
    if(nouvelle_case == 1 || nouvelle_case == 3) modele->modele[modele->snoopy.y+add_y][modele->snoopy.x+add_x] = 0;
    if(nouvelle_case == 3) {
        modele->vies_restantes--;
        modele->message = "Vous avez casse un bloc piege... Vous venez de perdre une vie !";
    }
}
int pousse_bloc(struct ModeleNiveau *modele, int x, int y, int direction) {
    int add_x = 0;
    int add_y = 0;
    switch (direction) {
        case 'z':
            add_y = -1;
            break;
        case 'q':
            add_x = -1;
            break;
        case 's':
            add_y = 1;
            break;
        case 'd':
            add_x = 1;
            break;
    }

    int nouvelle_case = getCaseValue(*modele, x+add_x, y+add_y);
    if(nouvelle_case == 0 || (nouvelle_case == 2 && pousse_bloc(modele, x+add_x, y+add_y, direction))) {
        modele->modele[y+add_y][x+add_x] = 4;
        modele->modele[y][x] = 0;
        return 1;
    }

    return 0;
}
void teleportation(struct ModeleNiveau *modele, int x, int y) {
    if(modele->nb_teleporteurs == 0) return;
    srand(time(NULL));
    struct Coordonnees tp_coord;
    do {
        tp_coord = modele->teleporteurs[rand() % modele->nb_teleporteurs];
    } while (tp_coord.x == x && tp_coord.y == y);
    modele->snoopy.x = tp_coord.x;
    modele->snoopy.y = tp_coord.y;
    modele->modele[modele->snoopy.y][modele->snoopy.x] = 8;
}
void oiseau(struct ModeleNiveau *modele) {
    for(int i = 0; i < modele->nb_oiseaux; i++) {
        struct Coordonnees oiseau = modele->oiseaux[i];
        if(oiseau.x == modele->snoopy.x && oiseau.y == modele->snoopy.y) {
            modele->oiseaux[i].x = modele->largeur;
            modele->oiseaux[i].y = modele->hauteur;
        }
    }
}
void tapis_roulant(struct ModeleNiveau *modele, int x, int y, int direction) {
    int add_x = 0;
    int add_y = 0;
    switch (direction) {
        case 'z':
            add_y = -1;
            break;
        case 'q':
            add_x = -1;
            break;
        case 's':
            add_y = 1;
            break;
        case 'd':
            add_x = 1;
            break;
    }
    int nouvelle_case = getCaseValue(*modele, x+add_x, y+add_y);

    if(nouvelle_case == 0 || (nouvelle_case == 2 && pousse_bloc(modele, x+add_x, y+add_y, direction))) {
        modele->snoopy.y = y+add_y;
        modele->snoopy.x = x+add_x;
        modele->modele[modele->snoopy.y][modele->snoopy.x] = 8;
    } else if(nouvelle_case == 5) {
        teleportation(modele, x+add_x, y+add_y);
    } else if(nouvelle_case == 6) {
        tapis_roulant(modele, x+add_x, y+add_y, direction);
    } else if(nouvelle_case == 9) {
        modele->snoopy.y = y+add_y;
        modele->snoopy.x = x+add_x;
        modele->modele[modele->snoopy.y][modele->snoopy.x] = 8;
        modele->sous_case = 0;
        oiseau(modele);
    } else {
        modele->snoopy.y = y;
        modele->snoopy.x = x;
        modele->sous_case = modele->modele[modele->snoopy.y][modele->snoopy.x];
        modele->modele[modele->snoopy.y][modele->snoopy.x] = 8;
    }
}