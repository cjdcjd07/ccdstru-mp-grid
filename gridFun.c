#include "gridHead.h"

void InitSystem(GameState *state)
{
    memset(state, 0, sizeof(GameState));
    state->good = 0;
    state->go = 1;
    state->start = 1;
    state->found = 1;
    state->val = 0;
    state->over = 0;
}

void UpdateFacts(GameState *state)
{
    int r_count = Count(state->R);
    int b_count = Count(state->B);
    int f_count = 9 - (r_count + b_count);

    if (f_count == 0 || state->val >= 20 || (!state->start && 
       ((r_count > 0 && b_count == 0) || (r_count == 0 && b_count > 0))))
    {
        state->over = 1;
    }
    else
    {
        state->over = 0;
    }
}

int IsValid(int a, int b)
{
    int valid = 0;

    if (a >= 1 && a <= 3 && b >= 1 && b <= 3)
    {
        valid = 1;
    }

    return valid;
}

int Count(int set[4][4])
{
    int c = 0;
    int i, j;

    for (i = 1; i <= 3; i++)
    {
        for (j = 1; j <= 3; j++)
        {
            if (set[i][j])
            {
                c++;
            }
        }
    }

    return c;
}

void RemovePiece(GameState *state, int a, int b)
{

}

void Replace(GameState *state, int a, int b)
{

}

void Expand(GameState *state, int a, int b)
{

}
void Update(GameState *state, int a, int b)
{

}

void NextPlayerMove(GameState *, int a, int b)
{

}

void GameOver(GameState *state)
{

}
