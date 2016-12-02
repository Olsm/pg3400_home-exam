#ifndef __GAME_H__
#define __GAME_H__
#endif //__GAME_H__

void flushBuffer();
void createPlayers(char players[2][21]);
void playGame(Board *board, char players[2][21], FILE *file);
void getFieldInput(int *fieldX, int *fieldY, char player[]);
int isMoveLegal(Board *board, Field playerF, int fieldX, int posY);
int getNextMove(Board *board, int *fieldX, int *fieldY, char player[], Field playerF);
void makeMove(Board *pBoard, enum Field field, int x, int y, int moveDir);
int isGameOver(Board *board, Field playerF);
void endGame(Board *board, char players[2][21]);