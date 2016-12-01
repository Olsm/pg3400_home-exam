#include <stdio.h>
#include <ctype.h>
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
    char fieldX;
    int fieldY;

    for (int i = 0; i < 2; ++i) {
        printf("\n");
        printBoard(&board);

        // Get field input from user
        getFieldInput(&fieldX, &fieldY, players[i]);
        flushBuffer();
    }
}

void getFieldInput(char *fieldX, int *fieldY, char player[]) {
    printf("\nPlayer %s, enter field (1 char & 1 int): ", player);
    while (scanf(" %1c %1i", fieldX, fieldY) != 2 ||
           tolower(*fieldX) < 'a' || tolower(*fieldX) > 'h' ||
           *fieldY < 1 || *fieldY > 8) {
        printf("Incorrect input. Letter (a-h) and number (1-8) (ex: b3): ");
        flushBuffer();
    }
}

void flushBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}