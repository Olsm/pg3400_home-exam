#include <stdio.h>
#include "board.h"

void flushBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

void createPlayers(char players[2][21]) {
    for (int i = 0; i < 2; ++i) {
        printf("Enter name player%d (max 20 chars): ", i);
        scanf("%20s", players[i]);  // Read max 10 chars
        flushBuffer();
    }
    printf("\n\n");
}

void playGame(Board board, char players[2][21]) {
    char field[2];
    for (int i = 0; i < 2; ++i) {
        printBoard(&board);
        printf("Player %s, enter field: ", players[i]);
        scanf("%2s", field);
        flushBuffer();
    }
}

int main(void) {
    // Create players
    char players[2][21];
    createPlayers(players);

    // Create the board
    Board currentBoard;
    initBoard(&currentBoard);

    // Start the game
    playGame(currentBoard, players);
}