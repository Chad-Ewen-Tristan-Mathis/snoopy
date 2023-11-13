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
void tapis_roulant(struct ModeleNiveau *modele, int x, int y, int direction, int *ancienne_case);

int getCaseValue(struct ModeleNiveau modele, int x, int y) {
    return modele.modele[y][x];
}

void deplacer(struct ModeleNiveau *modele, char direction, char *derniere_direction, int *ancienne_case) {
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
    int nouvelle_case = getCaseValue(*modele, modele->snoopy.x+add_x, modele->snoopy.y+add_y);
    if(nouvelle_case == 0 || nouvelle_case == 2 && pousse_bloc(modele, modele->snoopy.x+add_x, modele->snoopy.y+add_y, direction)) {
        modele->modele[modele->snoopy.y][modele->snoopy.x] = *ancienne_case;
        *ancienne_case = 0;
        modele->snoopy.y += add_y;
        modele->snoopy.x += add_x;
        *ancienne_case = modele->modele[modele->snoopy.y][modele->snoopy.x];
        modele->modele[modele->snoopy.y][modele->snoopy.x] = 8;
    } else if(nouvelle_case == 3) { // Bloc piégé
        // PIEGE
    } else if(nouvelle_case == 4) { // Bloc invincible
        // INVINCIBLE
    } else if(nouvelle_case == 5) { // Bloc apparition/disparition
        modele->modele[modele->snoopy.y][modele->snoopy.x] = *ancienne_case;
        *ancienne_case = 5;
        teleportation(modele, modele->snoopy.x+add_x, modele->snoopy.y+add_y);
    } else if(nouvelle_case == 6) { // Tapis roulant
        modele->modele[modele->snoopy.y][modele->snoopy.x] = *ancienne_case;
        *ancienne_case = 0;
        tapis_roulant(modele, modele->snoopy.x+add_x, modele->snoopy.y+add_y, direction, ancienne_case);
    } else if(nouvelle_case == 9) { // Oiseau
        modele->modele[modele->snoopy.y][modele->snoopy.x] = *ancienne_case;
        *ancienne_case = 0;
        modele->snoopy.y += add_y;
        modele->snoopy.x += add_x;
        modele->modele[modele->snoopy.y][modele->snoopy.x] = 8;
        *ancienne_case = 0;
        oiseau(modele);
    }
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
    if(nouvelle_case == 1) modele->modele[modele->snoopy.y+add_y][modele->snoopy.x+add_x] = 0;
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
    for(int i = 1; i < modele->hauteur-1; i++) {
        for(int j = 1; j < modele->largeur-1; j++) {
            if(modele->modele[i][j] == 7) {
                srand(time(NULL));
                struct Coordonnees tp_coord = modele->teleporteurs[rand() % (sizeof modele->teleporteurs / sizeof(struct Coordonnees))];
                modele->modele[y][x] = 0;
                modele->modele[tp_coord.y][tp_coord.x] = 8;
                modele->snoopy.x = tp_coord.x;
                modele->snoopy.y = tp_coord.y;
            }
        }
    }
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
void tapis_roulant(struct ModeleNiveau *modele, int x, int y, int direction, int *ancienne_case) {
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
        tapis_roulant(modele, x+add_x, y+add_y, direction, ancienne_case);
    } else if(nouvelle_case == 9) {
        modele->snoopy.y = y+add_y;
        modele->snoopy.x = x+add_x;
        modele->modele[modele->snoopy.y][modele->snoopy.x] = 8;
        *ancienne_case = 0;
        oiseau(modele);
    } else {
        modele->snoopy.y = y;
        modele->snoopy.x = x;
        *ancienne_case = modele->modele[modele->snoopy.y][modele->snoopy.x];
        modele->modele[modele->snoopy.y][modele->snoopy.x] = 8;
    }
}