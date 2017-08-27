#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "batalha_naval.h"
#define MAX 15
#define VAZIO '.'
#define CHEIO '#'
#define TIRO 'x'
#define DESTRUIDO '@'

struct Barco {
    int corveta;
    int submarino;
    int fragata;
    int destroyer;
    int cruzador;
    int portaAvioes;
};

typedef struct Barco barco;

barco qt_barcos = {2, 2, 2, 1, 1, 1};
barco qt_barcos_cpu = {2, 2, 2, 1, 1, 1};

char tabuleiro1[MAX][MAX];
char tabuleiro2[MAX][MAX];
char tabuleiro3[MAX][MAX];
int coordH[MAX] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14};
int coordV[MAX] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14};

char nome_jogador1[15] = "JOGADOR 1";
char nome_jogador2[15] = "CPU";
char jogar_denovo = 'n';

int contadorDeBarcos = 9;
int contadorDeBarcosCpu = 9;

int pontuacao_jogador = 0;
int contador_de_jogadas = 0;
int primeira_jogada = 1;

int vidas_jogador = 39;
int vidas_cpu = 39;

int cpu_acertou = 0;
int jogador_acertou = 0;

int fim_do_jogo = 0;
int jogador_venceu = 0;
int cpu_venceu = 0;

void imprimeBarcos();
int verificaBarcos();

void limpaTela () {
#ifdef __WIN32__
system("CLS");
#else
//printf("\e[H\e[2J");
    system("clear");
#endif
};

void limpaBuffer () {
#ifdef __WIN32__
    fflush(stdin);
#else
    __fpurge(stdin);
#endif
}

void iniciaTabuleiro() {
    int i, j;

    for (i = 0 ; i < MAX ; i++) {
        for (j = 0 ; j < MAX ; j++) {
            tabuleiro1[i][j] = VAZIO;
            tabuleiro2[i][j] = VAZIO;
            tabuleiro3[i][j] = VAZIO;
        }
    }
}

void imprimeOpcoesDeBarcos () {
    if (qt_barcos.corveta > 0) {
        printf("\t       1. Corveta....... (%d/2)\n", qt_barcos.corveta);
    }

    if (qt_barcos.submarino > 0) {
        printf("\t       2. Submarino..... (%d/2)\n", qt_barcos.submarino);
    }

    if (qt_barcos.fragata > 0) {
        printf("\t       3. Fragata....... (%d/2)\n", qt_barcos.fragata);
    }

    if (qt_barcos.destroyer > 0) {
        printf("\t       4. Destroyer..... (%d/1)\n", qt_barcos.destroyer);
    }

    if (qt_barcos.cruzador > 0) {
        printf("\t       5. Cruzador...... (%d/1)\n", qt_barcos.cruzador);
    }

    if (qt_barcos.portaAvioes > 0) {
        printf("\t       6. Porta-Aviões.. (%d/1)\n", qt_barcos.portaAvioes);
    }

    printf("\n");
}

