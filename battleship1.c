#include <stdio.h> 
#include <stdlib.h>
  int main() {
    printf("BATALHA NAVAL \n \n \n");
    printf("Destrua todos os barcos inimigos escolhendo a linha e coluna para tentar acertar \n");
    printf("\n");
    char base[11][11] = {
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0},
     {0, 0, 2, 0, 0, 0, 0, 1, 0, 0, 0},
     {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
     {0, 0, 2, 0, 5, 0, 0, 4, 4, 4, 0},
     {0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0},
     {0, 1, 0, 0, 5, 0, 0, 2, 0, 0, 0},
     {0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 1},
     {0, 0, 2, 0, 0, 3, 0, 3, 3, 0, 0},
     {0, 1, 0, 0, 0, 3, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 4, 4, 4, 0, 0}
   };
    char tabuleiro[11][11]; //matriz para o tabuleiro 10x10
    int i, j, cont1 = 0, cont2 = 0, cont3 = 0, cont4 = 0, cont5 = 0, cont6 = 0, fim = 1; //foi adicionado varios contadores, um para cada barco mais um para o número de tiros
    for (i = 1; i < 11; i++) {
      for (j = 1; j < 11; j++) {
        tabuleiro[i][j] = '.';
        printf("| % c | ", tabuleiro[i][j]);
      }
      printf("\n");
    }
    printf("Informe a Linha (0 a 10): "); //o usuario informa a linha
    scanf("%d", & i);
    printf("Informe a Coluna (0 a 10): "); // o usuario informa a coluna
    scanf("%d", & j);
    printf("\n");
    while (fim != 0) { // vai repetir enquanto o fim for diferente de 0
      if (base[i][j] == 2) // testa se a cordenada contem um submarino
      {
        tabuleiro[i][j] = 'S';
        printf("voce acertou um Submarino");
        cont2 = cont2 + 1;
        printf("\n");
      } else // se não
      {
        if (base[i][j] == 3) // testa se a cordenada contem um cruzador
        {
          tabuleiro[i][j] = 'C';
          cont3 = cont3 + 1;
          if (tabuleiro[i + 1][j] == 'C' || tabuleiro[i][j + 1] == 'C' || tabuleiro[i - 1][j] == 'C' || tabuleiro[i][j - 1] == 'C') // testa se destruiu o cruzador
          {
            printf("voce Afundou o Cruzador");
            printf("\n");
          } else {
            printf("voce acertou um Cruzador");
            printf("\n");
          }
        } else // se não
        {
          if (base[i][j] == 4) {
            tabuleiro[i][j] = 'E';
            cont4 = cont3 + 1;
            if (tabuleiro[i + 1][j] == 'E' && tabuleiro[i + 2][j] == 'E' || tabuleiro[i - 1][j] == 'E' && tabuleiro[i - 2][j] == 'E' || tabuleiro[i][j + 1] == 'E' &&
              tabuleiro[i][j + 2] == 'E' || tabuleiro[i][j - 1] == 'E' && tabuleiro[i][j - 2] == 'E' || tabuleiro[i + 1][j] == 'E' && tabuleiro[i - 1][j] == 'E' ||
              tabuleiro[i][j + 1] == 'E' && tabuleiro[i][j - 1] == 'E') {
              printf("voce Afundou um Encouracado");
              printf("\n");
            } else {
              printf("voce acertou um Encouracado");
              printf("\n");
            }
          } else {
            if (base[i][j] == 5) {
              tabuleiro[i][j] = 'P';
              cont5 = cont5 + 1;
              printf("\n");
              if (tabuleiro[i + 1][j] == 'P' && tabuleiro[i + 2][j] == 'P' && tabuleiro[i + 3][j] == 'P' || tabuleiro[i - 1][j] == 'P' && tabuleiro[i - 2][j] == 'P' && tabuleiro[i - 3][j] == 'P' || tabuleiro[i][j + 1] == 'P' && tabuleiro[i][j + 2] == 'P' && tabuleiro[i][j + 3] == 'P' || tabuleiro[i][j - 1] == 'P' && tabuleiro[i][j - 2] == 'P' && tabuleiro[i][j - 3] == 'P' || tabuleiro[i + 1][j] == 'P' && tabuleiro[i + 2][j] == 'P' && tabuleiro[i - 1][j] == 'P' || tabuleiro[i - 1][j] == 'P' && tabuleiro[i - 2][j] == 'P' && tabuleiro[i + 1][j] == 'P' || tabuleiro[i][j + 1] == 'P' && tabuleiro[i][j + 2] == 'P' && tabuleiro[i][j - 1] == 'P' || tabuleiro[i][j - 1] == 'P' && tabuleiro[i][j - 2] == 'P' && tabuleiro[i][j + 1] == 'P') {
                printf("voce afundou um porta-aviões");
                printf("\n");
              } else {
                printf("voce acertou um porta-avioes");
                printf("\n");
              }
            } else {
              if (base[i][j] == 1) {
                tabuleiro[i][j] = 'A';
                printf("voce destruiu um Hidroaviao");
                cont1 = cont1 + 1;
                printf("\n");
              } else // se a cordenada não contem nada, acertou a água
              {
                tabuleiro[i][j] = 'O';
                printf("Acertou Na Agua");
                printf("\n");
              }
            }
          }
        }
      }
      for (i = 1; i < 11; i++) {
        for (j = 1; j < 11; j++) {
          printf("| %c |", tabuleiro[i][j]);
        }
        printf("\n");
      }
      if (cont1 >= 5 && cont2 >= 4 && cont3 >= 6 && cont4 >= 6 && cont5 >= 4) // testa se acabou o jogo, se acabou fim = 0, se não informe linha e coluna
      {
        fim = 0;
      } else {
        printf("Informe a Linha: \n");
        scanf("%d", & i);
        printf("Informe a Coluna: \n");
        scanf("%d", & j);
        printf("\n");
        cont6 = cont6 + 1;
      }
    }
    printf("Fim De Jogo /n PARABENS! \n Voce venceu \n");
    printf("Numero de disparos: %d", cont6);
    fflush(stdin);
    getchar();
  }