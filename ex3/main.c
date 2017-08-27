#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include "batalha_naval.h"

/* variveis globais, constantes e definições */

/*
Direção Horizontal = 1
Direção Vertical = 0
*/

/*
Barcos:

2x Corveta: ##

2x Submarino: ###

2x Fragata: ##
            ##

1x Destroyer: ####

1x Cruzador: #####

1x Porta-Aviões: ######
                 ######
*/

int main () {
    FILE* arquivoRanking = NULL;

    arquivoRanking = fopen("ranking.txt", "a");

    if (arquivoRanking == NULL) {
        printf("Não foi possível abrir o arquivo de ranking!\n");
    }
    else {
        fclose(arquivoRanking);
        menuPrincipal();
    }

    return 0;
}