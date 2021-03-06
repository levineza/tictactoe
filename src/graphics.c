// Tic Tac Toe - A dark themed Tic Tac Toe game.
// Copyright (C) 2015 Zachariah Levine
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "graphics.h"
#include "board.h"

#define CHECK_POINT printf("*** Reached line %d of file %s ***\n"\
									, __LINE__, __FILE__)

// Global window/image declarations.
SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL;
SDL_Surface *gBoard = NULL;
SDL_Surface *gXToken = NULL;
SDL_Surface *gOToken = NULL;
SDL_Surface *gBackground = NULL;
SDL_Surface *gTitle = NULL;
SDL_Surface *gXWins = NULL;
SDL_Surface *gOWins = NULL;
SDL_Surface *gCatsGame = NULL;
SDL_Surface *gMainMenu = NULL;
SDL_Surface *gMenuLink = NULL;
SDL_Surface *gRefresh = NULL;
SDL_Surface *gCreditsMenu = NULL;

// Loads individual image
SDL_Surface *loadSurface(char *path);

// Blits the token to a cell in the BOARD
void blitToken(Token tokenType, int row, int col);

// Blit all tokens currently on the board to the window surface
void blitTokens(Board b);

bool init() {
	// Initialization flag.
	bool success = true;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	} else {
		// Create window
		gWindow = SDL_CreateWindow("Tic Tac Toe", 
       	                        SDL_WINDOWPOS_UNDEFINED,
         	                     SDL_WINDOWPOS_UNDEFINED,
            	                  SCREEN_WIDTH,
               	               SCREEN_HEIGHT,
                  	            0);
		if(gWindow == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", 
			SDL_GetError());
		} else {
			// Get window surface
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}
	return success;
}

bool loadMedia() {
	// Loading success flag
	bool success = true;

	// Load the background
	gBackground = loadSurface("../misc/backgroundblack.bmp");
	if (gBackground == NULL) {
		printf("Failed to load background!\n");
		success = false;
	}

	// Load the main menu
	gMainMenu = loadSurface("../misc/mainmenuneon.bmp");
	if (gMainMenu == NULL) {
		printf("Failed to load main menu!\n");
		success = false;
	}

	// Load the credit menu
	gCreditsMenu = loadSurface("../misc/credit_menu.bmp");
	if (gCreditsMenu == NULL) {
		printf("Failed to load credit menu!\n");
		success = false;
	}

	// Load the menu link for the game board
	gMenuLink = loadSurface("../misc/menuneon2.bmp");
	if (gMenuLink == NULL) {
		printf("Failed to load menu link used on the game board!\n");
		success = false;
	}
	SDL_SetColorKey(gMenuLink, SDL_TRUE, SDL_MapRGB(gMenuLink->format, 0, 0, 0));

	// Load the refresh symbol
	gRefresh = loadSurface("../misc/refreshneon.bmp");
	if (gRefresh == NULL) {
		printf("Failed to load refresh symbol used on the game board!\n");
		success = false;
	}
	SDL_SetColorKey(gRefresh, SDL_TRUE, SDL_MapRGB(gRefresh->format, 0, 0, 0));

	// Load the title
	gTitle = loadSurface("../misc/titleneon2.bmp");
	if (gTitle == NULL) {
		printf("Failed to load title!\n");
		success = false;
	}
	// Make all black pixels transparent
	SDL_SetColorKey(gTitle, SDL_TRUE, SDL_MapRGB(gTitle->format, 0, 0, 0));

	// Load message that displays when X wins
	gXWins = loadSurface("../misc/xwins.bmp");
	if (gXWins == NULL) {
		printf("Failed to load message that displays when X wins!\n");
		success = false;
	}
	// Make all black pixels transparent
	SDL_SetColorKey(gXWins, SDL_TRUE, SDL_MapRGB(gXWins->format, 0, 0, 0));

	// Load message that displays when O wins
	gOWins = loadSurface("../misc/owins.bmp");
	if (gOWins == NULL) {
		printf("Failed to load message that displays when O wins!\n");
		success = false;
	}
	// Make all black pixels transparent
	SDL_SetColorKey(gOWins, SDL_TRUE, SDL_MapRGB(gOWins->format, 0, 0, 0));

	// Load message that displays when it is a Cat's Game
	gCatsGame = loadSurface("../misc/catsgame.bmp");
	if (gCatsGame == NULL) {
		printf("Failed to load message that displays when it is a Cat's Game!\n");
		success = false;
	}
	// Make all black pixels transparent
	SDL_SetColorKey(gCatsGame, SDL_TRUE, SDL_MapRGB(gCatsGame->format, 0, 0, 0));

	// Load splash image
	//gBoard = loadSurface("../misc/board.bmp");
	gBoard = loadSurface("../misc/boardneon2.bmp");
	if (gBoard == NULL) {
		printf( "Failed to load board!\n" );
		success = false;
	}
	// Make all black pixels transparent
	SDL_SetColorKey(gBoard, SDL_TRUE, SDL_MapRGB(gBoard->format, 0, 0, 0));

	// Load the X token
	//gXToken = loadSurface("../misc/x.bmp");
	gXToken = loadSurface("../misc/Xneon2.bmp");
	if (gXToken == NULL) {
		printf("Failed to load X token!\n");
		success = false;
	}
	// Make all black pixels transparent
	SDL_SetColorKey(gXToken, SDL_TRUE, SDL_MapRGB(gXToken->format, 0, 0, 0));

	// Load the O token
	//gOToken = loadSurface("../misc/o.bmp");
	gOToken = loadSurface("../misc/Oneon2.bmp");
	if (gOToken == NULL) {
		printf("Failed to load O token!\n");
		success = false;
	}
	// Make all black pixels transparent
	SDL_SetColorKey(gOToken, SDL_TRUE, SDL_MapRGB(gXToken->format, 0, 0, 0));

	return success;
}

