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

    while((temps_arrivee - (int) time(NULL) > 0 || pause != 0) && nombre_oiseaux(modele) > 0) {
        handleKeypress(&modele, &temps_arrivee, &pause, &menu_principal);
        if(menu_principal == 1) break;
        if(pause != 0) continue;
        system("cls");
        afficher_niveau(modele, temps_arrivee - (int) time(NULL));
        afficher_vies(modele.vies_restantes);
        usleep(250000); // (0.25s)
    }
    if(menu_principal == 1) {
        system("cls");
        afficher_fichier("../assets/logo.txt");
        menu();
    } else if(nombre_oiseaux(modele) <= 0) {
        int temps_restant = temps_arrivee - (int) time(NULL);
        float temps_restant_prct = (float)(temps_restant * 100) / (float)120;
        modele.score += temps_restant*100;
        system("cls");
        afficher_fichier("../assets/victoire.txt");
        printf("\n\nScore du niveau %d : %d\n", modele.niveau, temps_restant*100);
        printf("Temps restant : %d (%.2f%%)\n", temps_restant, temps_restant_prct);
        printf("Nombre de vies restantes : %d\n", modele.vies_restantes);
        printf("Score total : %d\n", modele.score);
        printf("Appuyez sur une touche pour continuer...\n");
        sleep(1);
        while(!kbhit());

        int score = modele.score;
        int vies = modele.vies_restantes;
        char nouveau_niveau[10];
        sprintf(nouveau_niveau, "%d", modele.niveau+1);
        modele = modele_niveau(nouveau_niveau, 0);
        modele.score = score;
        modele.vies_restantes = vies;

        char *chemin = "../assets/sauvegardes/sauvegarde_temporaire.txt";

        sauvegarder_partie(modele, 120, chemin);
        charger_sauvegarde("sauvegarde_temporaire", 0);
    }
}

void afficher_vies(int vies) {
//    tableau de 3 fichiers
    FILE *fichiers[3];
    for(int i=0; i<vies; i++) fichiers[i] = fopen("../assets/coeur.txt", "r");

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
            printf("%s", ligne);
            if(i == vies-1) printf("\n");
        }
    }

    printf("\n\n");

    for(int i=0; i<vies; i++) fclose(fichiers[i]);
}