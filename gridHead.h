/**
* Description : This is the header file of a modified chain-
*   reaction game made for our CCSDTRU course in term 2. 
*   The game consists of a 3x3 board with players R and 
*   B. 
* Author/s : PIELAGO, JAMES & DIZON, CARL JOHN
* Section : S11 (New Section)
* Last Modified : March 28, 2026
*/

#include <stdio.h>

/* Text Color Macros */
#define REDBG "\x1b[41m"
#define BLUBG "\x1b[44m"
#define RED "\x1b[31m"
#define BLU "\x1b[34m"
#define YLW "\x1b[33m"
#define GRN "\x1b[32m"
#define RST "\x1b[0m"

/**
 * Contain's the game's variables and sets, except result.
*/
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
    int val; // Move counter
} GameStatus;

/* Function prototypes */
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