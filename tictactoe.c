#include "board.h"
#include "game.h"

int main(void)
{
	Board b = board_create();
	tictactoe(b);
	return 0;
}
