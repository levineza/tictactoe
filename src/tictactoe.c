#include "board.h"
#include "game.h"
#include "graphics.h"
#include <stdio.h>

int main(void)
{
	Board b = board_create();

	// Start SDL and create a window
//	if (!init()) {
//		printf("Failed to initialize!\n");
//	} else {
		// Load media file
//		if (!loadMedia()) {
//			printf("Failed to load media!\n");
//		} else {
			// Play Tic Tac Toe
			//tictactoe(b);
			tictactoeGraphical(b);
			//board_empty(b);
			//tictactoeGraphical(b);
			//board_empty(b);
			//tictactoe(b);
//		}
//	}

	// Destroy the board
	board_destroy(b);
	// Free resources and close SDL
//	close_sdl();
	return 0;
}
