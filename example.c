#include <stdio.h> 

void printInit(){
	printf ("XXXXX   XXXX  XXXXXX XXXXXX XX     XXXXXX  XXXXX XX  XX XX XXXX\n");
	printf ("XX  XX XX  XX   XX     XX   XX     XX     XX     XX  XX XX XX  XX\n");
	printf ("XXXXX  XX  XX   XX     XX   XX     XXXX    XXXX  XXXXXX XX XXXX\n"); 
	printf ("XX  XX XXXXXX   XX     XX   XX     XX         XX XX  XX XX XX\n");
	printf ("XXXXX  XX  XX   XX     XX   XXXXXX XXXXXX XXXXX  XX  XX XX XX\n");
	printf ("\n\n");
	printf("**************************************************************\n");
	printf("*Bem-vindo ao jogo de batalha naval! - Exemplo trabalho UFPR *\n");
	printf("**************************************************************\n");
	printf("\n\n\n");
	printf("Você está preparado? Pois nesse jogo você irá enfrentar a máquina!\n");
	printf("Primeiro, você deve definir o tamanho do campo de batalha com dimensão MxM. Sendo que o mínimo é 10x10.\n \
	        Depois, você deve definir as posições para o seu: cruzador, encouraçado, porta-aviões, submarino e hidroavião.\n");


	printf ("RULES OF THE GAME:\n");
	printf ("1. This is a two player game.\n");
	printf ("2. Player 1 is you and Player 2 is the computer.\n");
	printf ("3. Player 1 will be prompted if user wants to manually input coordinates\n");
	printf ("   for the game board or have the computer randomly generate a game board\n");
	printf ("4. There are five types of ships to be placed by longest length to the\n"); 
	printf ("   shortest; [c] Carrier has 5 cells, [b] Battleship has 4 cells, [r] Cruiser\n");
	printf ("   has 3 cells, [s] Submarine has 3 cells, [d] Destroyer has 2 cells\n");
	printf ("5. The computer randomly selects which player goes first\n");
	printf ("6. The game begins as each player tries to guess the location of the ships\n");
	printf ("   of the opposing player's game board; [*] hit and [m] miss\n");
	printf ("7. First player to guess the location of all ships wins\n\n");


}
int main() {
	printInit();
	getchar();
	return 0;
}