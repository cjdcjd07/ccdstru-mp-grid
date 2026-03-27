#include <stdio.h>

#define RED "\x1b[31m"
#define BLU "\x1b[34m"
#define YLW "\x1b[33m"
#define RST "\x1b[0m"

typedef struct 
{
    int R[3][3];
    int B[3][3];
    int S[3][3];
    int T[3][3];

    int good;
    int go;
    int over;
    int found;
    int start;
    int val;
} GameStatus;

// Function prototypes

void InitSystem(GameStatus* game);
int Count(int set[3][3]);

void Remove(GameStatus* game, int a, int b);
void Replace(GameStatus* game, int a, int b);
void Expand(GameStatus* game, int a, int b);
void Update(GameStatus* game, int a, int b);
int isOver(GameStatus *game);
void NextPlayerMove(GameStatus* game, int a, int b);
void GameOver(GameStatus* game);
void DisplayBoard(GameStatus *game);
