#ifndef __GAME_H__
#define __GAME_H__
#endif //__GAME_H__

void flushBuffer();
void createPlayers(char players[2][21]);
void playGame(Board *board, char players[2][21], FILE *file);
void getFieldInput(int *fieldX, int *fieldY, char player[]);
void addLegalMove(int legalMoves[8][2], int *index, int x, int y);
int isMoveLegalByDelta(Board *board, Field playerF, int fieldX, int fieldY, int deltaX, int deltaY);
int isMoveLegal(Board *board, int legalMoves[8][2], Field playerF, int fieldX, int posY);
int getNextMove(Board *board, int legalMoves[8][2], int *fieldX, int *fieldY, char player[], Field playerF);
void makeMove(Board *board, int legalMoves[8][2], enum Field field, int x, int y);
int isGameOver(Board *board, Field playerF);
void endGame(Board *board, char players[2][21]);