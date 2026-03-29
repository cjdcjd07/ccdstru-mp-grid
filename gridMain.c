/**
* Description : This is the main() file of a modified chain-
* reaction game made for our CCDSTRU course in Term 2. 
* The game consists of a 3x3 board with players R and B. 
* Author/s : PIELAGO, JAMES & DIZON, CARL JOHN
* Section : S11 (New Section)
* Last Modified : March 30, 2026
*/

#include "gridFun.c"

int main ()
{
    GameStatus game;
    int usrR = 0; // Stores user's input for row 
    int usrC = 0; // Stores user's input for column
 
    InitSystem(&game);

    printf("+--------------------------------------------------+\n");
    printf("|            GRIDLOCK: CHAIN REACTION              |\n");
    printf("+--------------------------------------------------+\n");
    
    while (!game.over)
    {
        DisplayBoard(&game);

        if (game.go)
        {
            printf("[%sR%s] Enter position (row, column): ", REDBG, RST);
        }
        else
        {
            printf("[%sB%s] Enter position (row, column): ", BLUBG, RST);
        }

        scanf("%d %d", &usrR, &usrC);
        usrR--;
        usrC--;

        /* Validates if input is correct, proceeds if it is.  */
        if (usrR >= 0 && usrR <= 2 && usrC >= 0 && usrC <= 2)
        {
            NextPlayerMove(&game, usrR, usrC);
        }
        else
        {
            printf("%sInvalid input (only 1-3)%s. Try again.\n", RED, RST);
        }
    }

    if (game.over)
    {
        printf("\n--- GAME OVER ---\n");
        DisplayBoard(&game);
        GameOver(&game);
    }

    return 0;
}

/**
* This is to certify that this project is our own work, based on our personal
* efforts in studying and applying the concepts learned. We have constructed the
* functions and their respective algorithms and corresponding code by ourselves.
* The program was run, tested, and debugged by our own efforts. We further certify
* that we have not copied in part or whole or otherwise plagiarized the work of
* other students and/or persons.
*
* PIELAGO, JAMES (DLSU ID# 12524301)
* DIZON, CARL JOHN (DLSU ID# 12504130)
*/