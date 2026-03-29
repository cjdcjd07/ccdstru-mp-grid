/**
 * Description : This is the function file of a modified 
 * chain-reaction game made for our CCDSTRU course in 
 * Term 2. The game consists of a 3x3 board with players R and B. 
 * Author/s: PIELAGO, JAMES & DIZON, CARL JOHN
 * Section : S11 (New Section)
 * Last Modified : March 30, 2026
*/

#include "gridHead.h"

/**
 * Initializes the game after launch, by setting the default
 * values and clearing the sets. 
 * @param game - pointer to game's variables and sets.
 * @return None
 * @pre game must be a valid pointer. 
*/
void InitSystem(GameStatus *game)
{
    int i, j;

    game->good = 0;
    game->go = 1;
    game->start = 1;
    game->found = 0;
    game->val = 0;
    game->over = 0;

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            game->R[i][j] = 0;
            game->B[i][j] = 0;
            game->S[i][j] = 0;
            game->T[i][j] = 0;
        }
    }
}

/**
 * Counts the number of true (1) or occupied nodes in a set,
 * i.e., their size. 
 * @param set - set to be counted on.
 * @return integer of the number of occupied nodes. 
 * @pre The set must be initialized. 
*/
int Count(int set[3][3])
{
    int c = 0;
    int i, j;

    for (i = 0; i <= 2; i++)
    {
        for (j = 0; j <= 2; j++)
        {
            if (set[i][j])
            {
                c++;
            }
        }
    }

    return c;
}

/**
 * Clears node (a,b) from the R or B sets by setting it to false
 * depending on whose turn it is, then clears it both in the 
 * S and T sets too.  
 * @param game - struct pointer to game's variables and sets.
 * @param a - row position
 * @param b - column position
 * @return None
 * @pre a and b must be within (0-2) 
*/
void Remove(GameStatus *game, int a, int b)
{
    if(game->go)
    {
        game->R[a][b] = 0; 
    }
    else
    {
        game->B[a][b] = 0;
    }

    game->S[a][b] = 0;
    game->T[a][b] = 0;
}

/**
 * Replaces the position with the current player and marks the
 * S or T set. It calls expand if a node is already occupied, 
 * is taking the second hit, and hasn't exploded before.  
 * @param game - struct pointer to game's variables and sets.
 * @param a - row position
 * @param b - column position
 * @return None
 * @pre a and b must be within (0-2) 
*/
void Replace(GameStatus *game, int a, int b)
{
    game->found = 0;

    /* R's Turn */
    if (game->go)
    {
        if(game->B[a][b])
        {
            game->B[a][b] = 0; 
            game->found = 1; 
        }
        else if(game->R[a][b])
        {
            game->found = 1; 
        }
        else 
        {
            game->R[a][b] = 1;
        }
    } 

    /* B's Turn */
    else
    {
        if(game->R[a][b])
        {
            game->R[a][b] = 0; 
            game->found = 1; 
        }
        else if(game->B[a][b])
        {
            game->found = 1; 
        }
        else 
        {
            game->B[a][b] = 1;
        }
    }

    /* Updates S and T. Expands if condition is met. */
    if (game->found)
    {
        if (!game->S[a][b])
        {
            game->S[a][b] = 1; 
            game->found = 0; 
        }
        else if (game->S[a][b] && !game->T[a][b])
        {
            game->T[a][b] = 1;
            Expand(game, a, b);
        }
            
    }
}

/**
 * Expands/Explodes from the current node to its surroundings
 * depending on the player (R or B), and removes itself from the 
 * expanded node.  
 * @param game - struct pointer to game's variables and sets.
 * @param a - row position
 * @param b - column position
 * @return None
 * @pre a and b must be within (0-2) 
*/
void Expand(GameStatus *game, int a, int b)
{
    Remove(game, a, b);

    if (game->go && a > 0)
    {
        Replace(game, a-1, b); // u = (a-1, b)
    }

    else if (!game->go && a < 2)
    {
        Replace(game, a+1, b); // d = (a+1, b)
    }
    
    if (b > 0)
    {
        Replace(game, a, b-1); // k = (a, b-1)
    }

    if (b < 2)
    {
        Replace(game, a, b+1); // r = (a, b+1)
    }
}

/**
 * Updates a position of the player's move and calls expand
 * if it's already in S but not in T yet. 
 * @param game - struct pointer to game's variables and sets.
 * @param a - row position
 * @param b - column position
 * @return None
 * @pre a and b must be within (0-2)
*/
void Update(GameStatus *game, int a, int b)
{
    game->good = 0;

    if (!game->S[a][b])
    {
        game->S[a][b] = 1; 
        game->good = !game->good; 
    }

    if (!game->good && game->S[a][b] && !game->T[a][b])
    {
        game->T[a][b] = 1; 
        Expand(game, a, b);
    }
}

