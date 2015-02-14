// Tic Tac Toe - A dark themed Tic Tac Toe game.
// Copyright (C) 2015 Zachariah Levine
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "game.h"
#include "AI.h"
#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef enum {HUMAN, COMPUTER} Player; 
typedef enum {MAINMENU, ONEPLAYER, TWOPLAYER, CREDITS, QUIT, DONOTHING} MainMenuState;

static void switchPlayer(Player *player);
static void switchToken(Token *token);
static void playerMove(Board b, Token token);
char tokenToChar(Token token);
static void printBoard(Board b);
static void dump_line(void);
static int *read_input(void);
static MainMenuState playerMoveGraphical(Board b, Token token, int numPlayers);
static void displayGameState(GameState state);
Token tictactoeText(Board b);
MainMenuState tictactoeGraphical(Board b, int numPlayers);
MainMenuState handleMenuMouseClick(int x, int y);
MainMenuState creditsMenu(void);
MainMenuState mainMenu(void);

int tictactoe(void)
{
	srand((unsigned) time(NULL));
	// Start SDL and create a window
	if (!init()) {
		printf("Failed to initialize!\n");
	} else {
		// Load media file
		if (!loadMedia()) {
			printf("Failed to load media!\n");
		} else {
			// State of the menu
			MainMenuState currentState = MAINMENU;

			Board b;
			if ((b = board_create()) == NULL) currentState = QUIT;

			while(currentState != QUIT) {
				switch (currentState) {
					case  MAINMENU:
						currentState = mainMenu();
						break;
					case ONEPLAYER:
						board_empty(b);
						currentState = tictactoeGraphical(b, 1);
						break;
					case TWOPLAYER:
						board_empty(b);
						currentState = tictactoeGraphical(b, 2);
						break;
					case CREDITS:
						currentState = creditsMenu();
						break;
					default:
						break;
				}
			}
			board_destroy(b);
		}
	}
	close_sdl();
	return 0;
}

MainMenuState mainMenu(void)
{
	MainMenuState currentState = MAINMENU;
	displayMenu();
	// Event handler
	SDL_Event e;

	int x, y;

	while (currentState == MAINMENU) {
		// Wait for an event to occur
		SDL_WaitEvent(&e);

		// User requests quit
		if (e.type == SDL_QUIT) {
			return QUIT;
		} else if (e.type == SDL_MOUSEBUTTONDOWN &&
			e.button.button == SDL_BUTTON_LEFT) {

			x = e.button.x;
			y = e.button.y;

			currentState = handleMenuMouseClick(x, y);
		} else {
			//handleMenuMouseMotion();
		}
	}
	return currentState;
}

MainMenuState creditsMenu(void)
{
	displayCreditsMenu();
	// Event handler
	SDL_Event e;

	int x, y;

	for (;;) {
		// Wait for an event to occur
		SDL_WaitEvent(&e);

		// User requests quit
		if (e.type == SDL_QUIT) {
			return QUIT;
		} else if (e.type == SDL_MOUSEBUTTONDOWN &&
			e.button.button == SDL_BUTTON_LEFT) {

			x = e.button.x;
			y = e.button.y;
			if (x >= 48 && y>= 413 && x <= 454 && y <= 465) return MAINMENU;
		}
	}
}

MainMenuState tictactoeGraphical(Board b, int numPlayers)
{
	Player currentPlayer;
	Token currentToken = X;
	GameState currentState = INPROGRESS;
	MainMenuState menuState = DONOTHING;

	if (rand() % 2 == 0) {
		currentPlayer = HUMAN;
	} else {
		currentPlayer = COMPUTER;
	}

	displayBoard(b);
	currentState = checkWin(b);
	displayGameState(currentState);

	// Main loop flag
	bool quit = false;

	// Event handler
	SDL_Event e;

	while(!quit) {
		// Wait for an event to occur
		SDL_WaitEvent(&e);

		// User requests quit
		if (e.type == SDL_QUIT) {
			quit = true;
		} else if (e.type == SDL_MOUSEBUTTONDOWN &&
			e.button.button == SDL_BUTTON_LEFT) {
			int x, y;
			x = e.button.x;
			y = e.button.y;
			// If the menu button was clicked
			if (x >= 426 && y >= BOARD_OFFSET_Y + BOARD_HEIGHT + 70) {
				return MAINMENU;
			// If the refresh button was clicked
			} else if (x <= 40 && y >= BOARD_OFFSET_Y + BOARD_HEIGHT + 60) {
				if (numPlayers == 1) return ONEPLAYER;
				if (numPlayers == 2) return TWOPLAYER;
			}
		} else {
			if (currentState != INPROGRESS) continue;
			if (currentPlayer == HUMAN) {
				menuState = playerMoveGraphical(b, currentToken, numPlayers);
				switchPlayer(&currentPlayer);
				switchToken(&currentToken);
			} else {
				if (numPlayers == 2) {
					menuState = playerMoveGraphical(b, currentToken, numPlayers);
				} else if (numPlayers == 1) {
					AI_makeMove(b, currentToken);
				}
				switchPlayer(&currentPlayer);
				switchToken(&currentToken);
			}
			if (menuState == QUIT) return QUIT;
			else if (menuState == MAINMENU) return MAINMENU;
			else if (menuState == ONEPLAYER) return ONEPLAYER;
			else if (menuState == TWOPLAYER) return TWOPLAYER;
			displayBoard(b);
			if ((currentState = checkWin(b)) != INPROGRESS) {
				displayGameState(currentState);
			}
		}
		SDL_Delay(32);
		SDL_FlushEvent(SDL_MOUSEMOTION);
	}
	return QUIT;
}

