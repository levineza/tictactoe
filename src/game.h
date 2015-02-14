// Tic Tac Toe - A dark themed Tic Tac Toe game.
// Copyright (C) 2015 Zachariah Levine
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef GAME_H
#define GAME_H

#include "board.h"

typedef enum {INPROGRESS, CATSGAME, XWON, OWON} GameState;

int tictactoe(void);
GameState checkWin(Board b);

#endif
