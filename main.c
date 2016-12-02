#include <stdio.h>
#include "board.h"
#include "game.h"

int main(void) {
    // Create file for logging moves
    FILE * file = fopen("moves.txt", "wt");
    if (!file) {
        perror("Could not open log files for moves");
        return -1;
    }

    // Create players
    char players[2][21];
    createPlayers(players);

    // Create the board
    Board currentBoard;
    initBoard(&currentBoard);

    // Start the game
    playGame(&currentBoard, players, file);

    fclose(file);
}