/*==============================================================================
- | Filename: utils.h 
- | Programmer: Jackson Antonio do Prado Lima
- | Date: September 1, 2017
- +------------------------------------------------------------------------------                                                                       
- | Description: The file contains all of the function prototypee and standard libraries
- |              required to run the game of Battleship.
- ==============================================================================*/

void clearScreen();
void initMatrix(char tabuleiro[][10]);
void printAbout();
void printAlign(int space, char *string);
void printBattleship();
void printMatrix(char matrix[][10]);
void printMenu1();
void printMenu2();
const char * directionMessage(char direction);
const char * shipName(char ship);
const int getShipSize(char ship);

/**
 * Verifica se a coordenada é válidas para inserção de uma embarcação no tabuleiro
 * 
 * @param line Linha da matriz
 * @param col Coluna da matriz
 * @return 1 se a coordenada é válida, 0 caso contrário
 */
int checkThreshold(char line, int col);

/**
 * Verifica se a coordenada é válida para inserção de uma embarcação no tabuleiro
 * 
 * @param shipType Tipo de embarcação
 * @param line Linha da matriz
 * @param col Coluna da matriz
 * @param direction Direção do posicionamento da embarcação
 * @param tabuleiro Tabuleiro do jogo
 * @return 1 se a coordenada é válido, 0 caso contrário
 */
int checkCoordenate(char shipType, char line, int col, char direction, char tabuleiro[][10]);

/**
 * Verifica o resultado de uma jogada (disparo) da batalha naval
 * 
 * @param jogadas Jogadas realizadas pelo jogador até o momento.
 * @param tabuleiroAdversario Tabuleiro do adversário
 * @param nomeJogador Nome do jogador
 * @param nomeAdversario Nome do adversário
 */
void checkShot(char jogadas[][10], char tabuleiroAdversario[][10], char *nomeJogador, char *nomeAdversario, int line, int col);

/**
 * Mostra as informações de duas matrizes lado a lado com o nome dos jogadores. 
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
void displayGameInfo(char *nomeJogador1, char jogadas1[][10], char *nomeJogador2, char jogadas2[][10]);

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
void displayGamePlayer(char* nomeJogador, char tabuleiro[][10]);

/**
 * Realiza uma jogada (disparo) da batalha naval por um jogador
 * 
 * @param jogadas Jogadas realizadas pelo jogador até o momento.
 * @param tabuleiroAdversario Tabuleiro do adversário
 * @param nomeJogador Nome do jogador
 * @param nomeAdversario Nome do adversário
 */
void giveShot(char jogadas[][10], char tabuleiroAdversario[][10], char *nomeJogador, char *nomeAdversario);

/**
 * A máquina realiza uma jogada (disparo) da batalha naval
 * 
 * @param jogadas Jogadas realizadas pelo jogador até o momento.
 * @param tabuleiroAdversario Tabuleiro do adversário
 * @param nomeJogador Nome do jogador
 * @param nomeAdversario Nome do adversário
 */
void giveRandomShot(char jogadas[][10], char tabuleiroAdversario[][10], char *nomeJogador, char *nomeAdversario);

/**
 * Verifica se o jogo já acabou
 * 
 * @param jogadas Tabuleiro de jogadas de algum jogador
 * @return Retorna 1 se todas as embarcações foram afundadas, 0 caso contrário
 */
 int isEndGame(char jogadas[][10]);

/**
 * Coloca uma embarcação no tabulerio
 * 
 * @param shipType Tipo de embarcação
 * @param line Linha da matriz
 * @param col Coluna da matriz
 * @param direction Direção do posicionamento da embarcação
 * @param tabuleiro Tabuleiro do jogo
 */
void putShip(char shipType, char line, int col, char direction, char tabuleiro[][10]);

/**
 * Coloca as embarcações de um jogador no tabulerio.
 * 
 * @param nomeJogador Nome do jogador
 * @param tabuleiro Tabuleiro do jogador
 */
void putShips(char *nomeJogador, char tabuleiro[][10]);

/**
 * Coloca as embarcações da "máquina" no tabulerio.
 * Aleatoriamente é selecionado um tabuleiro para a máquina.
 * 
 * @param tabuleiro Tabuleiro da máquina
 */
void putShipsCOM(char tabuleiro[][10]);

 /**
 * Realiza a leitura de uma coordenada para o tabuleiro.
 * A leitura continua até que uma coordenada válida seja informada.
 * 
 * @param *line Ponteiro de uma variável para ser a linha da matriz
 * @param *col Ponteiro de uma variável para ser a coluna da matriz
 */
void readCoordenate(char *line, int *col);

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
void printResultados(char *nomeJogador, char jogadas[][10], char tabuleiro[][10]);