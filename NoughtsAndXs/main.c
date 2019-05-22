#include <stdio.h>
#include <stdbool.h>


// print the board
void printBoard(char board[3][3], int maxRows, int maxCols)
{
    for (int rowCount = 0; rowCount < maxRows; rowCount++)
    {
        printf("[%c] [%c] [%c]\n", board[rowCount][0], board[rowCount][1], board[rowCount][2]);
    }
}

// Fill in the board with desired configuration
void getBoardInput(char board[3][3], int maxRow, int maxCol)
{
    for (int rowCount = 0; rowCount < maxRow; rowCount++)
    {
        for (int colCount = 0; colCount < maxCol; colCount++)
        {
            char c = getchar();
            board[rowCount][colCount] = c;
        }
    }
}

// place move on the board
int tryPlaceMove(int place, char c, char board[3][3], int maxRows, int maxCols)
{
    int count = 0;
    for (int rowCount = 0; rowCount < maxRows; rowCount++)
    {
        for (int colCount = 0; colCount < maxCols; colCount++)
        {
			int realPlace = place - 1;
            if (count++ == realPlace) {
                // Get the current value for this and see if its its empty, and if so place it, otherwise return false (invalid)
                if (c == 'X' || c == 'x' || c == 'O' || c == 'o') {
                    board[rowCount][colCount] = c;
                    //valid character set
                    return 1;
                }
                //invalid character
                return 0;
            }
        }
    }
    //invalid
    return 0;
}

int isLineWin(char board[3][3], int doVline)
{
	int lineWin = 0;
	for (int i = 0; i < 3; i++)
	{
		if (lineWin)
			break;
		char lastVal = doVline ? board[0][i] : board[i][0];
		for (int j = 0; j < 3; j++)
		{
			char current = doVline ? board[j][i] : board[i][j];
			if (lastVal == current)
			{
				lastVal = current;
				lineWin = 1;
			}
			else
			{
				lineWin = 0;
				break;
			}
		}
	}
	if (lineWin)
	{
		if(doVline) 
			puts("Vline win");
		else
			puts("hline win");
	}
	return lineWin;
}

int CheckForWin(char board[3][3], int maxRows, int maxCols, int pos, char c)
{
	
	/*
	Check \ diag
	 0  1  2
	 [x][][] 0
	 [][x][] 1
	 [][][x] 2	
	*/
	char diagChar = board[0][0];
	int isWinningDiag = 0;
	for (int i = 1; i < maxRows;)
	{
		char got = board[i][i++];
		if (got == diagChar)
		{
			diagChar == got;
			isWinningDiag = 1;
			continue;
		}
		isWinningDiag = 0;
		break;		
	}

	/*
	check / diag
	 0  1  2
	 [][][x] 0
	 [][x][] 1
	 [x][][] 2
	*/
	if (isWinningDiag)
	{
		puts("diag win \\");
		return isWinningDiag;

	}
	//otherwise check the other diagnoal
	isWinningDiag = 0;
	int indx = maxRows - 1;
	char last = board[0][indx];
	for (int i = 0; i < maxRows; i++)
	{
		char current = board[i][indx - i];
		if (last == current) {
			last = current;
			isWinningDiag = 1;
			continue;
		}
		isWinningDiag = 0;
		break;
	}
	if (isWinningDiag)
	{
		puts("diag win /");
	}
	
	return isWinningDiag || isLineWin(board,1) || isLineWin(board,0);
}

#define MAX_ROWS 3
#define MAX_COLS 3

int main(int argc, char** argv)
{
	// Start off with an empty board
    int board[][MAX_COLS] = {
        {' ',' ',' '},
        {' ',' ',' '},
        {' ',' ',' '},
    };

    // Setup the board
    puts("setup your board:");
    getBoardInput(board, MAX_ROWS, MAX_COLS);

	// Show how it starting board looks like
    printBoard(board, MAX_ROWS, MAX_COLS);

	// Ask players for moves
	int moves = 0;
	int isValid;
	int isWinningMove = 0;
	int player = 1;
	do
	{
		int pos;
		char c;

		// Ask the user for input
		printf("Player %d set your pos and char (eg 4X or 4O to add to positino 4): ", player);
		scanf_s("%d%c", &pos, &c);
		isValid = tryPlaceMove(pos, c, board, MAX_ROWS, MAX_COLS);		
				
		// Show board configuration after move placed
		printBoard(board, MAX_ROWS, MAX_COLS);
		
		// If the move was valid then loop again asking for next move
		if(isValid)
		{
			moves++;			
			isWinningMove = CheckForWin(board, MAX_ROWS, MAX_COLS, pos, c);			
		}
		else
		{
			puts("Invalid move, try again.");
		}
	}while(moves <9 && !isWinningMove);
	
	if (isWinningMove)
	{
		printf("player %d wins", player);
	}

    return 0;
}