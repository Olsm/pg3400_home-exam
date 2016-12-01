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

void playGame(Board *board, char players[2][21]) {
    int fieldX, fieldY, moveDir;
    Field playerFields[2] = {WHITE, BLACK};

    for (int i = 0; i < 2; ++i) {
        printf("\n");
        printBoard(board);

        // Get valid field input from user
        moveDir = getNextMove(board, &fieldX, &fieldY, players[i], playerFields[i]);
        makeMove(board, playerFields[i], fieldX, fieldY, moveDir);
        flushBuffer();
    }
}

int getNextMove(Board *board, int *fieldX, int *fieldY, char player[], Field playerF) {
    int legalMove = 0;
    while (!legalMove) {
        getFieldInput(fieldX, fieldY, player);
        legalMove = isMoveLegal(board, playerF, *fieldX, *fieldY);
        if (!legalMove)
            printf("Invalid move!");
    }
    return legalMove;
}

void makeMove(Board *board, enum Field playerF, int x, int y, int moveDir) {
    int xDelta = 0, yDelta = 0;

    // Chose which way to swap fields
    switch (moveDir) {
        case 1: // row left
            xDelta = -1;
            break;
        case 2: // row right
            xDelta = 1;
            break;
        case 3: // col down
            yDelta = -1;
            break;
        case 4: // col up
            yDelta = 1;
            break;
        case 5: // diag left up
            xDelta = -1;
            yDelta = -1;
            break;
        case 6: // diag right up
            xDelta = 1;
            yDelta = -1;
            break;
        case 7: // diag left down
            xDelta = -1;
            yDelta = 1;
            break;
        case 8: // diag right down
            xDelta = 1;
            yDelta = 1;
            break;
        default:
            exit(-1);
    }

    // Add field and swap opponent fields
    do { board->fields[x][y] = playerF;
    } while (board->fields[x += xDelta][y += yDelta] != playerF);
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

// TODO: This should be one check repeated 8 times
int isMoveLegal(Board *board, Field playerF, int fieldX, int fieldY) {
    Field otherPlayerF;
    if (playerF == BLACK)
        otherPlayerF = WHITE;
    else
        otherPlayerF = BLACK;

    // Moving to already taken spot is illegal
    if (board->fields[fieldX][fieldY] != EMPTY)
        return 0;

    // Check if valid in row to left
    if (fieldX-1 > 0 && board->fields[fieldX-1][fieldY] == otherPlayerF) {
        for (int i = fieldX-1; i >= 0; i--) {
            if (board->fields[i][fieldY] == playerF)
                return 1;
        }
    }

    // Check if valid in row to right
    if (fieldX+1 < BOARD_SIZE && board->fields[fieldX+1][fieldY] == otherPlayerF) {
        for (int i = fieldX+1; i < BOARD_SIZE; i++) {
            if (board->fields[i][fieldY] == playerF)
                return 2;
        }
    }

    // Check if valid in column down
    if (fieldY-1 > 0 && board->fields[fieldX][fieldY-1] == otherPlayerF) {
        for (int i = fieldY-1; i >= 0; i--) {
            if (board->fields[fieldX][i] == playerF)
                return 3;
        }
    }

    // Check if valid in column up
    if (fieldY-1 < BOARD_SIZE && board->fields[fieldX][fieldY+1] == otherPlayerF) {
        for (int i = fieldY+1; i < BOARD_SIZE; i++) {
            if (board->fields[fieldX][i] == playerF)
                return 4;
        }
    }

    // Check if valid in diagonal up left
    if (fieldX-1 > 0 && fieldY-1 > 0 && board->fields[fieldX-1][fieldY-1] == otherPlayerF) {
        for (int i = 1; i < fieldX-i > 0 && fieldY-i > 0; i++) {
            if (board->fields[fieldX - i][fieldY - i] == playerF)
                return 5;
        }
    }

    // Check if valid in diagonal up right
    if (fieldX+1 < BOARD_SIZE && fieldY+1 > 0 && board->fields[fieldX+1][fieldY-1] == otherPlayerF) {
        for (int i = 1; i < fieldX+i < BOARD_SIZE && fieldY+i > 0; i++) {
            if (board->fields[fieldX + i][fieldY - i] == playerF)
                return 6;
        }
    }

    // Check if valid in diagonal down left
    if (fieldX-1 > 0 && fieldY+1 < BOARD_SIZE && board->fields[fieldX-1][fieldY+1] == otherPlayerF) {
        for (int i = 1; fieldX-i > 0 && fieldY+i < BOARD_SIZE; i++) {
            if (board->fields[fieldX - i][fieldY + i] == playerF)
                return 7;
        }
    }

    // Check if valid in diagonal down right
    if (fieldX+1 < BOARD_SIZE && fieldY+1 > 0 && board->fields[fieldX+1][fieldY+1] == otherPlayerF) {
        for (int i = 1; fieldX+i < BOARD_SIZE && fieldY+i > 0; i++) {
            if (board->fields[fieldX + i][fieldY + i] == playerF)
                return 8;
        }
    }

    // Moving here is illegal
    return 0;
}


void flushBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}