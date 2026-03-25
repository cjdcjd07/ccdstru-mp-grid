#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <string.h>

typedef struct 
{
    int R[4][4];
    int B[4][4];
    int S[4][4];
    int T[4][4];

    int good;
    int go;
    int over;
    int found;
    int start;
    int val;
} GameState;

// Function prototypes

void InitSystem(GameState* state);
void UpdateFacts(GameState* state);
int IsValid(int a, int b);
int Count(int set[4][4]);

void RemovePiece(GameState* state, int a, int b);
void Replace(GameState* state, int a, int b);
void Expand(GameState* state, int a, int b);
void Update(GameState* state, int a, int b);
void NextPlayerMove(GameState* state, int a, int b);
void GameOver(GameState* state);

#endif