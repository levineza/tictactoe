SDL_CFLAGS=`sdl2-config --cflags`
SDL_LDFLAGS=`sdl2-config --libs`
CC=gcc
CFLAGS=$(SDL_CFLAGS) -c -Wall #-DNDEBUG
LDFLAGS=$(SDL_LDFLAGS)

tictactoe: tictactoe.o board.o game.o AI.o graphics.o
	$(CC) -o tictactoe tictactoe.o board.o game.o AI.o graphics.o $(LDFLAGS)

tictactoe.o: tictactoe.c
	$(CC) $(CFLAGS) tictactoe.c

board.o: board.c board.h
	$(CC) $(CFLAGS) board.c

game.o: game.c game.h board.h AI.h
	$(CC) $(CFLAGS) game.c

AI.o: AI.c AI.h
	$(CC) $(CFLAGS) AI.c

graphics.o: graphics.c graphics.h game.c game.h board.c board.h
	$(CC) $(CFLAGS) graphics.c 

clean:
	rm *.o tictactoe
