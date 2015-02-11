#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "board.h"

#define SCREEN_WIDTH  502 //302
#define SCREEN_HEIGHT  502 //302
#define TOKEN_WIDTH  100
#define TOKEN_HEIGHT  100
#define GRID_OFFSET_Y 100  //1
#define GRID_OFFSET_X 100  //1
#define GRID_WIDTH 300
#define GRID_HEIGHT 300

// Global window/image declarations.
// Eventually these will be local to the graphics module and will
// be removed from here
extern SDL_Window *gWindow;
extern SDL_Surface *gScreenSurface;
extern SDL_Surface *gBoard;
extern SDL_Surface *gXToken;
extern SDL_Surface *gOToken;
extern SDL_Surface *gBackground;

// Starts up SDL and creates window
bool init();

// Loads media
bool loadMedia();

// Frees media and shuts down SDL
void close_sdl();

// Move this declaration into graphics.cpp (maybe not this one)
// Blits the token to a cell in the grid
void blitToken(Token tokenType, int row, int col);

// Blit all tokens currently on the board to the window surface
void blitTokens(Board b);

// Display the Tic Tac Toe board
void displayBoard(Board b);

void displayXWins(void);
void displayOWins(void);
void displayCatsGame(void);

#endif // GRAPHICS_H
