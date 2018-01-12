#pragma once

// Daniel Neamati
// CS 2

#include "grid.hpp"

class Sudoku : public Grid {
	// Sudoku inherits from Grid and adds a printing feature.

public:
	Sudoku(); // Constructor
	~Sudoku(); // Destructor
	void printSudoku(); // Printing the Sudoku board
};