Token tictactoeText(Board b)
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

static void displayGameState(GameState state)
{
	if (state == XWON) {
		displayXWins();
	} else if (state == OWON) {
		displayOWins();
	} else if (state == CATSGAME) {
		displayCatsGame();
	}
	return;
}

MainMenuState handleMenuMouseClick(int x, int y)
{
	if (x >= 102 && y>= 145 && x <= 398 && y <= 211) return ONEPLAYER;
	if (x >= 96 && y>= 221 && x <= 406 && y <= 287) return TWOPLAYER;
	if (x >= 338 && y>= 441 && x <= 493 && y <= 493) return CREDITS;
	if (x >= 190 && y>= 297 && x <= 313 && y <= 353) return QUIT;
	return MAINMENU;
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

static MainMenuState playerMoveGraphical(Board b, Token token, int numPlayers)
{
	bool tokenPlaced = false;
	int x, y;
	int row, col, row_old, col_old;
	SDL_Event e;
	while(!tokenPlaced) {
		SDL_WaitEvent(&e);
		if (e.type == SDL_QUIT) return QUIT;
		else if (e.type == SDL_MOUSEBUTTONDOWN &&
					e.button.button == SDL_BUTTON_LEFT) {
			x = e.button.x;
			y = e.button.y;
			// If menu was clicked
			if (x >= 426 && y >= BOARD_OFFSET_Y + BOARD_HEIGHT + 70) return MAINMENU;
			// If refresh was clicked
			if (x <= 40 && y >= BOARD_OFFSET_Y + BOARD_HEIGHT + 60) {
				if (numPlayers == 1) return ONEPLAYER;
				if (numPlayers == 2) return TWOPLAYER;
			}
			// If the click was outside the board
			if (x <= BOARD_OFFSET_X || x >= BOARD_OFFSET_X + BOARD_WIDTH) continue;
			if (y <= BOARD_OFFSET_Y || y >= BOARD_OFFSET_Y + BOARD_HEIGHT) continue;

			row = (y - BOARD_OFFSET_Y)/TOKEN_HEIGHT;
			col = (x - BOARD_OFFSET_X)/TOKEN_WIDTH;
			//if (row < 0 || row > NUM_ROWS) continue;
			//if (col < 0 || col > NUM_COLS) continue;
			if (board_checkCell(b, row, col) != EMPTY) continue;
			board_placeToken(b, token, row, col);
			tokenPlaced = true;
		} else {
			SDL_GetMouseState( &x, &y );
			//printf("x = %d, y = %d\n", x, y); // Testing
			// If the click was outside the board
			if (x <= BOARD_OFFSET_X || x >= BOARD_OFFSET_X + BOARD_WIDTH) continue;
			if (y <= BOARD_OFFSET_Y || y >= BOARD_OFFSET_Y + BOARD_HEIGHT) continue;

			row = (y - BOARD_OFFSET_Y)/TOKEN_HEIGHT;
			col = (x - BOARD_OFFSET_X)/TOKEN_WIDTH;
			if (row == row_old && col == col_old) continue;
			if (board_checkCell(b, row, col) == EMPTY) {
				displayBoard(b);
				displayDullToken(token, row, col);
			}
			row_old = row;
			col_old = col;
			SDL_Delay(32);
			SDL_FlushEvent(SDL_MOUSEMOTION);
		}
	}
	return DONOTHING;
}

static void playerMove(Board b, Token token)
{
	int *a;
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

GameState checkWin(Board b)
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

	printf("\n     0   1   2 \n");
	printf("   ************\n");
	for (row = 0; row < NUM_ROWS; row++) {
		printf(" %d *", row);
		for (col = 0; col < NUM_COLS; col++) {
			if (col < NUM_COLS - 1)
				printf(" %c |", tokenToChar(board_checkCell(b, row, col)));
			else
				printf(" %c \n", tokenToChar(board_checkCell(b, row, col)));
		}
		if (row < NUM_ROWS -1)
			printf("   *___|___|___\n");
		else
			printf("   *   |   |   \n");
	}
}
