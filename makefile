CC=gcc
CFLAGS=-c -Wall
LDFLAGS=

tictactoe: tictactoe.o board.o game.o AI.o
	$(CC) $(LDFLAGS) -o tictactoe tictactoe.o board.o game.o AI.o

tictactoe.o: tictactoe.c
	$(CC) $(CFLAGS) tictactoe.c

board.o: board.c board.h
	$(CC) $(CFLAGS) board.c

game.o: game.c game.h board.h AI.h
	$(CC) $(CFLAGS) game.c

AI.o: AI.c AI.h
	$(CC) $(CFLAGS) AI.c

clean:
	rm *.o tictactoe
