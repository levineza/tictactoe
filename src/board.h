// Tic Tac Toe - A dark themed Tic Tac Toe game.
// Copyright (C) 2015 Zachariah Levine
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef BOARD_H // NOTE(Zach): This is an include guard
#define BOARD_H

#define NUM_ROWS 3
#define NUM_COLS 3

// NOTE(Zach): Create a new type called Token
typedef enum {EMPTY, X, O} Token;

// NOTE(Zach): Board is a pointer to the incomplete type board_type
typedef struct board_type *Board;

// NOTE(Zach): Create an instance of Abstract Data Type board, which is empty
Board board_create(void);

// NOTE(Zach): Destroy (free the memory of) Board, b
void board_destroy(Board b);

// NOTE(Zach): Return the value of the Board, b, at (row, col)
Token board_checkCell(Board b, int row, int col);

// NOTE(Zach): Insert a token into the Board, b, at (row, col)
// Return 0 for success and -1 for failure
int board_placeToken(Board b, Token token, int row, int col);

// NOTE(Zach): Empty the Board, b
void board_empty(Board b);

#endif // BOARD_H
