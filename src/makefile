SDL_CFLAGS=`sdl2-config --cflags`
SDL_LDFLAGS=`sdl2-config --libs`
CC=gcc
CFLAGS=$(SDL_CFLAGS) -c -Wall #-DNDEBUG
LDFLAGS=$(SDL_LDFLAGS)
SOURCES=board.c graphics.c game.c AI.c tictactoe.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=tictactoe

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean spotless
clean:
	rm -f $(OBJECTS)

spotless: clean
	rm -f $(EXECUTABLE)

board.o: board.h
graphics.o: graphics.h board.h
AI.o: AI.h board.h game.h
game.o: game.h board.h AI.h graphics.h
tictactoe.o: game.h
