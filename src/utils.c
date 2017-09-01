#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void clearScreen(){
  system("@cls||clear");
}

void initMatrix(char tabuleiro[][10]){
    for (int i = 0; i < 10; i++) {      
      for (int j = 0; j < 10; j++) {
        tabuleiro[i][j] = '.';
      }      
    }
}

/*
int getMatrixRow(char** matrix){
	return (sizeof(matrix)/sizeof(matrix[0]));
}

int getMatrixCol(char** matrix){
	return (sizeof(matrix)/sizeof(matrix[0][0]))/getMatrixRow(matrix);
}*/

void printAbout(){
	printf("**************************************************************\n");
	printf("*Bem-vindo ao jogo de batalha naval! - Exemplo trabalho UFPR *\n");
	printf("**************************************************************\n");
	printf("\n\n\n");
	printf("Esse exemplo foi desenvolvido por Jackson Antonio do Prado Lima.\n\n\n");
}

void printAlign(int space, char *string){
	 int length = strlen(string);

    printf ("%*s%*c"
            ,((space - length) >> 1) + length // string length + padding spaces
            , string
            , ((space - length) >> 1) + ((space - length) & 1) // tailing spaces
            , ' '
    );
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
	printf ("2) PvP\n");
	printf ("3) Voltar\n\n");	
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
			return 2;
	}
}

/**
 * Verifica se a coordenada é válidas para inserção de uma embarcação no tabuleiro
 * 
 * @param line Linha da matriz
 * @param col Coluna da matriz
 * @return 1 se a coordenada é válida, 0 caso contrário
 */
int checkThreshold(int line, int col){
	return !(line < 0 || col < 0 || line > 10 || col > 10);
}

/**
 * Verifica se a coordenada juntamente com a direção são válidas para inserção de uma embarcação no tabuleiro
 * 
 * @param shipType Tipo de embarcação
 * @param line Linha da matriz
 * @param col Coluna da matriz
 * @param direction Direção do posicionamento da embarcação
 * @param tabuleiro Tabuleiro do jogo
 * @return 1 se a coordenada é válida, 0 caso contrário
 */
int checkCoordenate(char shipType, char line, int col, char direction, char tabuleiro[][10]){
	int intLine = (int)line-65;
	/* Verifico:
	 * - se é uma coordenada dentro da matriz
	 * - se a letra informada para a direção é válida
	 * - se a direção e a coordenada ficam dentro da matriz
	*/
	if(!checkThreshold(intLine, col) 
		|| !(direction == 'W' || direction == 'S' || direction == 'A' || direction == 'D')
		|| (direction == 'W' && (intLine - getShipSize(shipType) < 0))
		|| (direction == 'S' && (intLine + getShipSize(shipType) > 10))
		|| (direction == 'A' && (col - getShipSize(shipType) < 0))
		|| (direction == 'D' && (col + getShipSize(shipType) > 10))){
		return 0;
	}

	// Verifico se as posições em que a embarcação será colocada estão livres
	switch(direction){
		case 'W':
			//"Para Cima"
			for(int i = intLine; i > (intLine - getShipSize(shipType)); i--){
				if(tabuleiro[i][col] != '.'){
					return 0;
				}
			}
			break;
		case 'S':
			//"Para Baixo"
			for(int i = intLine; i < (intLine + getShipSize(shipType)); i++){
				if(tabuleiro[i][col] != '.'){
					return 0;
				}
			}
			break;
		case 'D':
			//"Para Direita"
			for(int i = col; i < (col + getShipSize(shipType)); i++){
				if(tabuleiro[intLine][i] != '.'){
					return 0;
				}
			}
			break;
		case 'A':
			//"Para Esquerda"
			for(int i = col; i > (col - getShipSize(shipType)); i--){
				if(tabuleiro[intLine][i] != '.'){
					return 0;
				}
			}
			break;
	}

	return 1;
}

/**
 * Realiza a leitura de uma coordenada para o tabuleiro.
 * A leitura continua até que uma coordenada válida seja informada.
 * 
 * @param *line Ponteiro de uma variável para ser a linha da matriz
 * @param *col Ponteiro de uma variável para ser a coluna da matriz
 */
void readCoordenate(char *line, int *col){
	int intLine;
	do{
		printf("Informe a linha (A-J): ");
		scanf(" %c", line);
		printf("Informe a coluna (0-9): ");
		scanf("%i", col);

		 intLine= (int)*line-65;
		// Verifica se a coordenada é válida
		if(!checkThreshold(intLine, *col)){
			printf("\nCoordenada inválida! Tente novamente.\n");
		}
	}while(!checkThreshold(intLine, *col));
}

