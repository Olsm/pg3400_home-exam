CC = gcc
CFLAGS = -Wall -Wextra
SRC = game.c board.c
DEPS = $(SRC:.c=.h)
SRC += main.c
OBJ = $(SRC:.c=.o)
EXE = reversi

all: $(SRC) $(EXE)

$(EXE): $(OBJ)
        $(CC) -o $@ $(OBJ)

.o: .c $(DEPS)
        $(CC) -c -o $@ $< $(CFLAGS)

clean:
        rm -f $(OBJ) $(EXE)

remake: clean all