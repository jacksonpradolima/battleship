#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "utils.h"

#define SIZE 10

void run(int isPvCOM);

int main(){
	clearScreen();
	printBattleship();
	printMenu1();

	char optionMenu1;
	char optionMenu2;

	do{
		scanf(" %c", &optionMenu1);
		switch(optionMenu1){
			case '1':
				clearScreen();
				printBattleship();
				printMenu2();

				do{
					scanf(" %c", &optionMenu2);
					switch(optionMenu2){
						case '1':
							clearScreen();
							printBattleship();
							printf("\n\nBem-vindo à opção de jogo PvCOM!\n\n\n");
							run(1);
							clearScreen();
							printBattleship();
							printMenu2();
							break;
						case '2':
							clearScreen();
							printBattleship();
							printf("\n\nBem-vindo à opção de jogo PvP!\n\n\n");
							run(0);
							clearScreen();
							printBattleship();
							printMenu2();
							break;
						case '3':break;
						default:
							printf("Opção de menu inválida!\n");
					}

				}while((optionMenu2)!= '2');

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
			case '3': break;
			default:
				printf("Opção de menu inválida!\n");
		}
	}while((optionMenu1 = getchar())!= '3');

	return(0);
}

void run(int isPvCOM){
	while(1){
		// inicio o tabuleiro para o primeiro jogador
		char tabuleiro1[SIZE][SIZE];
		char jogadas1[SIZE][SIZE];
		char nomeJogador1[100];

		printf("Jogador 1, informe o seu nome: ");
		scanf("%s", nomeJogador1);
		initMatrix(jogadas1);
		putShips(nomeJogador1, tabuleiro1);

		// inicio o tabuleiro para o segundo jogador
		char tabuleiro2[SIZE][SIZE];
		char jogadas2[SIZE][SIZE];
		char nomeJogador2[100] = "COMPUTER"; // Nome default
		initMatrix(jogadas2);

		if(isPvCOM){
			putShipsCOM(tabuleiro2);
		}else{
			printf("Jogador 2, informe o seu nome: ");
			scanf("%s", nomeJogador2);
			putShips(nomeJogador2, tabuleiro1);
		}

		clearScreen();
		printBattleship();

		char moeda;
		printf("Jogador 1, escolha cara (C) ou coroa (O): ");
		do{
			scanf(" %c", &moeda);
			if(moeda != 'C' && moeda != 'O'){
				printf("Opção inválida! Tente novamente.\n");
			}
		}while(moeda != 'C' && moeda != 'O');
		
		srand(time(NULL));
		int primeiroJogador = 2 * (rand() / ((double)RAND_MAX + 1));

		char jogarNovamente;
		clearScreen();
		printBattleship();

		printf("O jogador %s irá começar! Preparem-se! \n\n", (primeiroJogador == (moeda == 'C' ? 0 : 1)) ? nomeJogador1 : nomeJogador2);
		
		sleep(2);

		do{
			displayGameInfo(nomeJogador1, jogadas1, nomeJogador2, jogadas2);
			printf("\nAgora é a vez do %s \n", primeiroJogador == 0 ? nomeJogador1 : nomeJogador2);
			switch(primeiroJogador){
				case 0:
					// Jogador 1
					giveShot(jogadas1, tabuleiro2, nomeJogador1, nomeJogador2);
					break;
				case 1:
					// jogador 2
					if(isPvCOM){
						sleep(2);
						giveRandomShot(jogadas2, tabuleiro1, nomeJogador2, nomeJogador1);
					}else{
						giveShot(jogadas2, tabuleiro1, nomeJogador2, nomeJogador1);
					}
					break;
			}

			// Alterno a jogada
			primeiroJogador = primeiroJogador == 0 ? 1 : 0;
		}while(!isEndGame(primeiroJogador == 0 ? jogadas2 : jogadas1)); // Comparo o inverso pois mudei o jogador anteriormente 

		printf("\n\n\n FIM DE JOGO! %s venceu!\n", primeiroJogador == 0 ? nomeJogador2 : nomeJogador1);
		//printResultados(nomeJogador1, jogadas1);
		printf("\n");
		//printResultados(nomeJogador2, jogadas2);
		printf("Pressione S para jogar novamente ou N para sair.");
		do{
			scanf(" %c", &jogarNovamente);
			if(jogarNovamente != 'S' && jogarNovamente != 'N'){
				printf("Opção inválida! Tente novamente.\n");
			}
		}while(jogarNovamente != 'S' && jogarNovamente != 'N');

		if(jogarNovamente != 'S'){
			break;
		}
	}
}