#include <stdio.h>
#include <stdbool.h>
#include "main.h"

void printBoard(char board[3][3])
{
    for (int rowCount = 0; rowCount <3; rowCount++)
    {
        printf("[%c] [%c] [%c]\n", board[rowCount][0], board[rowCount][1], board[rowCount][2]);
    }
}

void getBoardInput(char board[3][3])
{
    for (int rowCount = 0; rowCount <3; rowCount++)
    {
        for (int colCount = 0; colCount <3; colCount++)
        {
            char c = getchar();
            board[rowCount][colCount] = c;
        }
    }
}

int placeChar(int place, char c, char board[3][3])
{
    int count = 0;
    for (int rowCount = 0; rowCount <3; rowCount++)
    {
        for (int colCount = 0; colCount <3; colCount++)
        {
            if (count++ == place-1) {
                // Get the current value for this and see if its its empty, and if so place it, otherwise return false (invalid)
                if (c == 'X' || c == 'x' || c == 'O' || c == 'o') {
                    board[rowCount][colCount] = c;
                    //valid
                    return 1;
                }
                //invalid
                return 0;
            }
        }
    }
    //invalid
    return 0;
}

int isWinningMove(char board[3][3], int pos, char c)
{
	/*
	[0][0][0][x] => [max-max][max or 0]
	[0][0][x][0] => [max-2][max-1 or max-2]
	[0][x][0][0] => [max-2][max-2 or max-1]
	[x][0][0][0] => [max][max-max or max]
	*/
	for(int rowCount =0; rowCount < 3;rowCount++)
	{		

		for(int colCount =0; colCount < 3;colCount++)
		{
			
		}
	}

}

int main(int argc, char** argv)
{
    int board[][3] = {
        {' ',' ',' '},
        {' ',' ',' '},
        {' ',' ',' '},
    };

    // Setup the board
    puts("setup your board:");
    getBoardInput(board);
    printBoard(board);
	// only nine moves possible
	int moves = 0;
	int isValid;
	int isWinningMove = 0;
	do
	{
		printf("move #%d\n", moves);
		int pos;
		char c;
		// ask the user for input
		puts("set pos and char");
		scanf_s("%d%c", &pos, &c);

		isValid = placeChar(pos, c, board);
		
				
		printBoard(board);
		if(isValid){
			moves++;
			isWinningMove = CheckForWin(board, pos, c);
		}
		else
		{
			puts("Invalid move, try again.");
		}
	}while(moves <9 || isWinningMove);
	

    return 0;
}