/*  
Simple Number Puzzle like Game.
Author: Raghuvir Gondaliya.

Arrange the numbers in ascending order to win
COMMANDS : UP(i) DOWN(k) LEFT(j) RIGHT(k)
Quit : 'Q' capital only!
*/


#include<stdio.h>
#include<conio.h>


// declaration of custom functions
int servePuzzle(int *, int);
void displayPuzzle(int *);
int executeCmd(int *, char);
int findZero(int *, int *, int *);
void swapElements(int *x, int *y);
int checkPuzzle(int *);
int valueAt(int *, int, int);
int* addressAt(int *, int, int);


// global variables
char score = 0;
char level = 1;
int moves = -1;
char puzzleSize = 2;
char TOT_PUZZLES = 3;
char currentPuzzleIndex = 0;
int puzzle2x2[2][2] = {{1, 0} , {3, 2}};
int puzzle3x3[3][3] = {{5, 2, 3}, {4, 0, 1}, {8, 7, 6}};
int puzzle4x4[4][4] = {{1, 4, 3, 15}, {10, 7, 13, 8}, {9, 5, 11, 0}, {2, 14, 6, 12}};
int *puzzels[] = { &puzzle2x2[0][0],     // store base addresses
                   &puzzle3x3[0][0],
                   &puzzle4x4[0][0]
                 };



int main()
{
    char isSolved = 0;
    printf("\n\n####");
    printf("_________________________RAGHUVIR'S_____PUZZLES_________________________");
    printf("####\n\n");
    isSolved = servePuzzle(puzzels[currentPuzzleIndex], puzzleSize);
    if(isSolved)
    {
        score++;
        if(score > currentPuzzleIndex)
        {
            currentPuzzleIndex++;
            if(currentPuzzleIndex == TOT_PUZZLES)
            {
                printf("\n\tNo more puzzles to play...");
                return 0;
            }
            puzzleSize++;
            score = 0;
            level++;
        }
        main();
    }
    return 0;
}


// defination of custon functions
int servePuzzle(int *pzl, int size)
{
    char cmd = 'i', winStatus = 0, changes = 1;
    printf("  Arrange in ascending order by moving '0' up/down/left/right ...\n");
    printf("  UP = i  |  DOWN = k  |  LEFT = j  |  RIGHT = l\n\n");
    do
    {
        if(changes)
        {
            moves++;
            displayPuzzle(pzl);
            printf("\n  MOVES: %d\tSCORE: %d\tLEVEL: %d\n  Wanna Quit? - Press 'Q'.\n", moves, score, level);
            printf("  Enter your command(i/k/j/l): ");
        }
        do
        {
            cmd = getch();  // get valid cmd
        } while (cmd != 'i' && cmd != 'j' && cmd != 'k' && cmd != 'l' && cmd != 'Q');
        changes = executeCmd(pzl, cmd);
        winStatus = checkPuzzle(pzl);
        if(winStatus)
        {
            moves = -1;
            displayPuzzle(pzl);
            printf("\n\n\n\n\n\n\n\t0_0    -->    Congratulations    <--    0_0\n\n\t\tYou moved to the next step !\n\n\t\tscore %d to %d in level %d\n\n\n\n\n", score, score+1, level);
            // scramble the elements to make it difficult !
            swapElements(addressAt(pzl, score, score), addressAt(pzl, score, 1+score));
            swapElements(addressAt(pzl, score, score), addressAt(pzl, 1+score, score));
            return winStatus;
        }
    } while (cmd != 'Q');
    if(cmd == 'Q')
        getch();  
    return winStatus;
}


void displayPuzzle(int *p)
{
    printf("\n\t|--------------------------------------|\n");
    for(int i = 0; i < puzzleSize; i++)
    {
        printf("\t\t");
        for(int j = 0; j < puzzleSize; j++)
        {
            printf("%d\t", valueAt(p, i, j));
        }
        printf("\n\t|--------------------------------------|\n");
    }
    printf("\n\n");
}


int executeCmd(int *pzl, char ch)
{
    int i, j;
    char changes = 0;
    if(ch == 'i')
    {
        findZero(pzl, &i, &j);
        if(i > 0)
        {
            swapElements(addressAt(pzl, i, j), addressAt(pzl, i-1, j));
            changes = 1;
        }
        if(changes)
            printf("i (UP)\n\n\n");
    }
    else if(ch == 'j')
    {
        findZero(pzl, &i, &j);
        if(j > 0)
        {
            swapElements(addressAt(pzl, i, j), addressAt(pzl, i, j-1));
            changes = 1;
        }
        if(changes)
            printf("j (LEFT)\n\n\n");
    }
    else if(ch == 'k')
    {
        findZero(pzl, &i, &j);
        if(i < puzzleSize-1)
        {
            swapElements(addressAt(pzl, i, j), addressAt(pzl, i+1, j));
            changes = 1;
        }
        if(changes)
            printf("k (DOWN)\n\n\n");
    }
    else if(ch == 'l')
    {
        findZero(pzl, &i, &j);
        if(j < puzzleSize-1)
        {
            swapElements(addressAt(pzl, i, j), addressAt(pzl, i, j+1));
            changes = 1;
        }
        if(changes)
            printf("l (RIGHT)\n\n\n");
    }
    else if(ch == 'Q')
        printf("  Q: QUIT\n\n  Signing off ! You played well.\n  Hope to see you again :)\n\n");
    return changes;
}


int findZero(int *pzl, int *raw, int *clm)
{
    for(int i = 0; i < puzzleSize; i++)
    {
        for(int j = 0; j < puzzleSize; j++)
        {
            if(valueAt(pzl, i, j) == 0)
            {
                *raw = i;
                *clm = j;
                return 0;
            }
        }
    }
}


void swapElements(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}


int checkPuzzle(int *pzl)
{
    char prevValue = *pzl;
    pzl++;
    for(int i = 0; i < (puzzleSize*puzzleSize - 2); i++)
    {
        if(*pzl - prevValue != 1)
            return 0;
        prevValue = *pzl;
        pzl++;
    }
    return 1;
}


int valueAt(int *p, int i, int j)
{
    // returns the value at given i, j index
    int *addr = p + i*puzzleSize + j;
    int value = *addr; 
    return value;
}


int* addressAt(int *p, int i, int j)
{
    // returns the address at given index
    int *addr = p + i*puzzleSize + j;
    return addr;
}

