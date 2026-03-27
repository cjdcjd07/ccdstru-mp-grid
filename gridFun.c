#include "gridHead.h"

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

void Remove(GameStatus *game, int a, int b)
{
    if(game->go)
        game->R[a][b] = 0; 
    else
        game->B[a][b] = 0;

    game->S[a][b] = 0;
    game->T[a][b] = 0;
}

void Replace(GameStatus *game, int a, int b)
{
    game->found = 0;

    /* Red */
    if (game->go)
    {
        if(game->B[a][b])
            {
                game->B[a][b] = 0; 
                game->found = 1; 
            }
        else if(game->R[a][b])
            game->found = 1; 
        else 
            game->R[a][b] = 1;
    } 

    /* Blue */
    else
    {
        if(game->R[a][b])
            {
                game->R[a][b] = 0; 
                game->found = 1; 
            }
        else if(game->B[a][b])
            game->found = 1; 
        else 
            game->B[a][b] = 1;
    }

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
            game->found = 0;
            Expand(game, a, b);
        }
            
    }
}


void Expand(GameStatus *game, int a, int b)
{
    Remove(game, a, b);

    if (game->go && a > 0)
        Replace(game, a-1, b); // u = (a-1, b)
    else if (!game->go && a < 2)
        Replace(game, a+1, b); // d = (a+1, b)
    
    if (b > 0)
        Replace(game, a, b-1); // k = (a, b-1)
    if (b < 2)
        Replace(game, a, b+1); // r = (a, b+1)
}

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


int isOver(GameStatus *game)
{
    int n; // Bool to be returned
    int sizeR = Count(game->R);
    int sizeB = Count(game->B);
    int isFull = (9 - (sizeR + sizeB) == 3);
    int elimination = (!game->start && ((sizeR > 0 && sizeB == 0) || (sizeR == 0 && sizeB > 0)));

    if (isFull || game->val >= 20 || elimination)
        n = 1; // Game over...
    else    
        n = 0; // Game is ON

    return n;
}


void NextPlayerMove(GameStatus *game, int a, int b)
{
    int sizeR; 
    int sizeB; 
    
    /* Start Only */
    if (!game->over && game->start)
    {   
        if (game->go)  
            game->R[a][b] = 1; 
        else 
            game->B[a][b] = 1; 
        game->S[a][b] = 1; 
        game->good = 1; 
    }
    /* Normal */
    else if (!game->over && !game->start )
    {
        if ((game->go && game->R[a][b]) || (!game->go && game->B[a][b]))
        {
            Update(game, a, b); 
            game->good = 1; 
        }
    }

    sizeR = Count(game->R);
    sizeB = Count(game->B);

    if (game->start && sizeR == 1 && sizeB == 1)
        game->start = 0; 

    if (!game->over && game->good)
    {
        game->good = 0;
        game->go = !game->go; 
        game->val++; 
    }

    game->over = isOver(game);
}


void GameOver(GameStatus *game)
{
    int sizeR = Count(game->R); 
    int sizeB = Count(game->B);; 
    char result[3][7] = {"R Wins", "B Wins", "Draw"}; 
    game->over = 1; 

    if(sizeR > sizeB)
        printf("%s%s%s\n", RED, result[0], RST);
    else if (sizeR < sizeB)
        printf("%s%s%s\n", BLU, result[1], RST); 
    else if (sizeR == sizeB)
        printf("%s%s%s\n", YLW, result[2], RST);
}


void DisplayBoard(GameStatus *game)
{
    int i, j; 

    printf("\n    1  2  3\n");
    printf("  +--------\n");
       
    for (i = 1; i <= 3; i++)
    {
        printf("%d |", i);
        for(j = 1; j <= 3; j++)
        {
            if (game->R[i-1][j-1])
                printf(" %sR%s", RED, RST);
            else if (game->B[i-1][j-1])
                printf(" %sB%s", BLU, RST);
            else
                printf(" X");
        }
        printf("\n");
    }
}