/**
 * Verifica o resultado de uma jogada (disparo) da batalha naval
 * 
 * @param jogadas Jogadas realizadas pelo jogador até o momento.
 * @param tabuleiroAdversario Tabuleiro do adversário
 * @param nomeJogador Nome do jogador
 * @param nomeAdversario Nome do adversário
 */
void checkShot(char jogadas[][10], char tabuleiroAdversario[][10], char *nomeJogador, char *nomeAdversario, int line, int col){
	clearScreen();
	printBattleship();
	printf("\n\n");

	printf("Resultado do disparo realizado por: %s\n\n", nomeJogador);

	printf("*****************************************************************\n");
	// Verifico onde o disparo acertou e atribuo o indicador
	if(tabuleiroAdversario[line][col] == '.'){
		jogadas[line][col] = 'O';
		printf("* Água! \n");
	}else{
		printf("* Fogo! \n");
		jogadas[line][col] = 'X';

		char shipType = tabuleiroAdversario[line][col]; // Guardo o tipo de embarcação atingida
		int contHits = 0; // Quantas vezes essa embarcação foi atingida

		// Verifico se minha embarcação afundou
		for(int i = 0; i < 10; i ++){
			for(int j = 0; j < 10; j++){
				// Se há um disparo para minha embarcação, acumulo o número de vezes que ela foi acertada
				if(jogadas[i][j] == 'X' && tabuleiroAdversario[i][j] == shipType){
					contHits++;
				}
			}
		}

		// Se acertei o número de vezes igual ao tamanho dela, significa que afundei a embarcação
		if(contHits == getShipSize(shipType)){
			printf("* %s: Afundou %s %s!\n", nomeAdversario, shipType == 'N' ? "minha" : "meu", shipName(shipType));

			// Mostro no tabuleiro minha embarcação
			for(int i = 0; i < 10; i ++){
				for(int j = 0; j < 10; j++){
					// Procuro as posições da embarcação afundada e coloco a sigla dela para ser mostrada
					if(tabuleiroAdversario[i][j] == shipType){
						jogadas[i][j] = shipType;
					}
				}
			}
		}
	}
	printf("*****************************************************************\n");
	printf("\n\n\n");
}

/**
 * Mostra as informações dos tabuleiros lado a lado de dois jogadores com os seus respectivos nomes. 
 * Exemplo:
 *          Player          |         Computer
 *    0 1 2 3 4 5 6 7 8 9   |    0 1 2 3 4 5 6 7 8 9
 * A |P| | | | | | | | | |  | A | | | | | | | | | | |
 * B |P| | | | | | | | | |  | B | | | | | | | | | | |
 * C |P| | | | | | | | | |  | C | | | | | | |O| | | |
 * D |P| | | | | | | | | |  | D | | |x| | | | | | | |
 * E |P| | | | | | | | | |  | E | | | | | | | | | | |
 * F | | | | | | | | | | |  | F | | | | |O| | | | | |
 * G | | | | | | | | | | |  | G | | | | | | | | | | |
 * H | | | | | | | | | | |  | H | |O| | | | |O| | | |
 * I | | | | | | | | | | |  | I | | | | | | | | | | |
 * J | | | | | | | | | | |  | J | | | | | | | | | | |
 * 
 * @param nomeJogador1 Nome do jogador 1
 * @param jogadas1 Tabuleiro de jogadas do jogador 1
 * @param nomeJogador2 Nome do jogador 2
 * @param jogadas2 Tabuleiro de jogadas do jogador 2
 */
void displayGameInfo(char *nomeJogador1, char jogadas1[][10], char *nomeJogador2, char jogadas2[][10]){
	char separador[] = "     |   ";

	// Imprimo o cabeçalho
	printAlign(41, nomeJogador1);
	printf("%s", separador);
	printAlign(44, nomeJogador2);
	printf("\n");

	for(int cont = 0; cont < 2; cont++){
		printf(" ");
		for (int i = 0; i < 10; i++) {
			printf("   %i", i);
		}
		if(!cont){
			printf("%s", separador);
		}
	}
	printf("\n");
	
	// Imprimo as linhas
	for (int i = 0; i < 10; i++) {
		// Imprime a letra
		printf("%c | ", 65+i);

		// Imprime os valores do player1
		for (int j = 0; j < 10; j++) {
			printf("%c | ", jogadas1[i][j]);
		}

		// Imprime a letra
		printf("  |   %c | ", 65+i);
		// Imprime os valores do player 2
		for (int j = 0; j < 10; j++) {
			printf("%c | ", jogadas2[i][j]);
		}
		printf("\n");
	}
}

