#include "gridHead.h"

int main ()
{
    GameStatus game;
    int usrR = 0; // Stores user's input for row 
    int usrC = 0; // Stores user's input for column

    InitSystem(&game);

    printf("===============================\n");
    printf(" DSTRU GRID BY DIZON & PIELAGO \n");
    printf("===============================\n");
    
    while (!game.over)
    {
        DisplayBoard(&game);

        if (game.go)
            printf("[%sR%s] Enter position (row, column): \n", RED, RST);
        else
            printf("[%sB%s] Enter position (row, column): \n", BLU, RST);

        scanf("%d %d", &usrR, &usrC);
        usrR--;
        usrC--;

        /* Validates if input is correct, proceeds if it is.  */
        if (usrR >= 0 && usrR <= 2 && usrC >= 0 && usrC <= 2)
        {
            NextPlayerMove(&game, usrR, usrC);
        }
        else
            printf("%sInvalid input (only 1-3)%s. Try again.\n", RED, RST);
    }

    if (game.over)
    {
        printf("\n--- GAME OVER ---\n");
        DisplayBoard(&game);
        GameOver(&game);
    }

    return 0;
}