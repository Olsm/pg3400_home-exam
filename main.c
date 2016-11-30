#include <stdio.h>

void createPlayers(char *player1, char *player2) {
    printf("Enter name player1: ");
    scanf("%s", player1);
    printf("Enter name player2: ");
    scanf("%s", player2);
}

int main(void) {
    char player1[20];
    char player2[20];
    createPlayers(player1, player2);
    printf("%s %s", player1, player2);
}