/**
 * Mostra as informações do tabuleiro do jogador com os seu respectivo nome. 
 * Exemplo:
 *          Player        
 *    0 1 2 3 4 5 6 7 8 9 
 * A |P| | | | | | | | | |
 * B |P| | | | | | | | | |
 * C |P| | | | | | | | | |
 * D |P| | | | | | | | | |
 * E |P| | | | | | | | | |
 * F | | | | | | | | | | |
 * G | | | | |N|N|N| | | |
 * H | | | | | | | | | | |
 * I | | | | | | | | | | |
 * J | | | | | | | | | | |
 * 
 * @param nomeJogador Nome do jogador
 * @param tabuleiro Tabuleiro do jogador 
 */
void displayGamePlayer(char* nomeJogador, char tabuleiro[][10]){
	char separador[] = "     |   ";

	// Imprimo o cabeçalho
	printAlign(41, nomeJogador);
	printf("\n");
	
	printf(" ");
	for (int i = 0; i < 10; i++) {
		printf("   %i", i);
	}
	printf("\n");
	
	// Imprimo as linhas
	for (int i = 0; i < 10; i++) {
		// Imprime a letra
		printf("%c | ", 65+i);

		// Imprime os valores do jogador
		for (int j = 0; j < 10; j++) {
			printf("%c | ", tabuleiro[i][j]);
		}
		printf("\n");
	}
}

/**
 * Verifica se o jogo já acabou
 * 
 * @param jogadas Tabuleiro de jogadas de algum jogador
 * @return Retorna 1 se todas as embarcações foram afundadas, 0 caso contrário
 */
int isEndGame(char jogadas[][10]){
	int embarcacoesAfundadas = 0;

	// Verifico se todas as embarcações foram afundadas
	for(int i = 0; i < 5; i++){

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

		// Se o tabuleiro contém a letra da embarcação significa que essa embarcação foi afundada
		for(int i = 0; i < 10; i++){
			for(int j = 0; j < 10; j++){
				if(jogadas[i][j] == shipType){
					embarcacoesAfundadas++;
					i = j = 10;
					break;
				}
			}
		}
	}

	
	return embarcacoesAfundadas == 5 ? 1 : 0;
}

/**
 * Realiza uma jogada (disparo) da batalha naval por um jogador
 * 
 * @param jogadas Jogadas realizadas pelo jogador até o momento.
 * @param tabuleiroAdversario Tabuleiro do adversário
 * @param nomeJogador Nome do jogador
 * @param nomeAdversario Nome do adversário
 */
void giveShot(char jogadas[][10], char tabuleiroAdversario[][10], char *nomeJogador, char *nomeAdversario){
	int col, intLine;
	char line;

	// O programa solicita um disparo válido
	do{
	    readCoordenate(&line, &col);

		intLine = (int)line-65;

		if(jogadas[intLine][col] == '.'){
			break;
		}else{
			printf("Essa coordenada já foi informada anteriormente. Tente novamente.\n");
		}		
	}while(1);

	checkShot(jogadas, tabuleiroAdversario, nomeJogador, nomeAdversario, intLine, col);
}

/**
 * A máquina realiza uma jogada (disparo) da batalha naval
 * 
 * @param jogadas Jogadas realizadas pelo jogador até o momento.
 * @param tabuleiroAdversario Tabuleiro do adversário
 * @param nomeJogador Nome do jogador
 * @param nomeAdversario Nome do adversário
 */
void giveRandomShot(char jogadas[][10], char tabuleiroAdversario[][10], char *nomeJogador, char *nomeAdversario){
	int col, line;
	
	do{
		srand(time(NULL));
		line = rand() % 10;
		col = rand() % 10;
	    
		if(jogadas[line][col] == '.'){
			break;
		}
	}while(1);

	checkShot(jogadas, tabuleiroAdversario, nomeJogador, nomeAdversario, line, col);
}

/**
 * Coloca uma embarcação no tabulerio
 * 
 * @param shipType Tipo de embarcação
 * @param line Linha da matriz
 * @param col Coluna da matriz
 * @param direction Direção do posicionamento da embarcação
 * @param tabuleiro Tabuleiro do jogo
 */
