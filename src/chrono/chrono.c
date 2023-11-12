#include <time.h>
#include "chrono.h"

int nouveau_chrono() {
//    120s en plus du temps actuel
    return (int)time(NULL) + 120;
}