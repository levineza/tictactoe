// Tic Tac Toe - A dark themed Tic Tac Toe game.
// Copyright (C) 2015 Zachariah Levine
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "AI.h"
#include "board.h"
#include "game.h"
#include <stdlib.h>

// Currently just makes random moves
void AI_makeMove(Board b, Token token)
{
	int row, col;

	for (;;) {
		row = rand() % 3;
		col = rand() % 3;
		if (board_checkCell(b, row, col) == EMPTY) {
			board_placeToken(b, token, row, col);
			return;
		}
	}
	return;
}

int score(Board b, Token token)
{
	GameState currentState = checkWin(b);
	if (token == X) {
		if (currentState == XWON) return 1;
		else if (currentState == OWON) return -1;
	} else { // token == O
		if (currentState == OWON) return 1;
		else if (currentState == XWON) return -1;
	}
	return 0;
}
