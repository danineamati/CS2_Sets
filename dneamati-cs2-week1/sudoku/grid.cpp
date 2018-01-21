// Daniel Neamati
// CS 2

#include "grid.hpp"
#include <iostream>
#include <fstream>

using namespace std;

/*
 * @ brief Constructor initializes the base and actually grid to empty
 */
Grid::Grid()
{
	// Set al grid values to 0
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++) 
		{
			base_grid[row][col] = ' ';
			grid[row][col] = ' ';
		}
	}
}

/*
 * @ brief Destructor
 */
Grid::~Grid()
{
	// No memory allocated on heap
}

/*
 * @ brief Loads board from file
 */
int Grid::loadBoard(string filename)
{
	string line;
	ifstream gameFile(filename.c_str());

	if (!gameFile) 
	{
		cout << "Unable to open file: " << filename << endl;
		return 1;
	}

	else {

		int row_num = 0;

		while (getline(gameFile, line))
		{
			for (int col = 0; col < 9; col++)
			{
				base_grid[row_num][col] = line[col];
				grid[row_num][col] = line[col];
			}

			row_num ++;
		}

	}

	gameFile.close();

	return 0;
}

/*
 * @ brief Checks if board is complete
 */
bool Grid::isComplete()
{
	for (int row = 0; row < 9; row ++)
	{
		for (int col = 0; col < 9; col ++)
		{
			// Load value to check at row and col
			char val = grid[row][col];

			// Check no box is empty
			if (val == ' ')
				return false;

			// Check Horizontal
			for (int col_check = 0; col_check < 9; col_check ++)
			{
				if (grid[row][col_check] == val && col_check != col) 
				{
					return false;
				}
			}

			// Check Vertical
			for (int row_check = 0; row_check < 9; row_check ++)
			{
				if (grid[row_check][col] == val && row_check != row) 
				{
					return false;
				}
			}

			// Box Check
			/*
			* Overview of below operations:
			* "row_box = row - (row % 3)" sets row_box to left edge of wall
			* Add three to get one past the right edge
			* likewise for column
			*/
			for (int row_box = row - (row % 3); 
				row_box < (row - (row % 3) + 3); row_box ++)
			{
				for (int col_box = col - (col % 3); 
					col_box < (col - (col % 3) + 3); col_box ++)
				{
					// That that number not repeated in box
					// Hence must be at different row or column
					if (grid[row_box][col_box] == val 
						&& (row_box != row || col_box != col))
					{
						return false;
					}
				}
			}
		}
	}
	// If it has passed the above checks, move is valid
	return true;
}

/*
 * @ brief Checks if a user move is valid
 */
bool Grid::checkValid(int row, int col, char val)
{
	// ROW AND COLUMN have been 0-indexed as inputs!!
	// Check if 0 <= row <= 8 and 0 <= col <= 8
	if (row < 0 || row > 8)
	{
		cout << "ERROR: Row numbers should be 1-9";
		cout << endl;
		return false;
	}

	if (col < 0 || col > 8)
	{
		cout << "ERROR: Column numbers should be 1-9";
		cout << endl;
		return false;
	}

	// Check cell is empty
	if (grid[row][col] != ' ') 
	{
		cout << "ERROR! ";
		cout << "Cell is not empty!" << endl;
		return false;
	}

	// Check Horizontal
	for (int col_check = 0; col_check < 9; col_check ++)
	{
		if (grid[row][col_check] == val) 
		{
			cout << "ERROR! ";
			cout << val << " is already in row " << row << endl;
			return false;
		}
	}

	// Check Vertical
	for (int row_check = 0; row_check < 9; row_check ++)
	{
		if (grid[row_check][col] == val) 
		{
			cout << "ERROR! ";
			cout << val << " is already in column " << col << endl;
			return false;
		}
	}

	// Box Check
	/*
	* Overview of below operations:
	* "row_box = row - (row % 3)" sets row_box to left edge of wall
	* Add three to get one past the right edge
	* likewise for column
	*/
	for (int row_box = row - (row % 3); row_box < (row - (row % 3) + 3);
	      row_box ++)
	{
		for (int col_box = col - (col % 3); col_box < (col - (col % 3) + 3);
		      col_box ++)
		{
			if (grid[row_box][col_box] == val)
			{
				cout << "ERROR! ";
				cout << val << " is already in box." << endl;
				return false;
			}
		}
	}

	// If it has passed the above checks, move is valid
	return true;
}

/*
 * @ brief Writes to the grid (not to base_grid)
 */
void Grid::writeNum(int x, int y, char val)
{
	grid[x][y] = val;
}

/*
 * @ brief Undos a move at a given location if not original number
 */
void Grid::undoNum(int x, int y)
{
	// Recall that base_grid is unmodified from the original
	if (base_grid[x][y] != ' ')
	{
		cout << "ERROR! ";
		cout << "Cell is not user entered. Cannot remove original." << endl;
	}
	else {
		grid[x][y] = ' ';
	}
}
