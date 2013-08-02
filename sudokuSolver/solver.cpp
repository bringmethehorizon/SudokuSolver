#include "solver.h"
bool isOk(int num, int x, int y)
{
	int startX,endX,startY,endY;
	if(x<3)
	{
		startX=0;
		endX=3;
	}
	else if(x<6)
	{
		startX=3;
		endX=6;
	}
	else if(x<9)
	{
		startX=6;
		endX=9;
	}

	if(y<3)
	{
		startY=0;
		endY=3;
	}
	else if(y<6)
	{
		startY=3;
		endY=6;
	}
	else if(y<9)
	{
		startY=6;
		endY=9;
	}

	for(int i=0; i<9; i++)
		if(matrix[x][i]==num) return false;
	for(int i=0; i<9; i++)
		if(matrix[i][y]==num) return false;
	for(int i=startX; i<endX; i++)
	{
		for(int j=startY; j<endY; j++)
		{
			if(matrix[i][j]==num) return false;
		}
	}

	return true;
}

void init()
{
	std::fstream input;
	input.open("input.txt",std::ios::in);
	for(int i=0; i<9; i++)
	{
		for(int j=0; j<9; j++)
		{
			input >> matrix[i][j];
		}
	}
	input.close();
}
void print_matrix()
{
	for(int i=0; i<9; i++)
	{
		for(int j=0; j<9; j++)
		{
			std::cout << matrix[i][j];
		}
		std::cout << std::endl;
	}
}

int sudokuHelper(int puzzle[][9], int row, int column) 
{
	if (9 == row) { return 1; }

	if (puzzle[row][column]) 
	{
		if (column == 8) 
		{
			if (sudokuHelper(puzzle, row+1, 0)) return 1;
		} 
		else 
		{
			if (sudokuHelper(puzzle, row, column+1)) return 1;
		}
		return 0;
	}

	for (int nextNumber=1; nextNumber<10; nextNumber++) 
	{
		if(isOk(nextNumber, row, column)) 
		{
			puzzle[row][column] = nextNumber;
			if (column == 8) 
			{
				if (sudokuHelper(puzzle, row+1, 0)) return 1;
			}
			else 
			{
				if (sudokuHelper(puzzle, row, column+1)) return 1;
			}
			puzzle[row][column] = 0;
		}
	}
	return 0;
}

int solveSudoku(int puzzle[][9]) 
{
	//init();
	return sudokuHelper(puzzle, 0, 0);
}