/**
 * Checks if the game is over or not yet. 
 * @param game - struct pointer to game's variables and sets.
 * @return n, where: 
 *  0 - Game is not over
 *  Over: 
 *  1 - One has no more nodes 
 *  2 - 3 Nodes left 
 *  3 - 21 moves have been made 
 * @pre game must be a valid pointer. 
*/
int isOver(GameStatus *game)
{
    int n; // Bool integer to be returned
    int sizeR = Count(game->R);
    int sizeB = Count(game->B);
    int isFull = (9 - (sizeR + sizeB) == 3);
    int isEliminated = (!game->start && ((sizeR > 0 && sizeB == 0) || 
                       (sizeR == 0 && sizeB > 0))); // isEliminated

    if (isEliminated)
    {
        n = 1; // Game over by eliminated...
    }
    else if (isFull)
    {
        n = 2; // Game over by 3-nodes-remaining rule...
    }
    else if (game->val >= 20)
    {
        n = 3; // Game over by max turns...
    }
    else 
    {
        n = 0; // Game is ON!
    }

    return n;
}

/**
 * Handles a player's moves and the checks if it's the starting turns 
 * or not (normal mode), which it updates. It also changes the turns 
 * and updates the turn counter. Then, calls isOver() to check if the 
 * game is over at the end.  
 * @param game - struct pointer to game's variables and sets.
 * @param a - row position
 * @param b - column position
 * @return None
 * @pre a and b must be within (0-2)
*/
void NextPlayerMove(GameStatus *game, int a, int b)
{
    int sizeR; 
    int sizeB; 
    
    /* Start Only Mode */
    if (!game->over && game->start)
    {   
        if ((game->go && game->B[a][b]) || (!game->go && game->R[a][b]))
        {
            printf("ERROR: Position already occupied.\n");
        }
        else
        {
            if (game->go)
            {
                game->R[a][b] = 1; 
            }
            else 
            {
                game->B[a][b] = 1; 
            }

            game->S[a][b] = 1; 
            game->good = 1; 
        }
        
    }
    /* !Start or Normal Mode*/
    else if (!game->over && !game->start )
    {
        if ((game->go && game->R[a][b]) || (!game->go && game->B[a][b]))
        {
            Update(game, a, b); 
            game->good = 1; 
        }

        else
        {
            printf("ERROR: You can only select your own nodes!\n");
        }
    }

    sizeR = Count(game->R);
    sizeB = Count(game->B);

    if (game->start && sizeR == 1 && sizeB == 1)
    {
        game->start = 0; 
    }

    if (!game->over && game->good)
    {
        game->good = 0;
        game->go = !game->go; 
        game->val++; 
    }

    game->over = isOver(game);
}

/**
 * If the game is over, this function prints the final message and 
 * determines who the winner is or if it's a draw by the amount of 
 * nodes occupied by R vs B. 
 * @param game - struct pointer to game's variables and sets.
 * @return None
 * @pre game must be a valid struct pointer. 
*/
void GameOver(GameStatus *game)
{
    int sizeR = Count(game->R); 
    int sizeB = Count(game->B);; 
    char result[3][7] = {"R Wins", "B Wins", "Draw"};

    switch (game->over)
    {
        case 1: 
            printf("Eliminated, GG! ");
            break;
        case 2: 
            printf("Only 3 spaces left, GG! ");
            break;
        case 3: 
            printf("Max turns reached, GG! ");
            break;
        default: // General statement for possible future modifications 
            printf("Over, GG! ");
    }

    if(sizeR > sizeB)
    {
        printf("%s%s%s\n", RED, result[0], RST);
    }
    else if (sizeR < sizeB)
    {
        printf("%s%s%s\n", BLU, result[1], RST); 
    }
    else if (sizeR == sizeB)
    {
        printf("%s%s%s\n", YLW, result[2], RST);
    }
}

/**
 * Prints the board display from the start until the end, it 
 * displays the moves remaining and the nodes occupied by 
 * players R and B. 
 * @param game - struct pointer to game's variables and sets.
 * @return None
 * @pre game must be a valid struct pointer. 
*/
void DisplayBoard(GameStatus *game)
{
    int i, j; 

    // Note that the current turn is INCLUDED in the remaining turns
    printf("\nTurn #%d (%d Left)\n", game->val, 21-game->val); 

    printf("    1 2 3\n");
    printf("  +-------\n");
       
    for (i = 1; i <= 3; i++)
    {
        printf("%d |", i);
        for(j = 1; j <= 3; j++)
        {
            if (game->R[i-1][j-1])
            {
                printf(" %sR%s", RED, RST);
            }
            else if (game->B[i - 1][j - 1])
            {
                printf(" %sB%s", BLU, RST);
            }
            else
            {
                printf(" X");
            }
        }

        printf("\n");
    }
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