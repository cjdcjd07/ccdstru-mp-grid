#include "gridHead.h"
#include "gridFun.c"

#include <stdio.h>

int main ()
{
    GameState game;
    int r = 0;
    int c = 0;
    int nGrid = 1; // Loop control flag

    InitSystem(&game);

    while (!game.over && nGrid)
    {

    }

    printf("\n--- GAME OVER ---\n");
    GameOver(&game);

    return 0;
}