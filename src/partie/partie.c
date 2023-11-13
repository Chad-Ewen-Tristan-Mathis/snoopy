#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <conio.h>

#include "partie.h"
#include "../menu/menu.h"
#include "../niveau/niveau.h"
#include "../tools/tools.h"
#include "../chrono/chrono.h"
#include "../deplacements/commandes.h"
#include "../sauvegardes/sauvegardes.h"

void nouvelle_partie(char *id) {
    jeu(modele_niveau(id, 0));
}

void jeu(struct ModeleNiveau modele) {
    system("cls");
    int temps_arrivee = nouveau_chrono();
    int pause = 0;
    int menu_principal = 0;

    int ancienne_case = 0;
    char derniere_direction = ' ';
    while((temps_arrivee - (int) time(NULL) > 0 || pause != 0) && nombre_oiseaux(modele) > 0) {
        handleKeypress(&modele, &temps_arrivee, &pause, &menu_principal, &derniere_direction, &ancienne_case);
        if(menu_principal == 1) break;
        if(pause != 0) continue;
        system("cls");
        afficher_niveau(modele, temps_arrivee - (int) time(NULL), derniere_direction);
        afficher_vies(modele.vies_restantes);
        usleep(250000); // (0.25s)
    }
    if(menu_principal == 1) {
        system("cls");
        afficher_fichier("../assets/ASCII/logo.txt");
        menu();
    } else if(nombre_oiseaux(modele) <= 0) {
        int temps_restant = temps_arrivee - (int) time(NULL);
        float temps_restant_prct = (float)(temps_restant * 100) / (float)120;
        modele.score += temps_restant*100;
        system("cls");
        afficher_fichier("../assets/ASCII/victoire.txt");
        wprintf(L"\n\nScore du niveau %d : %d\n", modele.niveau, temps_restant*100);
        wprintf(L"Temps restant : %d (%.2f%%)\n", temps_restant, temps_restant_prct);
        wprintf(L"Nombre de vies restantes : %d\n", modele.vies_restantes);
        wprintf(L"Score total : %d\n", modele.score);
        wprintf(L"Appuyez sur une touche pour continuer...\n");
        sleep(1);
        while(!kbhit()) usleep(250000);

        int score = modele.score;
        int vies = modele.vies_restantes;
        char nouveau_niveau[10];
        sprintf(nouveau_niveau, "%d", modele.niveau+1);

        modele = modele_niveau(nouveau_niveau, 0);
        modele.score = score;
        modele.vies_restantes = vies;

        sauvegarder_partie(modele, 120, "../assets/sauvegardes/sauvegarde_temporaire.txt");
        charger_sauvegarde("sauvegarde_temporaire", 0);
    } else if(temps_arrivee - (int) time(NULL) <= 0) {
        system("cls");
        afficher_fichier("../assets/ASCII/defaite.txt");
        wprintf(L"\n\nNombre de vies restantes : %d\n", --modele.vies_restantes);
        wprintf(L"Score total : %d\n", modele.score);

        if(modele.vies_restantes <= 0) {
            wprintf(L"Appuyez sur une touche pour retourner au menu principal...\n");
            sleep(1);
            while(!kbhit());
            system("cls");
            afficher_fichier("../assets/ASCII/logo.txt");
            menu();
            return;
        }

        wprintf(L"Appuyez sur une touche pour ressayer le niveau...\n");
        sleep(1);
        while(!kbhit());

        int score = modele.score;
        int vies = modele.vies_restantes;
        char nouveau_niveau[10];
        sprintf(nouveau_niveau, "%d", modele.niveau);
        modele = modele_niveau(nouveau_niveau, 0);
        modele.score = score;
        modele.vies_restantes = vies;

        sauvegarder_partie(modele, 120, "../assets/sauvegardes/sauvegarde_temporaire.txt");
        charger_sauvegarde("sauvegarde_temporaire", 0);
    }
}

void afficher_vies(int vies) {
//    tableau de 3 fichiers
    FILE *fichiers[3];
    for(int i=0; i<vies; i++) fichiers[i] = fopen("../assets/ASCII/coeur.txt", "r");

    char ligne[100];
    int fin = 0;
    while(!fin) {
        for(int i=0; i<vies; i++) {
            if(fgets(ligne, sizeof ligne, fichiers[i]) == NULL) {
                fin = 1;
                break;
            }
            if(ligne[strlen(ligne)-1] == '\n') ligne[strlen(ligne)-1] = '\0';
            for(int j=0; j< strlen(ligne); j++) ligne[j] = ligne[j] == 'x' ? ' ' : ligne[j];
            wprintf(L"%s", ligne);
            if(i == vies-1) wprintf(L"\n");
        }
    }

    wprintf(L"\n\n");

    for(int i=0; i<vies; i++) fclose(fichiers[i]);
}