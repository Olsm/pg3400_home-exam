#include <stdio.h>
#include "board.h"
#include "game.h"

void createPlayers(char players[2][21]) {
    for (int i = 0; i < 2; ++i) {
        printf("Enter name player %d (max 20 chars): ", i+1);
        scanf("%20s", players[i]);  // Read max 10 chars
        flushBuffer();
    }
}

void playGame(Board board, char players[2][21]) {
    char field[2];
    for (int i = 0; i < 2; ++i) {
        printf("\n");
        printBoard(&board);
        printf("\nPlayer %s, enter field (2 chars): ", players[i]);
        scanf("%2s", field);
        flushBuffer();
    }
}

void flushBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}