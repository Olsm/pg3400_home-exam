#ifndef __GAME_H__
#define __GAME_H__
#endif //__GAME_H__

void flushBuffer();
void createPlayers(char players[2][21]);
void playGame(Board *board, char players[2][21]);
void getFieldInput(int *fieldX, int *fieldY, char player[]);
int isMoveLegal(Board *board, Field playerF, int fieldX, int posY);
void getNextMove(Board *board, int *fieldX, int *fieldY, char player[], Field playerF);