void close_sdl() {
  // de-allocate surfaces
  SDL_FreeSurface(gBoard);
  SDL_FreeSurface(gXToken);
  SDL_FreeSurface(gOToken);
  SDL_FreeSurface(gBackground);
  SDL_FreeSurface(gTitle);
  SDL_FreeSurface(gXWins);
  SDL_FreeSurface(gOWins);
  SDL_FreeSurface(gCatsGame);
  SDL_FreeSurface(gMainMenu);
  SDL_FreeSurface(gMenuLink);
  SDL_FreeSurface(gRefresh);
  SDL_FreeSurface(gCreditsMenu);

	gBoard = NULL;
	gXToken = NULL;
	gOToken = NULL;
	gBackground = NULL;
	gTitle = NULL;
	gXWins = NULL;
	gOWins = NULL;
	gCatsGame = NULL;
	gMainMenu = NULL;
	gMenuLink = NULL;
	gRefresh = NULL;
	gCreditsMenu = NULL;

	// Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	// Quit SDL subsystems
	SDL_Quit();
}

// Loads bitmaps
SDL_Surface *loadSurface(char *path)
{
	// The final optimized image
	SDL_Surface *optimizedSurface = NULL;

	// Load image at specified path
	SDL_Surface *loadedSurface = SDL_LoadBMP(path);
	if(loadedSurface == NULL) {
		printf("Unable to load image %s! SDL Error: %s\n", path, SDL_GetError());
	} else {
		// Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
		if(optimizedSurface == NULL) {
			printf("Unable to optimize image %s! SDL Error: %s\n", path, SDL_GetError());
		}

		// Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return optimizedSurface;
}

// Blits the token to a cell in the BOARD
void blitToken(Token tokenType, int row, int col)
{
		SDL_Surface *token;
		if (tokenType == X) token = gXToken;
		else if (tokenType == O) token = gOToken;

		// Determine the position for the token
		SDL_Rect tokenRect;
		tokenRect.x = BOARD_OFFSET_X + TOKEN_WIDTH * col;
		tokenRect.y = BOARD_OFFSET_Y + TOKEN_HEIGHT * row;
		tokenRect.w = TOKEN_WIDTH;
		tokenRect.h = TOKEN_HEIGHT;

		// Blit the token to the desired position
      SDL_BlitSurface(token, NULL, gScreenSurface, &tokenRect);  
		return;
}

// Blit all tokens currently on the board to the window surface
void blitTokens(Board b)
{
	int row, col;

	// Loop through all the cells of the board and if there is a
	// token present blit it to the window surface
	for (row = 0; row < NUM_ROWS; row++) {
		for (col = 0; col < NUM_COLS; col++) {
			if (board_checkCell(b, row, col) == X) {
				blitToken(X, row, col);
			} else if (board_checkCell(b, row, col) == O) {
				blitToken(O, row, col);
			}
		}
	}
}

void displayBoard(Board b)
{
	SDL_BlitSurface(gBackground, NULL, gScreenSurface, NULL);
	SDL_BlitSurface(gTitle, NULL, gScreenSurface, NULL);
	//SDL_BlitSurface(gBoard, NULL, gScreenSurface, NULL);
	blitTokens(b);
	SDL_BlitSurface(gBoard, NULL, gScreenSurface, NULL);
	displayMenuLink();
	displayRefresh();
	SDL_UpdateWindowSurface(gWindow);
}

void displayXWins(void)
{
	// Determine the position for the X Wins! message 
	SDL_Rect tokenRect;
	tokenRect.x = 0;
	tokenRect.y = BOARD_OFFSET_Y + BOARD_HEIGHT;
	tokenRect.w = SCREEN_WIDTH;
	tokenRect.h = TOKEN_HEIGHT;

	// Blit the message to the desired position
	SDL_BlitSurface(gXWins, NULL, gScreenSurface, &tokenRect);  
	SDL_UpdateWindowSurface(gWindow);
	return;
}

void displayOWins(void)
{
	// Determine the position for the O Wins! message
	SDL_Rect tokenRect;
	tokenRect.x = 0;
	tokenRect.y = BOARD_OFFSET_Y + BOARD_HEIGHT;
	tokenRect.w = SCREEN_WIDTH;
	tokenRect.h = TOKEN_HEIGHT;

	// Blit the message to the desired position
	SDL_BlitSurface(gOWins, NULL, gScreenSurface, &tokenRect);  
	SDL_UpdateWindowSurface(gWindow);
	return;
}

void displayCatsGame(void)
{
	// Determine the position for the Cat's Game message
	SDL_Rect tokenRect;
	tokenRect.x = 0;
	tokenRect.y = BOARD_OFFSET_Y + BOARD_HEIGHT;
	tokenRect.w = SCREEN_WIDTH;
	tokenRect.h = TOKEN_HEIGHT;

	// Blit the message to the desired position
	SDL_BlitSurface(gCatsGame, NULL, gScreenSurface, &tokenRect);  
	SDL_UpdateWindowSurface(gWindow);
	return;
}

void displayDullToken(Token tokenType, int row, int col)
{
		SDL_Surface *token;
		if (tokenType == X) token = gXToken;
		else if (tokenType == O) token = gOToken;

	SDL_SetSurfaceColorMod(token, 127, 127, 127);
	blitToken(tokenType, row, col);
	SDL_UpdateWindowSurface(gWindow);
	SDL_SetSurfaceColorMod(token, 255, 255, 255);
	return;
}

void displayMenu(void)
{
	SDL_BlitSurface(gMainMenu, NULL, gScreenSurface, NULL);
	SDL_UpdateWindowSurface(gWindow);
	return;
}

void displayCreditsMenu(void)
{
	SDL_BlitSurface(gCreditsMenu, NULL, gScreenSurface, NULL);
	SDL_UpdateWindowSurface(gWindow);
	return;
}

void displayMenuLink(void)
{
	// Determine the position for the Cat's Game message
	SDL_Rect tokenRect;
	//tokenRect.x = 0;
	//tokenRect.y = BOARD_OFFSET_Y + BOARD_HEIGHT;
	//tokenRect.w = SCREEN_WIDTH;
	//tokenRect.h = TOKEN_HEIGHT;
	tokenRect.x = 426;
	tokenRect.y = BOARD_OFFSET_Y + BOARD_HEIGHT + 70;
	tokenRect.w = 80;
	tokenRect.h = 39;

	// Blit the message to the desired position
	SDL_BlitSurface(gMenuLink, NULL, gScreenSurface, &tokenRect);  
	//SDL_UpdateWindowSurface(gWindow);
	return;
}

void displayRefresh(void)
{
	// Determine the position for the Cat's Game message
	SDL_Rect tokenRect;
	tokenRect.x = 0;
	tokenRect.y = BOARD_OFFSET_Y + BOARD_HEIGHT + 60;
	tokenRect.w = 40;
	tokenRect.h = 40;

	// Blit the message to the desired position
	//SDL_BlitSurface(gRefresh, NULL, gScreenSurface, &tokenRect);  
	SDL_BlitScaled(gRefresh, NULL, gScreenSurface, &tokenRect);  
	//SDL_UpdateWindowSurface(gWindow);
	return;
	
}
