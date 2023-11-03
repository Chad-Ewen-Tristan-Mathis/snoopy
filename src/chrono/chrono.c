#include <time.h>
#include "chrono.h"

int nouveau_chrono() {
//    120s en plus du temps actuel
    return time(NULL) + 120;
}
int temps_restant(int chrono) {
    return chrono - time(NULL);
}