void putShip(char shipType, char line, int col, char direction, char tabuleiro[][10]){
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

/**
 * Coloca as embarcações de um jogador no tabulerio.
 * 
 * @param nomeJogador Nome do jogador
 * @param tabuleiro Tabuleiro do jogador
 */
void putShips(char *nomeJogador, char tabuleiro[][10]){
	printf("\n %s, agora posicione as suas embarcações no tabuleiro.\n\n", nomeJogador);

	char chooseSelection = 'S';

	do{
		initMatrix(tabuleiro);

		for(int i = 0; i < 5; i++){
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

				printf("Você está posicionando a embarcação \"%s\".\n", shipName(shipType));
				readCoordenate(&line, &col);
				printf("Informe a direção (W,S,A,D): ");
				scanf(" %c", &direction);

				if(checkCoordenate(shipType, line, col, direction, tabuleiro)){
					char confirmation = 'S';
					printf("\nPressione S para confirmar a coordenada %c-%i com direção \"%s\" para a embarcação \"%s\".\n", line, col, directionMessage(direction), shipName(shipType));

					do{
						scanf(" %c", &confirmation);
						if(confirmation != 'S' && confirmation != 'N'){
							printf("Opção inválida! Tente novamente.\n");
						}
					}while(confirmation != 'S' && confirmation != 'N');

					if(confirmation == 'S'){
						putShip(shipType, line, col, direction, tabuleiro);
						break;
					}
				}else{
					printf("\nCoordenada inválida! Tente novamente.\n");
				}
			}while(1);

			clearScreen();
			printBattleship();
			displayGamePlayer(nomeJogador, tabuleiro);
		}
		printf("\n\nEmbarcações posicionadas! Pressione S para confirmar as posições ou N para reiniciar: ");
		do{
			scanf(" %c", &chooseSelection);
			if(chooseSelection != 'S' && chooseSelection != 'N'){
				printf("Opção inválida! Tente novamente.\n");
			}
		}while(chooseSelection != 'S' && chooseSelection != 'N');
	}while(chooseSelection != 'S');
}

/**
 * Coloca as embarcações da "máquina" no tabulerio.
 * Aleatoriamente é selecionado um tabuleiro para a máquina.
 * 
 * @param tabuleiro Tabuleiro da máquina
 */
void putShipsCOM(char tabuleiro[][10]){
	// Como é complicado posicionar aleatoriamente e cheio de regras eu vou fazer uns jogos "fixos" e selecionar aleatoriamente um deles
	srand(time(NULL));
	int game = rand() % 3;
	char shipType, line, direction;
	int col;

	initMatrix(tabuleiro);

	switch(game){
		case 0: 
			// Posicionar o Porta-aviões
			shipType = 'P';
			line = 'A', col = 0, direction = 'D';
			putShip(shipType, line, col, direction, tabuleiro);

			// Posicionar o Embarcação de Guerra
			shipType = 'N';
			line = 'F', col = 1, direction = 'S';
			putShip(shipType, line, col, direction, tabuleiro);

			// Posicionar o Cruzador
			shipType = 'C';
			line = 'E', col = 6, direction = 'A';
			putShip(shipType, line, col, direction, tabuleiro);

			// Posicionar o Submarino
			shipType = 'S';
			line = 'H', col = 6, direction = 'W';
			putShip(shipType, line, col, direction, tabuleiro);

			// Posicionar o Destruidor
			shipType = 'D';
			line = 'D', col = 6, direction = 'D';
			putShip(shipType, line, col, direction, tabuleiro);
			break;
		case 1: 
			// Posicionar o Porta-aviões
			shipType = 'P';
			line = 'I', col = 1, direction = 'W';
			putShip(shipType, line, col, direction, tabuleiro);

			// Posicionar o Embarcação de Guerra
			shipType = 'N';
			line = 'C', col = 7, direction = 'A';
			putShip(shipType, line, col, direction, tabuleiro);

			// Posicionar o Cruzador
			shipType = 'C';		
			line = 'H', col = 5, direction = 'S';
			putShip(shipType, line, col, direction, tabuleiro);

			// Posicionar o Submarino
			shipType = 'S';
			line = 'A', col = 9, direction = 'S';
			putShip(shipType, line, col, direction, tabuleiro);

			// Posicionar o Destruidor
			shipType = 'D';
			line = 'C', col = 3, direction = 'S';
			putShip(shipType, line, col, direction, tabuleiro);
			break;
		case 2: 
			// Posicionar o Porta-aviões
			shipType = 'P';
			line = 'A', col = 0, direction = 'D';
			putShip(shipType, line, col, direction, tabuleiro);

			// Posicionar o Embarcação de Guerra
			shipType = 'N';
			line = 'C', col = 1, direction = 'D';
			putShip(shipType, line, col, direction, tabuleiro);

			// Posicionar o Cruzador
			shipType = 'C';
			line = 'E', col = 3, direction = 'D';
			putShip(shipType, line, col, direction, tabuleiro);

			// Posicionar o Submarino
			shipType = 'S';
			line = 'G', col = 7, direction = 'W';
			putShip(shipType, line, col, direction, tabuleiro);

			// Posicionar o Destruidor
			shipType = 'D';
			line = 'J', col = 4, direction = 'D';
			putShip(shipType, line, col, direction, tabuleiro);
			break;
	}
}

