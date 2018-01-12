// Daniel Neamati
// CS 2

#include "game.hpp"
#include "sudoku.hpp"
#include <iostream>

using namespace std;

/*
 * @ brief Completely uses the Grid Constructor
 */

Sudoku::Sudoku() : Grid() {
	// Construct exactly like grid
}

/*
 * @ brief Destructor
 */
Sudoku::~Sudoku() {
	// No heap allocated memory
}

/*
 * @ brief Prints the Sudoku Board at current state
 */
void Sudoku::printSudoku()
{
	// Start by printing the top of the board
	cout << "-------------------------" << endl;

	for (int row = 0; row < 9; row ++)
	{
		cout << "| ";

		for (int col = 0; col < 9; col ++)
		{
			cout << grid[row][col] << ' ';
			if (col % 3 == 2)
				cout << "| ";
		}

		cout << endl;

		if (row % 3 == 2)
			cout << "-------------------------" << endl;
	}

}


/*
* @brief Loads and runs a Sudoku game
*/
int main()
{
	Game Sudoku_game;
	Sudoku_game.Run();
	return 0;
}