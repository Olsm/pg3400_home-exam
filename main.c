#include <stdio.h>
#include "board.h"

// TODO: Prevent string overflow
void createPlayers(char *player1, char *player2) {
    printf("Enter name player1: ");
    scanf("%s", player1);
    printf("Enter name player2: ");
    scanf("%s", player2);
    printf("\n\n");
}

int main(void) {
    // Create players
    char player1[20];
    char player2[20];
    createPlayers(player1, player2);

    // Create and print the board
    Board currentBoard;
    initBoard(&currentBoard);
    printBoard(&currentBoard);

    
}