void imprimeTabuleiro () {
    int i, j;

    printf("\n\n");
    printf("\t       NOME: %10s               ENERGIA: %2d/39", nome_jogador1, vidas_jogador);
    printf("\t        NOME: %s                      ENERGIA: %2d/39\n", nome_jogador2, vidas_cpu);

    printf("\t       ---------------------------------------------");
    printf("            ---------------------------------------------\n");

    printf("\t         |");
    for (i = 0 ; i < MAX - 1 ; i++) {
        printf("%3d", coordH[i]);
    }
    printf("              |");
    for (i = 0 ; i < MAX - 1 ; i++) {
        printf("%3d", coordH[i]);
    }

    printf("\n\t       --+------------------------------------------");
    printf("            --+------------------------------------------\n");

    for (i = 1 ; i < MAX ; i++) {
        printf("\t       %2d|", coordV[i-1]);
        for (j = 1 ; j < MAX ; j++) {
            printf("  %c", tabuleiro1[i][j]);
        }
        printf("         ");
        printf("   %2d|", coordV[i-1]);
        for (j = 1 ; j < MAX ; j++) {
            printf("  %c", tabuleiro3[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

int verificaDestroyer(int direcao, int linha, int coluna, char M[MAX][MAX]){
    int i, j;

    if(direcao){
        for(j = coluna ; j <= coluna + 4 ; j++){
            if(j >= MAX || M[linha][j] == CHEIO){
                return 0;
            }
        }
    }
    else{
        for(i = linha ; i <= linha + 4 ; i++){
            if(i >= MAX || M[i][coluna] == CHEIO){
                return 0;
            }
        }
    }
    return 1;
}

void imprimeDestroyer (int direcao, int linha, int coluna, char M[MAX][MAX]) {
    int i, j;

    if (direcao) {
        for (j = coluna ; j < coluna + 4 ; j++) {
            M[linha][j] = CHEIO;
        }
    }
    else {
        for (i = linha ; i < linha + 4 ; i++) {
            M[i][coluna] = CHEIO;
        }
    }

    if (M == tabuleiro1) {
        qt_barcos.destroyer--;
    }
    else {
        qt_barcos_cpu.destroyer--;
    }
}

int verificaCruzador(int direcao, int linha, int coluna, char M[MAX][MAX]){
    int i, j;

    if(direcao){
        for(j = coluna ; j <= coluna + 5 ; j++){
            if(j >= MAX || M[linha][j] == CHEIO){
                return 0;
            }
        }
    }
    else{
        for(i = linha ; i <= linha + 5 ; i++){
            if(i >= MAX || M[i][coluna] == CHEIO){
                return 0;
            }
        }
    }
    return 1;
}

void imprimeCruzador (int direcao, int linha, int coluna, char M[MAX][MAX]) {
    int i, j;

    if (direcao) {
        for (j = coluna ; j < coluna + 5 ; j++) {
            M[linha][j] = CHEIO;
        }
    }
    else {
        for (i = linha ; i < linha + 5 ; i++) {
            M[i][coluna] = CHEIO;
        }
    }

    if (M == tabuleiro1) {
        qt_barcos.cruzador--;
    }
    else {
        qt_barcos_cpu.cruzador--;
    }
}

int verificaPortaAvioes (int direcao, int linha, int coluna, char M[MAX][MAX]){
    int i, j;

    if (direcao) {
        for (i = linha ; i < linha + 2 ; i++) {
            for (j = coluna ; j < coluna + 6 ; j++) {
                if (i >= MAX || j >= MAX || M[i][j] == CHEIO) {
                    return 0;
                }
            }
        }
    }
    else {
        for (i = linha ; i < linha + 6 ; i++) {
            for (j = coluna ; j < coluna + 2 ; j++) {
                if (i >= MAX || j >= MAX || M[i][j] == CHEIO) {
                    return 0;
                }
            }
        }
    }
    return 1;
}

void imprimePortaAvioes (int direcao, int linha, int coluna, char M[MAX][MAX]) {
    int i, j;

    if (direcao) {
        for (i = linha ; i < linha + 2 ; i++) {
            for (j = coluna ; j < coluna + 6 ; j++) {
                M[i][j] = CHEIO;
            }
        }
    }
    else {
        for (i = linha ; i < linha + 6 ; i++) {
            for (j = coluna ; j < coluna + 2 ; j++) {
                M[i][j] = CHEIO;
            }
        }
    }

    if (M == tabuleiro1) {
        qt_barcos.portaAvioes--;
    }
    else {
        qt_barcos_cpu.portaAvioes--;
    }
}

int verificaFragata (int linha, int coluna, char M[MAX][MAX]){
    int i, j;

    for (i = linha ; i < linha + 2 ; i++) {
        for (j = coluna ; j < coluna + 2 ; j++) {
            if (i >= MAX || j >= MAX || M[i][j] == CHEIO) {
                return 0;
            }
        }
    }
    return 1;
}

void imprimeFragata (int linha, int coluna, char M[MAX][MAX]) {
    int i, j;

    for (i = linha ; i < linha + 2 ; i++) {
        for (j = coluna ; j < coluna + 2 ; j++) {
            M[i][j] = CHEIO;
        }
    }

    if (M == tabuleiro1) {
        qt_barcos.fragata--;
    }
    else {
        qt_barcos_cpu.fragata--;
    }
}

int verificaCorveta (int direcao, int linha, int coluna, char M[MAX][MAX]) {
    int i, j;

    if (direcao) {
        for (j = coluna ; j < coluna + 2 ; j++) {
            if (j >= MAX || M[linha][j] == CHEIO) {
                return 0;
            }
        }
    }
    else {
        for (i = linha ; i < linha + 2 ; i++) {
            if (i >= MAX || M[i][coluna] == CHEIO) {
                return 0;
            }
        }
    }
    return 1;
}

void imprimeCorveta (int direcao, int linha, int coluna, char M[MAX][MAX]) {
    int i, j;

    if (direcao) {
        for (j = coluna ; j < coluna + 2 ; j++) {
            M[linha][j] = CHEIO;
        }
    }
    else {
        for (i = linha ; i < linha + 2 ; i++) {
            M[i][coluna] = CHEIO;
        }
    }

    if (M == tabuleiro1) {
        qt_barcos.corveta--;
    }
    else {
        qt_barcos_cpu.corveta--;
    }
}

int verificaSubmarino(int direcao, int linha, int coluna, char M[MAX][MAX]){
    int i, j;

    if(direcao){
        for(j = coluna ; j <= coluna + 3 ; j++){
            if(j >= MAX || M[linha][j] == CHEIO){
                return 0;
            }
        }
    }
    else{
        for(i = linha ; i <= linha + 3 ; i++){
            if(i >= MAX || M[i][coluna] == CHEIO){
                return 0;
            }
        }
    }
    return 1;
}

void imprimeSubmarino (int direcao, int linha, int coluna, char M[MAX][MAX]) {
    int i, j;

    if (direcao) {
        for (j = coluna ; j < coluna + 3 ; j++) {
            M[linha][j] = CHEIO;
        }
    }
    else {
        for (i = linha ; i < linha + 3 ; i++) {
            M[i][coluna] = CHEIO;
        }
    }

    if (M == tabuleiro1) {
        qt_barcos.submarino--;
    }
    else {
        qt_barcos_cpu.submarino--;
    }
}

int haBarcos (int barco, char M[MAX][MAX]) {
    switch (barco) {
        case 1:
            if (M == tabuleiro1) {
                if (qt_barcos.corveta == 0) {
                    return 0;
                }
            }
            else {
                if (qt_barcos_cpu.corveta == 0) {
                    return 0;
                }
            }
            break;
        case 2:
            if (M == tabuleiro1) {
                if (qt_barcos.submarino == 0) {
                    return 0;
                }
            }
            else {
                if (qt_barcos_cpu.submarino == 0) {
                    return 0;
                }
            }
            break;
        case 3:
            if (M == tabuleiro1) {
                if (qt_barcos.fragata == 0) {
                    return 0;
                }
            }
            else {
                if (qt_barcos_cpu.fragata == 0) {
                    return 0;
                }
            }
            break;
        case 4:
            if (M == tabuleiro1) {
                if (qt_barcos.destroyer == 0) {
                    return 0;
                }
            }
            else {
                if (qt_barcos_cpu.destroyer == 0) {
                    return 0;
                }
            }
            break;
        case 5:
            if (M == tabuleiro1) {
                if (qt_barcos.cruzador == 0) {
                    return 0;
                }
            }
            else {
                if (qt_barcos_cpu.cruzador == 0) {
                    return 0;
                }
            }
            break;
        case 6:
            if (M == tabuleiro1) {
                if (qt_barcos.portaAvioes == 0) {
                    return 0;
                }
            }
            else {
                if (qt_barcos_cpu.portaAvioes == 0) {
                    return 0;
                }
            }
            break;
    }
    return 1;
}

void colheDados (char M[MAX][MAX]) {
    int barco, linha, coluna, direcao = 0;
    char op;

    do {
        imprimeOpcoesDeBarcos();
        printf("\t       Barco: ");
        limpaBuffer();
        scanf("%d", &barco);
        while (barco <= 0 || barco > 6 || !haBarcos(barco, M)) {
            printf("\t       Opção inválida! Digite um barco válido: ");
            limpaBuffer();
            scanf("%d", &barco);
        }

        if (barco != 3) {
            printf("\t       Direção [h/v]: ");
            limpaBuffer();
            scanf("%c", &op);
            while (tolower(op) != 'h' && tolower(op) != 'v') {
                printf("\t       Opção inválida! Digite outra direção [h/v]: ");
                limpaBuffer();
                scanf("%c", &op);
            }

            (tolower(op) == 'h') ? (direcao = 1) : (direcao = 0) ;
        }

        printf("\t       Linha: ");
        limpaBuffer();
        scanf("%d", &linha);
        while (linha >= MAX || linha <= 0) {
            printf("\t       Opção inválida! Digite uma linha válida: ");
            limpaBuffer();
            scanf("%d", &linha);
        }

        printf("\t       Coluna: ");
        limpaBuffer();
        scanf("%d", &coluna);
        while (coluna >= MAX || coluna <= 0) {
            printf("\t       Opção inválida! Digite uma coluna válida: ");
            limpaBuffer();
            scanf("%d", &coluna);
        }

        if (verificaBarcos(barco, direcao, linha, coluna, M)) {
            imprimeBarcos(barco, direcao, linha, coluna, M);
            limpaTela();
            imprimeTabuleiro();
            contadorDeBarcos--;
            printf("\t       > Barco inserido com sucesso!\n\n");
        }
        else {
            limpaTela();
            imprimeTabuleiro();
            printf("\t       > Erro ao inserir o barco! Tente Novamente!\n\n");
        }
    } while (contadorDeBarcos);
}

void colheDadosCpu (char M[MAX][MAX]) {
    int barco, linha, coluna, direcao = 0;

    srand((unsigned)time(NULL));

    do {
        barco = (rand() % 6) + 1;
        while (!haBarcos(barco, M)) {
            barco = (rand() % 6) + 1;
        }

        linha = (rand() % 14) + 1;

        coluna = (rand() % 14) + 1;

        direcao = rand() % 2;

        if (verificaBarcos(barco, direcao, linha, coluna, M)) {
            imprimeBarcos(barco, direcao, linha, coluna, M);
            contadorDeBarcosCpu--;
        }
    } while (contadorDeBarcosCpu);
}

int verificaBarcos (int barco, int direcao, int linha, int coluna, char M[MAX][MAX]) {
    switch (barco) {
        case 1:
            return verificaCorveta(direcao, linha, coluna, M);
        case 2:
            return verificaSubmarino(direcao, linha, coluna, M);
        case 3:
            return verificaFragata(linha, coluna, M);
        case 4:
            return verificaDestroyer(direcao, linha, coluna, M);
        case 5:
            return verificaCruzador(direcao, linha, coluna, M);
        case 6:
            return verificaPortaAvioes(direcao, linha, coluna, M);
    }
    return 0;
}

void imprimeBarcos (int barco, int direcao, int linha, int coluna, char M[MAX][MAX]) {
    switch (barco) {
        case 1:
            imprimeCorveta(direcao, linha, coluna, M);
            break;
        case 2:
            imprimeSubmarino(direcao, linha, coluna, M);
            break;
        case 3:
            imprimeFragata(linha, coluna, M);
            break;
        case 4:
            imprimeDestroyer(direcao, linha, coluna, M);
            break;
        case 5:
            imprimeCruzador(direcao, linha, coluna, M);
            break;
        case 6:
            imprimePortaAvioes(direcao, linha, coluna, M);
            break;
    }
}

int verificaJogada (int linha, int coluna, char M[MAX][MAX]) {
    if (M[linha][coluna] == TIRO || M[linha][coluna] == DESTRUIDO) {
        return 0;
    }
    return 1;
}

int atira (int linha, int coluna, char M[MAX][MAX]) {
    if (M == tabuleiro2) {
        if (M[linha][coluna] == VAZIO) {
            M[linha][coluna] = TIRO;
            tabuleiro3[linha][coluna] = TIRO;
            return 0;
        }
        else {
            M[linha][coluna] = DESTRUIDO;
            tabuleiro3[linha][coluna] = DESTRUIDO;
            pontuacao_jogador += 100;
            vidas_cpu--;
            return 1;
        }
    }
    else {
        if (M[linha][coluna] == VAZIO) {
            M[linha][coluna] = TIRO;
            return 0;
        }
        else {
            M[linha][coluna] = DESTRUIDO;
            vidas_jogador--;
            return 1;
        }
    }
}

void turnoDoJogador () {
    int linha, coluna, jogada_ok = 0;

    limpaTela();
    imprimeTabuleiro();

    do {

        if (!primeira_jogada) {
            printf("\t       > Jogador: ");
            (jogador_acertou) ? (printf("ALVO ATINGIDO!!!\n")) : (printf("ÁGUA!!!\n"));
            printf("\t       > CPU: ");
            (cpu_acertou) ? (printf("VOCÊ FOI ATINGIDO!!!\n")) : (printf("ÁGUA!!!\n"));
            printf("\t       ---------------------------------------------\n");
        }
        else {
            primeira_jogada = 0;
        }

        printf("\t       > Sua vez!\n\n");

        printf("\t       Linha: ");
        limpaBuffer();
        scanf("%d", &linha);
        while (linha <= 0 || linha >= 15) {
            printf("\t       Digite uma linha válida!: ");
            limpaBuffer();
            scanf("%d", &linha);
        }

        printf("\t       Coluna: ");
        limpaBuffer();
        scanf("%d", &coluna);
        while (coluna <= 0 || coluna >= 15) {
            printf("\t       Digite uma coluna válida!: ");
            limpaBuffer();
            scanf("%d", &coluna);
        }

        if (verificaJogada(linha, coluna, tabuleiro2)) {
            if (atira(linha, coluna, tabuleiro2)) {
                limpaTela();
                imprimeTabuleiro();
                jogador_acertou = 1;
            }
            else {
                limpaTela();
                imprimeTabuleiro();
                jogador_acertou = 0;
            }
            jogada_ok = 1;
        }
        else {
            limpaTela();
            imprimeTabuleiro();
            printf("\t       > Jogada inválida! Faça outra jogada:\n\n");
            jogada_ok = 0;
        }

    } while (!jogada_ok);
}

void turnoDaCpu () {
    int linha, coluna, jogada_ok = 0;

    srand((unsigned)time(NULL));

    do {
        linha = (rand() % 14) + 1;

        coluna = (rand() % 14) + 1;

        if (verificaJogada(linha, coluna, tabuleiro1)) {
            if (atira(linha, coluna, tabuleiro1)) {
                cpu_acertou = 1;
            }
            else {
                cpu_acertou = 0;
            }
            jogada_ok = 1;
        }
        else {
            jogada_ok = 0;
        }
    } while (!jogada_ok);
}

void verificaFimDeJogo () {
    if (vidas_jogador == 0 || vidas_cpu == 0) {
        fim_do_jogo = 1;
        if (vidas_cpu == 0) {
            jogador_venceu = 1;
        }
        else {
            cpu_venceu = 1;
        }
    }
}

void escreveNoRanking () {
    FILE* arquivoRanking = NULL;

    arquivoRanking = fopen("ranking.txt", "a");

    if (arquivoRanking == NULL) {
        printf("\t\t\t\t> Erro ao escrever no ranking!\n");
    }
    else {
        fprintf(arquivoRanking, "%d %s\n", pontuacao_jogador, nome_jogador1);
    }

    fclose(arquivoRanking);
}

void organizarRanking() {
    int i, j, cont = 0, aux;
    char url[] = "ranking.txt", nomes[35][15], auxNome[15];
    int pontos[35];
    FILE* arquivoRanking;

    arquivoRanking = fopen(url, "r");

    if(arquivoRanking == NULL){
        printf("ERRO: NAO FOI POSSIVEL ABRIR O ARQUIVO\n");
    }
    else{
        while((fscanf(arquivoRanking, "%d %[^\n]s", &pontos[cont], nomes[cont])) != EOF ){
        cont++;
        }
    }

    fclose(arquivoRanking); //leu todo o arquivo, ordenar agora, BUBBLE SORT (finalmente)!!

    for(i = 0; i < cont ; i++){
        for(j = i + 1 ; j < cont ; j++){
            if(pontos[i] < pontos[j]){
                aux = pontos[i];
                pontos[i] = pontos[j];
                pontos[j] = aux;

                strcpy(auxNome, nomes[i]);
                strcpy(nomes[i], nomes[j]);
                strcpy(nomes[j], auxNome);
            }
        }
    }

    // escrever de volta no txt
    arquivoRanking = fopen(url, "w");

    if(arquivoRanking == NULL){
        printf("ERRO: NAO FOI POSSIVEL ABRIR O ARQUIVO\n");
    }
    else{
        for(i = 0 ; i < cont ; i++)
        fprintf(arquivoRanking, "%d %s\n", pontos[i], nomes[i]);
    }

    fclose(arquivoRanking);
}

void mostrarRanking () {
    int i, cont = 0;
    char url[] = "ranking.txt", nomes[35][15], op;
    int pontos[35];
    FILE *arquivoRanking;

    arquivoRanking = fopen(url, "r");

    while((fscanf(arquivoRanking,"%d %[^\n]s", &pontos[cont], nomes[cont])) != EOF){
        cont++;
    }

    fclose(arquivoRanking);

    limpaTela();

    printf("\t\t\t\t\t\t    ____              __   _            \n");
    printf("\t\t\t\t\t\t   / __ \\____ _____  / /__(_)___  ____ _\n");
    printf("\t\t\t\t\t\t  / /_/ / __ `/ __ \\/ //_/ / __ \\/ __ `/\n");
    printf("\t\t\t\t\t\t / _, _/ /_/ / / / / ,< / / / / / /_/ /\n");
    printf("\t\t\t\t\t\t/_/ |_|\\__,_/_/ /_/_/|_/_/_/ /_/\\__, /\n");
    printf("\t\t\t\t\t\t                               /____/\n\n");

    printf("\t\t\t\t\t          --------------------------------\n");

    for(i = 0 ; i < cont ; i++){
        if(i >= 9) {
            printf("\t\t\t\t\t          | %2do | %5d       %10s |\n", i + 1, pontos[i], nomes[i]);
            printf("\t\t\t\t\t          --------------------------------\n");
        }
        else {
            printf("\t\t\t\t\t          | %2do | %5d       %10s |\n", i + 1, pontos[i], nomes[i]);
            printf("\t\t\t\t\t          --------------------------------\n");
        }
    }

    printf("\n\t\t\t\t\t          > Digite [s] para voltar: ");
    limpaBuffer();
    op = tolower(getchar());

    while (op != 's') {
        printf("\n\t\t\t\t\t          > Digite [s] para voltar: ");
        limpaBuffer();
        op = tolower(getchar());
    }

    menuPrincipal_1();
}

void fimDeJogo () {
    pontuacao_jogador = (int)(39000 / contador_de_jogadas);
    limpaTela();

    if (jogador_venceu) {
        printf("\t\t\t\t--------------------------------------------------------------------------\n");
        printf("\t\t\t\t|                                                                        |\n");
        printf("\t\t\t\t|                       PARABÉNS!!! VOCÊ VENCEU!!!                       |\n");
        printf("\t\t\t\t|                                                                        |\n");
        printf("\t\t\t\t|                             SUA PONTUAÇÃO                              |\n");
        printf("\t\t\t\t|                                                                        |\n");
        printf("\t\t\t\t|                         %10s | %05d pts                         |\n", nome_jogador1, pontuacao_jogador);
        printf("\t\t\t\t|                                                                        |\n");
        printf("\t\t\t\t--------------------------------------------------------------------------\n");

        escreveNoRanking();
    }
    else {
        printf("\t\t\t\t--------------------------------------------------------------------------\n");
        printf("\t\t\t\t|                                                                        |\n");
        printf("\t\t\t\t|                       QUE PENA... VOCÊ PERDEU...                       |\n");
        printf("\t\t\t\t|                                                                        |\n");
        printf("\t\t\t\t|                           TENTE NOVAMENTE                              |\n");
        printf("\t\t\t\t|                                                                        |\n");
        printf("\t\t\t\t--------------------------------------------------------------------------\n\n");
    }

    printf("\t\t\t        > Você deseja iniciar outro jogo [s/n]? ");
    limpaBuffer();
    jogar_denovo = tolower(getchar());

    if (jogar_denovo == 's') {
        reset();
        menuPrincipal_1();
    }
}

void rodadas () {
    int turno = 1;

    do {
        if (turno) {
            turnoDoJogador();
            contador_de_jogadas++;
            turno = 0;
        }
        else {
            turnoDaCpu();
            turno = 1;
        }
        verificaFimDeJogo();
    } while (!fim_do_jogo);

    fimDeJogo();
}

void novoJogo () {
    limpaTela();
    printf("QUAL O SEU NOME, COMANDANTE?: ");
    limpaBuffer();
    scanf("%[^\n]s", nome_jogador1);
    limpaTela();

    iniciaTabuleiro();
    colheDadosCpu(tabuleiro2);
    imprimeTabuleiro();
    colheDados(tabuleiro1);
    rodadas();
}

void reset () {
    qt_barcos.corveta = 2;
    qt_barcos_cpu.corveta = 2;
    qt_barcos.submarino = 2;
    qt_barcos_cpu.submarino = 2;
    qt_barcos.fragata = 2;
    qt_barcos_cpu.fragata = 2;
    qt_barcos.destroyer = 1;
    qt_barcos_cpu.destroyer = 1;
    qt_barcos.cruzador = 1;
    qt_barcos_cpu.cruzador = 1;
    qt_barcos.portaAvioes = 1;
    qt_barcos_cpu.portaAvioes = 1;

    strcpy(nome_jogador1, "JOGADOR 1");
    jogar_denovo = 'n';

    contadorDeBarcos = 9;
    contadorDeBarcosCpu = 9;

    pontuacao_jogador = 0;
    contador_de_jogadas = 1;
    primeira_jogada = 1;

    vidas_jogador = 39;
    vidas_cpu = 39;

    cpu_acertou = 0;
    jogador_acertou = 0;

    fim_do_jogo = 0;
    jogador_venceu = 0;
    cpu_venceu = 0;
}

void executaOpcao (char opcao) {
    switch (opcao) {
        case '1':
            novoJogo();
            break;
        case '2':
            guia_Jogo();
            break;
        case '3':
            organizarRanking();
            mostrarRanking();
            break;
    }
}

void menuPrincipal () {
    char opcao;
    char tem_certeza;

        printf("ATENÇÃO!!!\n\n");
        printf("Para uma melhor visualização, MAXIMIZE a janela do seu terminal!\n\n");
        printf("> Pressione ENTER para continuar ");
        opcao = getchar();

    do {
        limpaTela();

        printf("\t\t\t\t         ____        __        ____             _   __                  __\n");
        printf("\t\t\t\t        / __ )____ _/ /_____ _/ / /_  ____ _   / | / /___ __   ______ _/ /\n");
        printf("\t\t\t\t       / __  / __ `/ __/ __ `/ / __ \\/ __ `/  /  |/ / __ `/ | / / __ `/ / \n");
        printf("\t\t\t\t      / /_/ / /_/ / /_/ /_/ / / / / / /_/ /  / /|  / /_/ /| |/ / /_/ / /  \n");
        printf("\t\t\t\t     /_____/\\__,_/\\__/\\__,_/_/_/ /_/\\__,_/  /_/ |_/\\__,_/ |___/\\__,_/_/   \n\n");

        printf("\n\n");
        printf("\t\t\t\t\t\t       --------------------------------\n");
        printf("\t\t\t\t\t\t       |        MENU PRINCIPAL        |\n");
        printf("\t\t\t\t\t\t       --------------------------------\n");
        printf("\t\t\t\t\t\t       |  1. NOVO JOGO                |\n");
        printf("\t\t\t\t\t\t       |  2. INSTRUÇÕES DO JOGO       |\n");
        printf("\t\t\t\t\t\t       |  3. RANKING                  |\n");
        printf("\t\t\t\t\t\t       |  0. SAIR                     |\n");
        printf("\t\t\t\t\t\t       --------------------------------\n\n\n");

        printf("\t\t\t\t\t\t       > Digite uma opção: ");
        limpaBuffer();
        scanf("%c", &opcao);
        while (opcao != '0' &&  opcao != '1' &&  opcao != '2' &&  opcao != '3') {
            printf("\t\t\t\t\t\t       > Digite uma opção válida! ");
            limpaBuffer();
            scanf("%c", &opcao);
        }

        if (opcao == '0') {
            printf("\t\t\t\t\t\t       > Tem certeza que deseja sair [s/n]? ");
            limpaBuffer();
            scanf("%c", &tem_certeza);
            while (tolower(tem_certeza) != 's' && tem_certeza != 'n') {
                printf("\t\t\t\t\t\t       > Digite uma opção válida! [s/n]: ");
                limpaBuffer();
                scanf("%c", &tem_certeza);
            }

            if (tem_certeza == 's') {
                break;
            }
        }
    } while (opcao == '0');

    executaOpcao(opcao);
}

void menuPrincipal_1 () {

    char opcao;
    char tem_certeza;

    do {
        limpaTela();

        printf("\t\t\t\t         ____        __        ____             _   __                  __\n");
        printf("\t\t\t\t        / __ )____ _/ /_____ _/ / /_  ____ _   / | / /___ __   ______ _/ /\n");
        printf("\t\t\t\t       / __  / __ `/ __/ __ `/ / __ \\/ __ `/  /  |/ / __ `/ | / / __ `/ / \n");
        printf("\t\t\t\t      / /_/ / /_/ / /_/ /_/ / / / / / /_/ /  / /|  / /_/ /| |/ / /_/ / /  \n");
        printf("\t\t\t\t     /_____/\\__,_/\\__/\\__,_/_/_/ /_/\\__,_/  /_/ |_/\\__,_/ |___/\\__,_/_/   \n\n");

        printf("\n\n");
        printf("\t\t\t\t\t\t       --------------------------------\n");
        printf("\t\t\t\t\t\t       |        MENU PRINCIPAL        |\n");
        printf("\t\t\t\t\t\t       --------------------------------\n");
        printf("\t\t\t\t\t\t       |  1. NOVO JOGO                |\n");
        printf("\t\t\t\t\t\t       |  2. INSTRUÇÕES DO JOGO       |\n");
        printf("\t\t\t\t\t\t       |  3. RANKING                  |\n");
        printf("\t\t\t\t\t\t       |  0. SAIR                     |\n");
        printf("\t\t\t\t\t\t       --------------------------------\n\n\n");

        printf("\t\t\t\t\t\t       > Digite uma opção: ");
        limpaBuffer();
        scanf("%c", &opcao);
        while (opcao != '0' &&  opcao != '1' &&  opcao != '2' &&  opcao != '3') {
            printf("\t\t\t\t\t\t       > Digite uma opção válida! ");
            limpaBuffer();
            scanf("%c", &opcao);
        }

        if (opcao == '0') {
            printf("\t\t\t\t\t\t       > Tem certeza que deseja sair [s/n]? ");
            limpaBuffer();
            scanf("%c", &tem_certeza);
            while (tolower(tem_certeza) != 's' && tem_certeza != 'n') {
                printf("\t\t\t\t\t\t       > Digite uma opção válida! [s/n]: ");
                limpaBuffer();
                scanf("%c", &tem_certeza);
            }

            if (tem_certeza == 's') {
                break;
            }
        }
    } while (opcao == '0');

    executaOpcao(opcao);
}

void guia_Jogo(){

    char opcao = '0';
    char frase[100];
    FILE *file;
    file = fopen("instrucao.txt", "r");
    limpaTela();

    if (file == NULL){
        printf("Arquivo nao pode ser executado\n");
        system("pause");
    }

    printf("\t\t\t\t         ____        __        ____             _   __                  __\n");
    printf("\t\t\t\t        / __ )____ _/ /_____ _/ / /_  ____ _   / | / /___ __   ______ _/ /\n");
    printf("\t\t\t\t       / __  / __ `/ __/ __ `/ / __ \\/ __ `/  /  |/ / __ `/ | / / __ `/ / \n");
    printf("\t\t\t\t      / /_/ / /_/ / /_/ /_/ / / / / / /_/ /  / /|  / /_/ /| |/ / /_/ / /  \n");
    printf("\t\t\t\t     /_____/\\__,_/\\__/\\__,_/_/_/ /_/\\__,_/  /_/ |_/\\__,_/ |___/\\__,_/_/   \n");

    while (fgets(frase, 100, file) != NULL){
        printf("%s", frase);
    }

    printf("\t\t> Digite [s] para voltar: ");

    do {
        limpaBuffer();
        scanf("%c", &opcao);

        if (opcao != 's'){
        printf("\t\t> Digite [s] para voltar: ");
    }
    else if (opcao == 's') {

        fclose(file);
        menuPrincipal_1();
        }

    } while (opcao != 's');
}