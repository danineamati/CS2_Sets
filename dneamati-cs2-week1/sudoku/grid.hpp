#pragma once

// Daniel Neamati
// CS 2

#include <string>

using namespace std;

/*
 * @ brief Makes a Sudoku Grid that can be written to and loaded
 */
class Grid
{
private:
	char base_grid[9][9]; // This is the original untouched board
protected:
	char grid[9][9]; // The Sudoku Grid is 9 by 9
public:
	Grid();    // Constructor
	~Grid();   // Destructor

	int loadBoard(string filename); // Loads base_grid and grid

	bool isComplete();    // Check if user has solved the puzzle
	bool checkValid(int x, int y, char val);   // Check individual move

	// Mutators
	void writeNum(int x, int y, char val);  // Fill in move
	void undoNum(int x, int y); // Undo move (Fill with empty)
};