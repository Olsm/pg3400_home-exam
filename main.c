#include "board.h"
#include "game.h"

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