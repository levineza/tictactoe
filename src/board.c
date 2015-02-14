// Tic Tac Toe - A dark themed Tic Tac Toe game.
// Copyright (C) 2015 Zachariah Levine
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// NOTE(Zach): Definition of board_type, the implementation of the ADT Board
struct board_type {
	// NOTE(Zach): The board is a 2D-array of type Token
	Token board[NUM_ROWS][NUM_COLS];
};

// NOTE(Zach): Create an instance of Abstract Data Type Board, which is empty
Board board_create(void)
{
	Board b = (Board) malloc(sizeof(struct board_type));
	board_empty(b);
	return b;
}

// NOTE(Zach): Destroy (free the memory of) Board, b.
void board_destroy(Board b)
{
	free(b);
	return;
}

// NOTE(Zach): Return the value of the Board, b, at (row, col)
Token board_checkCell(Board b, int row, int col)
{
	// asserts turned off after testing with compiler flag -DNDEBUG
	assert(b != NULL);
	if (b == NULL) return EMPTY;
	return b->board[row][col];
}

// NOTE(Zach): Insert a token into the Board, b, at (row, col)
// Return 0 for success and -1 for failure
int board_placeToken(Board b, Token token, int row, int col)
{
	if (b == NULL) return -1;
	// asserts turned off after testing with compiler flag -DNDEBUG
	assert(0 <= row && row < NUM_ROWS);
	assert(0 <= col && col < NUM_COLS);

	if (b->board[row][col] == EMPTY) {
		b->board[row][col] = token;
		return 0;
	}
	return -1;
}

// NOTE(Zach): Empty the Board, b
void board_empty(Board b)
{
	if (b == NULL) return;
	int row, col;

	for (row = 0; row < NUM_ROWS; row++)
		for (col = 0; col < NUM_COLS; col++)
			b->board[row][col] = EMPTY;

	return;
}
