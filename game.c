#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "board.h"
#include "game.h"

void createPlayers(char players[2][21]) {
    for (int i = 0; i < 2; ++i) {
        printf("Enter name player %d (max 20 chars): ", i+1);
        scanf("%20s", players[i]);  // Read max 10 chars
        flushBuffer();
    }
}

void playGame(Board *board, char players[2][21], FILE *file) {
    int gameOver = 0;
    int fieldX, fieldY;
    int legalMoves[8][2];
    Field playerFields[2] = {WHITE, BLACK};

    while (!gameOver) {
        for (int i = 0; i < 2; ++i) {
            if (!isGameOver(board, playerFields[i])) {
                printf("\n\n");
                printBoard(board);

                // Get next move input from user and make the move
                getNextMove(board, legalMoves, &fieldX, &fieldY, players[i], playerFields[i]);
                makeMove(board, legalMoves, playerFields[i], fieldX, fieldY);
                flushBuffer();

                // Save the move to file
                fprintf(file, "%s moved to %c%d\n", players[i], fieldX+'a', fieldY+1);
                fflush(file);
            }

            // Check if game is over
            gameOver = isGameOver(board, playerFields[0]) && isGameOver(board, playerFields[1]);
        }
    }

    endGame(board, players);

    printf("\n\nPress a key to exit\n");
    getchar();
    exit(0);
}

int getNextMove(Board *board, int legalMoves[8][2], int *fieldX, int *fieldY, char player[], Field playerF) {
    int legalMove = 0;
    while (!legalMove) {
        getFieldInput(fieldX, fieldY, player);
        legalMove = isMoveLegal(board, legalMoves, playerF, *fieldX, *fieldY);
        if (!legalMove)
            printf("Invalid move!");
    }
    return legalMove;
}

void makeMove(Board *board, int legalMoves[8][2], enum Field playerF, int fieldX, int fieldY) {
    int xDelta = 0, yDelta = 0, x, y;

    // swap fields in all legal move directions
    int i = 0;
    while (legalMoves[i][0] != 0 || legalMoves[i][1] != 0) {
        x = fieldX, y = fieldY;
        xDelta = legalMoves[i][0], yDelta = legalMoves[i][1];

        // Add field and swap opponent fields
        do { board->fields[x][y] = playerF;
        } while ((x += xDelta) > 0 && x < BOARD_SIZE &&
                 (y += yDelta) > 0 && y < BOARD_SIZE &&
                 board->fields[x][y] != playerF);
        i++;
    }
}

void getFieldInput(int *fieldX, int *fieldY, char player[]) {
    char fieldXIn;

    // Get a char and an int for field input (row and column)
    printf("\nPlayer %s, enter field: ", player);
    while (scanf(" %1c %1i", &fieldXIn, fieldY) != 2 ||
           tolower(fieldXIn) < 'a' || tolower(fieldXIn) > 'h' ||
           *fieldY < 1 || *fieldY > 8) {
        printf("Incorrect input. Letter (a-h) and number (1-8) (ex: b3): ");
        flushBuffer();
    }

    // Make fieldX and fieldY match board array bounds
    *fieldX = tolower(fieldXIn) - 'a';
    *fieldY = *fieldY - 1;
}

int isMoveLegalByDelta(Board *board, Field playerF, int fieldX, int fieldY, int deltaX, int deltaY) {
    // Previous field must be of opponent
    if (playerF == WHITE &&
            board->fields[fieldX+deltaX][fieldY+deltaY] != BLACK)
        return 0;
    if (playerF == BLACK &&
            board->fields[fieldX+deltaX][fieldY+deltaY] != WHITE)
        return 0;

    // Field + delta must be more than 0 and less than board size
    if (!(fieldX+deltaX >= 0 && fieldX+deltaX <= BOARD_SIZE) ||
            !(fieldY+deltaY >= 0 && fieldY+deltaY <= BOARD_SIZE))
        return 0;

    // Check if any of the next fields is the player field
    for (int i = fieldX + deltaX, j = fieldY + deltaY;
            i >= 0 && i <= BOARD_SIZE && j >= 0 && j <= BOARD_SIZE;
            i = i + deltaX, j = j + deltaY) {

        // If empty comes before a playerfield move is illegal
        if (board->fields[i][j] == EMPTY)
            return 0;

        // Legal move
        if (board->fields[i][j] == playerF)
            return 1;
    }

    // Move was not legal
    return 0;
}

void addLegalMove(int legalMoves[8][2], int *index, int x, int y) {
    legalMoves[*index][0] = x;
    legalMoves[*index][1] = y;
    *index += 1;
}

int isMoveLegal(Board *board, int legalMoves[8][2], Field playerF, int fieldX, int fieldY) {
    int index = 0;
    for (int i = 0; i < 8; ++i) {
        legalMoves[i][0] = 0;
        legalMoves[i][1] = 0;
    }

    // Moving to already taken spot is illegal
    if (board->fields[fieldX][fieldY] != EMPTY)
        return 0;

    // Check if move is legal in any direction
    if (isMoveLegalByDelta(board, playerF, fieldX, fieldY, -1, 0))
        addLegalMove(legalMoves, &index, -1, 0);
    if (isMoveLegalByDelta(board, playerF, fieldX, fieldY, 1, 0))
        addLegalMove(legalMoves, &index, 1, 0);
    if (isMoveLegalByDelta(board, playerF, fieldX, fieldY, 0, -1))
        addLegalMove(legalMoves, &index, 0, -1);
    if (isMoveLegalByDelta(board, playerF, fieldX, fieldY, 0, 1))
        addLegalMove(legalMoves, &index, 0, 1);
    if (isMoveLegalByDelta(board, playerF, fieldX, fieldY, -1, -1))
        addLegalMove(legalMoves, &index, -1, -1);
    if (isMoveLegalByDelta(board, playerF, fieldX, fieldY, 1, -1))
        addLegalMove(legalMoves, &index, 1, -1);
    if (isMoveLegalByDelta(board, playerF, fieldX, fieldY, -1, 1))
        addLegalMove(legalMoves, &index, -1, 1);
    if (isMoveLegalByDelta(board, playerF, fieldX, fieldY, 1, 1))
        addLegalMove(legalMoves, &index, 1, 1);

    // If index is > 0 there are legal moves
    // If index is 0 there are no legal moves
    return index;
}

int isGameOver(Board *board, Field playerF) {
    int legalMoves[8][2];
    // Check if there is any legal moves for the player
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (isMoveLegal(board, legalMoves, playerF, i, j))
                return 0;
        }
    }

    // There was no legal moves left so game is over
    return 1;
}

void endGame(Board *board, char players[2][21]) {
    printf("\n");
    printBoard(board);
    int white = 0, black = 0;

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board->fields[i][j] == WHITE)
                white++;
            else if (board->fields[i][j] == BLACK)
                black++;
        }
    }

    if (white > black)
        printf("\nPlayer %s won the game", players[0]);
    else if (black > white)
        printf("\nPlayer %s won the game", players[1]);
    else
        printf("\nThere is no winner, game tie");
}

void flushBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}