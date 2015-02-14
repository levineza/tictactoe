// Tic Tac Toe - A dark themed Tic Tac Toe game.
// Copyright (C) 2015 Zachariah Levine
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "board.h"

#define SCREEN_WIDTH  502
#define SCREEN_HEIGHT  502
#define TOKEN_WIDTH  100
#define TOKEN_HEIGHT  100
#define BOARD_OFFSET_Y 100
#define BOARD_OFFSET_X 100
#define BOARD_WIDTH 300
#define BOARD_HEIGHT 300

// Starts up SDL and creates window
bool init();

// Loads media
bool loadMedia();

// Frees media and shuts down SDL
void close_sdl();

// Display the Tic Tac Toe board
void displayBoard(Board b);

void displayXWins(void);
void displayOWins(void);
void displayCatsGame(void);
void displayDullToken(Token token, int row, int col);
void displayMenu(void);
void displayCreditsMenu(void);
void displayMenuLink(void);
void displayRefresh(void);

#endif // GRAPHICS_H
