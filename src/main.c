#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void clearScreen();
void printAbout();
void printBattleship();
void printMenu1();
void printMenu2();
void printPvCOM();
void testRandom();
void menuControl();
void initMatrix(char tabuleiro[10][10]);
void printMatrix(char tabuleiro[10][10]);
void putShips(char tabuleiro[10][10]);
void putShipsCOM(char tabuleiro[10][10]);
void readCoordenate(char shipType, char *line, int *col, char *direction);
void confirmCoordenate(char shipType, char line, int col, char direction, char *confirmation);
void checkCoordenate(char shipType, char line, int col, char direction, char tabuleiro[10][10], char *confirmation);
void putShip(char shipType, char line, int col, char direction, char tabuleiro[10][10], char *confirmation);
const char * directionMessage(char direction);
const char * shipName(char ship);
const int getShipSize(char ship);

int main(){
	menuControl();

	return(0);
}

void clearScreen()
{
  system("@cls||clear");
}

void initMatrix(char tabuleiro[10][10]){
    for (int i = 0; i < 10; i++) {      
      for (int j = 0; j < 10; j++) {
        tabuleiro[i][j] = '.';
      }      
    }
}

void printMatrix(char tabuleiro[10][10]){
	printf(" ");
	for (int i = 0; i < 10; i++) {
		printf("   %i", i);
	}
	printf("\n");
    for (int i = 0; i < 10; i++) {
      printf("%c | ", 65+i);
      for (int j = 0; j < 10; j++) {
        printf("%c | ", tabuleiro[i][j]);
      }
      printf("\n");
    }
}

/*************************************************************************************************/

void checkCoordenate(char shipType, char line, int col, char direction, char tabuleiro[10][10], char *confirmation){
	int intLine = (int)line-65;

	/* Verifico:
	 * - se é uma coordenada dentro da matriz
	 * - se a letra informada para a direção é válida
	 * - se a direção e a coordenada ficam dentro da matriz
	*/
	if(intLine < 0 
		|| col < 0 
		|| intLine > 9 
		|| col > 9 
		|| !(direction == 'W' || direction == 'S' || direction == 'A' || direction == 'D')
		|| (direction == 'W' && (intLine - getShipSize(shipType) < 0))
		|| (direction == 'S' && (intLine + getShipSize(shipType) > 9))
		|| (direction == 'A' && (col - getShipSize(shipType) < 0))
		|| (direction == 'D' && (col + getShipSize(shipType) > 9))){		
		*confirmation = 'N';
		return;
	}

	// Verifico se as posições em que a embarcação será colocada estão livres
	switch(direction){
		case 'W':
			//"Para Cima"
			for(int i = intLine; i > (intLine - getShipSize(shipType)); i--){
				if(tabuleiro[i][col] != '.'){
					*confirmation = 'N';
					break;
				}
			}
			break;
		case 'S':
			//"Para Baixo"
			for(int i = intLine; i < (intLine + getShipSize(shipType)); i++){
				if(tabuleiro[i][col] != '.'){
					*confirmation = 'N';
					break;
				}
			}
			break;
		case 'D':
			//"Para Direita"
			for(int i = col; i < (col + getShipSize(shipType)); i++){
				if(tabuleiro[intLine][i] != '.'){
					*confirmation = 'N';
					break;
				}
			}
			break;
		case 'A':
			//"Para Esquerda"
			for(int i = col; i > (col - getShipSize(shipType)); i--){
				if(tabuleiro[intLine][i] != '.'){
					*confirmation = 'N';
					break;
				}
			}
			break;
	}
}

/**
* Método que apenas coloca as embarcações nos seus devidos lugares
*/
void putShip(char shipType, char line, int col, char direction, char tabuleiro[10][10], char *confirmation){
	int intLine = (int)line-65;
	switch(direction){
		case 'W':
			//"Para Cima"
			for(int i = intLine; i > (intLine - getShipSize(shipType)); i--){
				tabuleiro[i][col] = shipType;
			}
			break;
		case 'S':
			//"Para Baixo"
			for(int i = intLine; i < (intLine + getShipSize(shipType)); i++){
				tabuleiro[i][col] = shipType;
			}
			break;
		case 'D':
			//"Para Direita"
			for(int i = col; i < (col + getShipSize(shipType)); i++){
				tabuleiro[intLine][i] = shipType;
			}
			break;
		case 'A':
			//"Para Esquerda"
			for(int i = col; i > (col - getShipSize(shipType)); i--){
				tabuleiro[intLine][i] = shipType;
			}
			break;
	}
}

