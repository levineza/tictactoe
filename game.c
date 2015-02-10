#include "game.h"
#include "AI.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum {HUMAN, COMPUTER} Player; 
typedef enum {INPROGRESS, CATSGAME, XWON, OWON} GameState;

static void switchPlayer(Player *player);
static void switchToken(Token *token);
static void playerMove(Board b, Token token);
static GameState checkWin(Board b);
char tokenToChar(Token token);
static void printBoard(Board b);
static void dump_line(void);
static int *read_input(void);

Token tictactoe(Board b)
{
	Player currentPlayer;
	Token currentToken = X;
	GameState currentState = INPROGRESS;
	srand((unsigned) time(NULL));

	if (rand() % 2 == 0) {
		currentPlayer = HUMAN;
	} else {
		currentPlayer = COMPUTER;
	}
	printBoard(b);

	while((currentState = checkWin(b)) == INPROGRESS) {
		if (currentPlayer == HUMAN) {
			playerMove(b, currentToken);
			switchPlayer(&currentPlayer);
			switchToken(&currentToken);
		} else {
			playerMove(b, currentToken);
			//AI_makeMove(b, currentToken);
			switchPlayer(&currentPlayer);
			switchToken(&currentToken);
		}
		printBoard(b);
	}

	if (currentState == XWON) {
		printf("   %c Won!\n", tokenToChar(X));
		return X;
	} else if (currentState == OWON) {
		printf("   %c Won!\n", tokenToChar(O));
		return O;
	} else {
		printf(" Cat's Game!\n");
		return EMPTY;
	}
}

static void switchPlayer(Player *player)
{
	if (*player == HUMAN) {
		*player = COMPUTER;
	} else {
		*player = HUMAN;
	}
}

static void switchToken(Token *token)
{
	if (*token == X) {
		*token = O;
	} else {
		*token = X;
	}
}

static void dump_line(void)
{
	while(getchar() != '\n'); // Skip the rest of the line
}

static int *read_input(void)
{
	int ch, ch0, *a = NULL;

	while((ch = getchar()) == ' '); // Skip whitespace
	if ('0' <= ch && ch <= '2') {
		ch0 = ch;
	} else {
		dump_line();
		return NULL;
	}

	while((ch = getchar()) == ' '); // Skip whitespace
	if (ch != ',') { printf("No comma!\n"); dump_line(); return NULL;	}
	while((ch = getchar()) == ' '); // Skip whitespace
	if ('0' > ch || ch > '2') { dump_line(); return NULL; }
	dump_line();

	a = malloc(2*sizeof(int));
	a[0] = ch0 - '0';
	a[1] = ch - '0';

	return a;
}

static void playerMove(Board b, Token token)
{
	int row, col, *a;
	printf("Player %c, enter your move (row, col): ", token == X ? 'X' : 'O');
	a = read_input();

	while (a == NULL || board_checkCell(b, a[0], a[1]) != EMPTY) {
		printf("That move is invalid.\n");
		printf("Player %c, enter your move (row, col): ", token == X ? 'X' : 'O');
		a = read_input();
	}

	board_placeToken(b, token, a[0], a[1]);
	free(a);
}

static GameState checkWin(Board b)
{
	int row, col, count;

	//check rows
	for (row = 0; row < NUM_ROWS; row++) {
		for (col = 1, count = 1; col < NUM_COLS; col++) {
			if (board_checkCell(b, row, 0) == EMPTY) break;
			if (board_checkCell(b, row, 0) == board_checkCell(b, row, col)) {
				count++;
			}
		}
		if (count == 3) {
			if (board_checkCell(b, row, 0) == X) return XWON;
			else return OWON;
		}
	}

	//check columns
	for (col = 0; col < NUM_COLS; col++) {
		for (row = 1, count = 1; row < NUM_ROWS; row++) {
			if (board_checkCell(b, 0, col) == EMPTY) break;
			if (board_checkCell(b, 0, col) == board_checkCell(b, row, col)) {
				count++;
			}
		}
		if (count == 3) {
			if (board_checkCell(b, 0, col) == X) return XWON;
			else return OWON;
		}
	}

	// check diagonal down to right
	for (row = 1, col = 1, count = 1; row < NUM_ROWS; row++, col++) {
		if (board_checkCell(b, 0, 0) == EMPTY) break;
		if (board_checkCell(b, 0, 0) == board_checkCell(b, row, col)) {
			count++;
		}
	}
	if (count == 3) {
		if (board_checkCell(b, 0, 0) == X) return XWON;
		else return OWON;
	}

	// check diagonal down to left
	for (row = 1, col = 1, count = 1; row < NUM_ROWS; row++, col--) {
		if (board_checkCell(b, 0, 2) == EMPTY) break;
		if (board_checkCell(b, 0, 2) == board_checkCell(b, row, col)) {
			count++;
		}
	}
	if (count == 3) {
		if (board_checkCell(b, 0, 2) == X) return XWON;
		else return OWON;
	}

	// check cat's game
	for (row = 0, count = 0; row < NUM_ROWS; row++) {
		for (col = 0; col < NUM_COLS; col++) {
			if (board_checkCell(b, row, col) != EMPTY) count++;
		}
	}
	if (count == NUM_ROWS * NUM_COLS) return CATSGAME;

	return INPROGRESS;
}

char tokenToChar(Token token)
{
	switch(token) {
		case X:
			return 'X';
		case O:
			return 'O';
		default:
			return ' ';
	}
}

static void printBoard(Board b)
{
	int row, col;

	for (row = 0; row < NUM_ROWS; row++) {
		for (col = 0; col < NUM_COLS; col++) {
			if (col < NUM_COLS - 1)
				printf(" %c |", tokenToChar(board_checkCell(b, row, col)));
			else
				printf(" %c \n", tokenToChar(board_checkCell(b, row, col)));
		}
		if (row < NUM_ROWS -1)
			printf("___|___|___\n");
		else
			printf("   |   |   \n");
	}
}
