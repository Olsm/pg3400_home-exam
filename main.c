#include <stdio.h>
#include "board.h"

// TODO: Prevent string overflow
void createPlayers(char players[2][20]) {
    for (int i = 0; i < 2; ++i) {
        printf("Enter name player1: ");
        scanf("%s", players[i]);
    }
    printf("\n\n");
}

int main(void) {
    // Create players
    char players[2][20];
    createPlayers(players);

    // Create and print the board
    Board currentBoard;
    initBoard(&currentBoard);
    printBoard(&currentBoard);
}