/*************************************************************************************************/

void readCoordenate(char shipType, char *line, int *col, char *direction){
	printf("Você está posicionando a embarcação \"%s\".\n", shipName(shipType));
	printf("Informe a linha (A-J): ");
	scanf(" %c", line);
	printf("Informe a coluna (0-9): ");
	scanf("%i", col);
	printf("Informe a direção (W,S,A,D): ");
	scanf(" %c", direction);
}

void confirmCoordenate(char shipType, char line, int col, char direction, char *confirmation){
	printf("\nDeseja confirmar a coordenada %c-%i com direção \"%s\" para a embarcação \"%s\"? (S/N)\n", line, col, directionMessage(direction), shipName(shipType));
	scanf(" %c", confirmation);
}

void putShips(char tabuleiro[10][10]){
	printf("\nAgora posicione as embarcações no tabuleiro.\n\n");

	for(int i = 0; i < 5; i++){
		char confirmation;
		char shipType;

		switch(i){
			case 0:
				shipType = 'P';
				break;
			case 1:
				shipType = 'N';
				break;
			case 2:
				shipType = 'C';
				break;
			case 3:
				shipType = 'S';
				break;
			case 4:
				shipType = 'D';
				break;
		}

		do{
			// Valores default (só pra iniciar com algo)
			char line = 'A';
			int col = 0;
			char direction = 'W';
			confirmation = 'S';

			readCoordenate(shipType, &line, &col, &direction);
			checkCoordenate(shipType, line, col, direction, tabuleiro, &confirmation);

			if(confirmation == 'S'){
				confirmCoordenate(shipType, line, col, direction, &confirmation);
				if(confirmation == 'S'){
					putShip(shipType, line, col, direction, tabuleiro, &confirmation);
				}
			}else{
				printf("Coordenada inválida! Tente novamente.\n\n");
			}
		}while(confirmation == 'N');

		clearScreen();
		printBattleship();
		printMatrix(tabuleiro);
	}
}

/*************************************************************************************************/

void putShipsCOM(char tabuleiro[10][10]){
	printf("\nO computador está posicionado as suas embarcações\n");

	char lines[] = {'A','B','C','D','E','F','G','H','I','J'};
	int cols[] = {0,1,2,3,4,5,6,7,8,9};
	char directions[] = {'W','S','D','A'};

	for(int i = 0; i < 5; i++){
		char confirmation;
		char shipType;
		int tries = 0;

		do{
			if(tries >= 100){
				tries = 0;
				i = 0;
				initMatrix(tabuleiro);
			}

			switch(i){
				case 0:
					shipType = 'P';
					break;
				case 1:
					shipType = 'N';
					break;
				case 2:
					shipType = 'C';
					break;
				case 3:
					shipType = 'S';
					break;
				case 4:
					shipType = 'D';
					break;
			}

			// Seleciono aleatoriamente uma coordena e direção
			char col = cols[rand() % 10], direction = directions[rand() % 4];
			int line = lines[rand() % 10];
			
			checkCoordenate(shipType, line, col, direction, tabuleiro, &confirmation);

			if(confirmation == 'S'){
				putShip(shipType, line, col, direction, tabuleiro, &confirmation);
			}else{
				tries++;
			}
		}while(confirmation == 'N');

		printf("Posicionado o %s\n", shipName(shipType));
		/*clearScreen();
		printBattleship();*/		
		printMatrix(tabuleiro);
	}
}


