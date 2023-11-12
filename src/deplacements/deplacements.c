#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#include "deplacements.h"
#include "commandes.h"
#include "../niveau/niveau.h"
#include "../tools/tools.h"

int pousse_bloc(struct ModeleNiveau *modele, int x, int y, int direction);
void teleportation(struct ModeleNiveau *modele, int x, int y);
void tapis_roulant(struct ModeleNiveau *modele, int x, int y, int direction);

int getCaseValue(struct ModeleNiveau modele, int x, int y) {
    return modele.modele[y][x];
}

void haut(struct ModeleNiveau *modele) {
    int nouvelle_case = getCaseValue(*modele, modele->snoopy.x, modele->snoopy.y - 1);
    if(nouvelle_case == 0 || nouvelle_case == 1 || nouvelle_case == 2 && pousse_bloc(modele, modele->snoopy.x, modele->snoopy.y-1, 'z')) {
        modele->modele[modele->snoopy.y][modele->snoopy.x] = 0;
        modele->modele[--modele->snoopy.y][modele->snoopy.x] = 8;
    } else if(nouvelle_case == 3) { // Bloc piégé
        // PIEGE
    } else if(nouvelle_case == 4) { // Bloc invincible
        // INVINCIBLE
    } else if(nouvelle_case == 5) { // Bloc apparition/disparition
        teleportation(modele, modele->snoopy.x, modele->snoopy.y-1);
    } else if(nouvelle_case == 6) { // Tapis roulant
        tapis_roulant(modele, modele->snoopy.x, modele->snoopy.y, 'z');
    }
}
void bas(struct ModeleNiveau *modele) {
    int nouvelle_case = getCaseValue(*modele, modele->snoopy.x, modele->snoopy.y + 1);
    if(nouvelle_case == 0 || nouvelle_case == 1 || nouvelle_case == 2 && pousse_bloc(modele, modele->snoopy.x, modele->snoopy.y+1, 's')) {
        modele->modele[modele->snoopy.y][modele->snoopy.x] = 0;
        modele->modele[++modele->snoopy.y][modele->snoopy.x] = 8;
    } else if(nouvelle_case == 3) { // Bloc piégé
        // PIEGE
    } else if(nouvelle_case == 4) { // Bloc invincible
        // INVINCIBLE
    } else if(nouvelle_case == 5) { // Bloc apparition/disparition
        teleportation(modele, modele->snoopy.x, modele->snoopy.y+1);
    } else if(nouvelle_case == 6) { // Tapis roulant
        tapis_roulant(modele, modele->snoopy.x, modele->snoopy.y, 's');
    }
}
void gauche(struct ModeleNiveau *modele) {
    int nouvelle_case = getCaseValue(*modele, modele->snoopy.x-1, modele->snoopy.y);
    if(nouvelle_case == 0 || nouvelle_case == 1 || nouvelle_case == 2 && pousse_bloc(modele, modele->snoopy.x-1, modele->snoopy.y, 'q')) {
        modele->modele[modele->snoopy.y][modele->snoopy.x] = 0;
        modele->modele[modele->snoopy.y][--modele->snoopy.x] = 8;
    } else if(nouvelle_case == 3) { // Bloc piégé
        // PIEGE
    } else if(nouvelle_case == 4) { // Bloc invincible
        // INVINCIBLE
    } else if(nouvelle_case == 5) { // Bloc apparition/disparition
        teleportation(modele, modele->snoopy.x-1, modele->snoopy.y);
    } else if(nouvelle_case == 6) { // Tapis roulant
        tapis_roulant(modele, modele->snoopy.x, modele->snoopy.y, 'q');
    }
}
void droite(struct ModeleNiveau *modele) {
    int nouvelle_case = getCaseValue(*modele, modele->snoopy.x+1, modele->snoopy.y);
    if(nouvelle_case == 0 || nouvelle_case == 1 || nouvelle_case == 2 && pousse_bloc(modele, modele->snoopy.x+1, modele->snoopy.y, 'd')) {
        modele->modele[modele->snoopy.y][modele->snoopy.x] = 0;
        modele->modele[modele->snoopy.y][++modele->snoopy.x] = 8;
    } else if(nouvelle_case == 3) { // Bloc piégé
        // PIEGE
    } else if(nouvelle_case == 4) { // Bloc invincible
        // INVINCIBLE
    } else if(nouvelle_case == 5) { // Bloc apparition/disparition
        teleportation(modele, modele->snoopy.x+1, modele->snoopy.y);
    } else if(nouvelle_case == 6) { // Tapis roulant
        tapis_roulant(modele, modele->snoopy.x, modele->snoopy.y, 'd');
    }
}

int pousse_bloc(struct ModeleNiveau *modele, int x, int y, int direction) {
    if(direction == 'z') {
        int nouvelle_case = getCaseValue(*modele, x, y - 1);
        if(nouvelle_case == 0 || nouvelle_case == 1 || (nouvelle_case == 2 && pousse_bloc(modele, x, y - 1, direction))) { // Case vide
            modele->modele[y-1][x] = 2;
            modele->modele[y][x] = 0;
            return 1;
        }
    } else if(direction == 'q') {
        int nouvelle_case = getCaseValue(*modele, x - 1, y);
        if(nouvelle_case == 0 || nouvelle_case == 1 || (nouvelle_case == 2 && pousse_bloc(modele, x - 1, y, direction))) { // Case vide
            modele->modele[y][x-1] = 2;
            modele->modele[y][x] = 0;
            return 1;
        }
    } else if(direction == 's') {
        int nouvelle_case = getCaseValue(*modele, x, y + 1);
        if(nouvelle_case == 0 || nouvelle_case == 1 || (nouvelle_case == 2 && pousse_bloc(modele, x, y + 1, direction))) { // Case vide
            modele->modele[y+1][x] = 2;
            modele->modele[y][x] = 0;
            return 1;
        }
    } else if(direction == 'd') {
        int nouvelle_case = getCaseValue(*modele, x + 1, y);
        if(nouvelle_case == 0 || nouvelle_case == 1 || (nouvelle_case == 2 && pousse_bloc(modele, x + 1, y, direction))) { // Case vide
            modele->modele[y][x+1] = 2;
            modele->modele[y][x] = 0;
            return 1;
        }
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
// TAPIS ROULANT A REVOIR
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
    if(nouvelle_case == 0) {
        modele->modele[y][x] = 0;
        modele->snoopy.y += add_y*2;
        modele->snoopy.x += add_x*2;
        modele->modele[modele->snoopy.y][modele->snoopy.x] = 8;
    } else if(nouvelle_case == 1) {
        modele->modele[modele->snoopy.y][modele->snoopy.x] = 0;
        modele->snoopy.y += add_y*2;
        modele->snoopy.x += add_x*2;
        modele->modele[modele->snoopy.y][modele->snoopy.x] = 8;
    } else if(nouvelle_case == 2 && pousse_bloc(modele, modele->snoopy.x + add_x, modele->snoopy.y + add_y, direction)) {
        modele->modele[modele->snoopy.y][modele->snoopy.x] = 0;
        modele->snoopy.y += add_y*2;
        modele->snoopy.x += add_x*2;
        modele->modele[modele->snoopy.y][modele->snoopy.x] = 8;
    } else if(nouvelle_case == 3) {
        // PIEGE
    } else if(nouvelle_case == 4) {
        // INVINCIBLE
    } else if(nouvelle_case == 5) {
        teleportation(modele, x+add_x, y+add_y);
    } else if(nouvelle_case == 6) {
        tapis_roulant(modele, x+add_x, y+add_y, direction);
    }
};