#pragma once

// Daniel Neamati
// CS 2

#include <string>

using namespace std;

/**
* @brief Stores the state of a game (namely sudoku)
*/
class Game
{
private:
	int moves; // The number of moves
public:
	Game(); // Constructor
	~Game(); // Destructor

	string getMove(); // Asks user for move
	void Run(); // Allows user to play Sudoku
};