/**
 * Mostra o resultado do jogo de um jogador. O resultado apresenta:
 * 1) Número total de disparos realizados;
 * 2) Número de disparos na água;
 * 3) Número de disparos em embarcações, por tipo de embarcação (na ordem
 *    inversa apresentada na tabela de embarcações, ou seja, começando pelo
 *    Destruidor), e omitindo os tipos para os quais não foi atingida qualquer
 *    embarcação;
 * 4) Número de embarcações afundadas, por tipo de embarcação (na ordem
 *    inversa apresentada na tabela de embarcações, ou seja, começando pelo
 *    Destruidor), e omitindo os tipos para os quais não foi afundada qualquer
 *    embarcação.
 *
 * @param nomeJogador Nome do jogador
 * @param jogadas Jogadas realizadas pelo jogador
 * @param tabuleiro Tabuleiro do jogador
 */
void printResultados(char *nomeJogador, char jogadas[][10], char tabuleiro[][10]){
	int totalDisparos = 0, totalFogo = 0, totalAgua = 0, totalAfundado = 0;
	char embarcacoesAfundadas[5] = {'.','.','.','.','.'};
	int embarcacoesAtingidas[5] = {0,0,0,0,0};

	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 10; j++){
			// Obrigatoriamente conto um disparo, depois é verificado se a coordenada foi atingid
			totalDisparos++;
			switch(jogadas[i][j]){
				case '.':
					// Disparo não realizado
					totalDisparos--;
					break;
				case 'X':
					// Disparo que acertou alguma embarcação
					totalFogo++;
					// Verifico em qual embarcação atingiu e aumento o número de vezes em que ela foi atingida
					switch(tabuleiro[i][j]){
						case 'P':
							embarcacoesAtingidas[0] += 1;
							break;
						case 'N':
							embarcacoesAtingidas[1] += 1;
							break;
						case 'C':
							embarcacoesAtingidas[2] += 1;
							break;
						case 'S':
							embarcacoesAtingidas[3] += 1;
							break;
						case 'D':
							embarcacoesAtingidas[4] += 1;
							break;
					}
					break;
				case 'O':
					// Disparo na água
					totalAgua++;
					break;
				// Embarcações afundadas
				case 'P':
					if(embarcacoesAfundadas[0] == '.'){
						embarcacoesAfundadas[0] = 'P';
						totalAfundado++;
					}
					break;
				case 'N':
					if(embarcacoesAfundadas[1] == '.'){
						embarcacoesAfundadas[1] = 'N';
						totalAfundado++;
					}
					break;
				case 'C':
					if(embarcacoesAfundadas[2] == '.'){
						embarcacoesAfundadas[2] = 'C';
						totalAfundado++;
					}
					break;
				case 'S':
					if(embarcacoesAfundadas[3] == '.'){
						embarcacoesAfundadas[3] = 'S';
						totalAfundado++;
					}
					break;
				case 'D':
					if(embarcacoesAfundadas[4] == '.'){
						embarcacoesAfundadas[4] = 'D';
						totalAfundado++;
					}
					break;
			}
			
		}
	}

	printf("%s, seu resultado foi: \n", nomeJogador);
	printf("Número total de disparos realizados: %d\n", totalDisparos);
	printf("Número total de disparos na água: %d\n", totalAgua);
	

	if(totalAfundado != 5){
		int valor = 0;

		for(int i = 0; i < 5; valor+=embarcacoesAtingidas[i], i++);

		printf("\nNúmero de disparos em embarcações: %d\n", valor);

		if((totalDisparos - totalAgua) > 0){
			for(int i = 4; i >= 0; i--){
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

					if(embarcacoesAtingidas[i]!= 0){
						printf("\t%s, atingida %d %s\n", shipName(shipType), embarcacoesAtingidas[i], embarcacoesAtingidas[i] == 1 ? "vez" : "vezes");
					}
			}
		}
	}

	printf("\nNúmero de embarcações afundadas: %d\n", totalAfundado);

	if(totalAfundado > 0){
		printf("Embarcações afundadas: \n");
		for(int i = 4; i >= 0; i--){
				if(embarcacoesAfundadas[i]!= '.'){
					printf("\t%s\n", shipName(embarcacoesAfundadas[i]));
				}
		}
	}
}