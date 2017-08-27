#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 15
#define VAZIO '.'
#define CHEIO '#'

char tabuleiro1[MAX][MAX];
char tabuleiro2[MAX][MAX];
int coordH[MAX] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14};
int coordV[MAX] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14};
char nome_jogador1[15] = "JOGADOR 1";
char nome_jogador2[15] = "CPU";
int contadorDeBarcos = 9;


/* variveis globais, contates e definições */

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

// Sumário de funções ////////////////////////////////////////////////////////
void limpaTela();
void iniciaTabuleiro();
void imprimeOpcoesDeBarcos();
void imprimeTabuleiro();
void colheDados();
int verificaBarcos();
void imprimeBarcos();
int verificaCorveta();
void imprimeCorveta();
int verificaSubmarino();
void imprimeSubmarino();
int verificaDestroyer();
void imprimeDestroyer();
int verificaCruzador();
void imprimeCruzador();
int verificaFragata();
void imprimeFragata();
int verificaPortaAvioes();
void imprimePortaAvioes();
// ///////////////////////////////////////////////////////////////////////////

void limpaTela () {
    system("clear");
};

void iniciaTabuleiros() {
    int i, j;

    for (i = 0 ; i < MAX ; i++) {
        for (j = 0 ; j < MAX ; j++) {
            tabuleiro1[i][j] = VAZIO;
            tabuleiro2[i][j] = VAZIO;
        }
    }
}

void imprimeOpcoesDeBarcos () {
    printf("1. Corveta\n");
    printf("2. Submarino\n");
    printf("3. Fragata\n");
    printf("4. Destroyer\n");
    printf("5. Cruzador\n");
    printf("6. Porta-Aviões\n\n");
}

void imprimeTabuleiro (char M[MAX][MAX]) {
    int i, j;
    if (M == tabuleiro1) {
        printf("\t\t  NOME: %s\n", nome_jogador1);
        printf("\t       ---------------------------------------------\n");
    }
    else {
        printf("\t\t  NOME: %s\n", nome_jogador2);
        printf("\t       ---------------------------------------------\n");
    }
    printf("\t         |");
    for (i = 0 ; i < MAX - 1 ; i++) {
        printf("%3d", coordH[i]);
    }
    printf("\n\t       --+------------------------------------------\n");
    for (i = 1 ; i < MAX ; i++) {
        printf("\t       %2d|", coordV[i-1]);
        for (j = 1 ; j < MAX ; j++) {
            printf("  %c", M[i][j]);
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
}

void colheDados (char M[MAX][MAX]) {
    int barco, linha, coluna, direcao = 0;
    char op;

    do {
        imprimeOpcoesDeBarcos();
        printf("Barco: ");
        scanf("%d", &barco);
        while (barco <= 0 || barco > 6) {
            printf("Opção inválida! Digite um barco válido: ");
            getchar();
            scanf("%d", &barco);
        }

        if (barco != 3) {
            printf("Direção [h/v]: ");
            scanf(" %c", &op);
            while (tolower(op) != 'h' && tolower(op) != 'v') {
                printf("Opção inválida! Digite outra direção [h/v]: ");
                scanf(" %c", &op);
            }

            (tolower(op) == 'h') ? (direcao = 1) : (direcao = 0) ;
        }

        printf("Linha: ");
        scanf(" %d", &linha);
        while (linha >= MAX || linha <= 0) {
            printf("Opção inválida! Digite uma linha válida: ");
            getchar();
            scanf(" %d", &linha);
        }

        printf("Coluna: ");
        scanf(" %d", &coluna);
        while (coluna >= MAX || coluna <= 0) {
            printf("Opção inválida! Digite uma coluna válida: ");
            getchar();
            scanf(" %d", &coluna);
        }

        if (verificaBarcos(barco, direcao, linha, coluna, M)) {
            imprimeBarcos(barco, direcao, linha, coluna, M);
            limpaTela();
            imprimeTabuleiro(M);
            contadorDeBarcos--;
            printf("Barco inserido com sucesso!\n");
        }
        else {
            limpaTela();
            imprimeTabuleiro(M);
            printf("Erro ao inserir o barco! Tente Novamente!\n");
        }
    } while (contadorDeBarcos);
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
}

void imprimeBarcos (int barco, int direcao, int linha, int coluna, char M[MAX][MAX]) {
    switch (barco) {
        case 1:
            return imprimeCorveta(direcao, linha, coluna, M);
        case 2:
            return imprimeSubmarino(direcao, linha, coluna, M);
        case 3:
            return imprimeFragata(linha, coluna, M);
        case 4:
            return imprimeDestroyer(direcao, linha, coluna, M);
        case 5:
            return imprimeCruzador(direcao, linha, coluna, M);
        case 6:
            return imprimePortaAvioes(direcao, linha, coluna, M);
    }
}

int main () {

    iniciaTabuleiros();
    imprimeTabuleiro(tabuleiro1);
    colheDados(tabuleiro1);

    return 0;
}