void printPvCOM(){
	printf("\n\nBem-vindo à opção de jogo PvCOM!\n\n\n");

	// inicio o tabuleiro para o primeiro jogador
	char tabuleiro1[10][10];
	char nomeJogador1[100];

	printf("Informe o nome do primeiro Jogador: ");
	scanf("%s", nomeJogador1);
	initMatrix(tabuleiro1);

	printf("\nTabuleiro do jogador '%s'\n", nomeJogador1);
	printMatrix(tabuleiro1);

	putShips(tabuleiro1);

	clearScreen();
	printBattleship();
	printf("\nTabuleiro do jogador '%s'\n", nomeJogador1);
	printMatrix(tabuleiro1);

	// inicio o tabuleiro para a máquina
	/*char tabuleiro2[10][10];
	char nomeJogador2[] = "COMPUTER";	
	initMatrix(tabuleiro2);
	putShipsCOM(tabuleiro2);
	printf("\nTabuleiro do jogador '%s'\n", nomeJogador2);
	printMatrix(tabuleiro2);*/
	/*
	printf("\nTabuleiro do jogador '%s'\n", nomeJogador1);
	printMatrix(tabuleiro1);
	printf("\nTabuleiro do jogador '%s'\n", nomeJogador2);
	printMatrix(tabuleiro2);
	*/
}

void menuControl(){
	clearScreen();
	printBattleship();
	printMenu1();

	char optionMenu1;
	char optionMenu2;

	while((optionMenu1 = getchar())!= '3'){
		switch(optionMenu1){
			case '1':
				clearScreen();
				printBattleship();
				printMenu2();
				while((optionMenu2 = getchar())!= '2'){
					switch(optionMenu2){
						case '1':
							clearScreen();
							printBattleship();
							printPvCOM();
							printMenu2();
							break;
					}
				}
				clearScreen();
				printBattleship();
				printMenu1();
				break;			
			case '2':
				clearScreen();
				printBattleship();
				printAbout();
				printMenu1();
				break;
		}
	}
}
void printAbout(){
	printf("**************************************************************\n");
	printf("*Bem-vindo ao jogo de batalha naval! - Exemplo trabalho UFPR *\n");
	printf("**************************************************************\n");
	printf("\n\n\n");
	printf("Esse exemplo foi desenvolvido por Jackson Antonio do Prado Lima.\n\n\n");
	/*
	Informar mais alguma coisa
	*/
}

void printBattleship(){
	printf ("XXXXX   XXXX  XXXXXX XXXXXX XX     XXXXXX  XXXXX XX  XX XX XXXX\n");
	printf ("XX  XX XX  XX   XX     XX   XX     XX     XX     XX  XX XX XX  XX\n");
	printf ("XXXXX  XX  XX   XX     XX   XX     XXXX    XXXX  XXXXXX XX XXXX\n"); 
	printf ("XX  XX XXXXXX   XX     XX   XX     XX         XX XX  XX XX XX\n");
	printf ("XXXXX  XX  XX   XX     XX   XXXXXX XXXXXX XXXXX  XX  XX XX XX\n");	
	printf ("\n\n");
}

void printMenu1(){
	printf ("Escolha uma opção:\n");
	printf ("1) Jogar\n");	
	printf ("2) Sobre o jogo\n");
	printf ("3) Sair\n\n");
}

void printMenu2(){
	printf ("Escolha uma opção:\n");	
	printf ("1) PvCOM\n");
	printf ("2) Voltar\n\n");	
}

const char * directionMessage(char direction)
{
	switch(direction){
		case 'W':
			return "Para Cima";
		case 'S':
			return "Para Baixo";
		case 'D':
			return "Para Direita";
		case 'A':
			return "Para Esquerda";
	} 
}

const char * shipName(char ship)
{
	switch(ship){
		case 'P':
			return "Porta-aviões";
		case 'N':
			return "Embarcação de Guerra";
		case 'C':
			return "Cruzador";
		case 'S':
			return "Submarino";
		case 'D':
			return "Destruidor";
	} 
}

const int getShipSize(char ship)
{
	switch(ship){
		case 'P':
			return 5;
		case 'N':
			return 4;
		case 'C':
			return 3;
		case 'S':
			return 3;
		case 'D':
			return 3;
	}
} 

void testRandom(){
	time_t t;
	
   /* Intializes random number generator */
   srand((unsigned) time(&t));

   /* Print 5 random numbers from 0 to 49 */
   for(int i = 0; i < 10 ; i++) 
   {
      printf("%d\n", rand() % 10);
   }
}