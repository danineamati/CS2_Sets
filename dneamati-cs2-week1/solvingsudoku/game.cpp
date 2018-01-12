// Daniel Neamati
// CS 2

#include "game.hpp"
#include "sudoku.hpp"
#include <string>
#include <cassert>
#include <iostream>

using namespace std;

// Constructor: Initialize a new game
Game::Game() {
	moves = 0;
}

// Destructor
Game::~Game() {
    // No memory in heap	
}

/*
 * @ brief Receives user input for a move
 */
string Game::getMove() {
	string current_move;
	cout << "Enter move: ";

	// Load the player move
	getline(cin, current_move);

	return current_move;
	
}

/*
 * @ brief Runs a game of sudoku. Call helper functions
 * for user input, loading board, etc.
 */
void Game::Run() {
	Sudoku Sud_grid;

	// Load Grid from file
	string filename;
	cout << "Enter File to load: " << endl;
	cin >> filename;
	int loaded = Sud_grid.loadBoard(filename);

	if(loaded == 0)
	{
		// To start off the User, we will print the original board
		Sud_grid.printSudoku();
		cin.ignore();


		// Now we begin the game loop
		while (!Sud_grid.isComplete()) 
		{
			string current_move = getMove();
			
			// if d, register move
			if (current_move[0] == 'd' && current_move.size() >= 7) 
			{
	            // check if move allowed
	            // - '1' is needed to cast char to int and index at 1 
	            // rather than 0
	            if (Sud_grid.checkValid((int) current_move[2] - '1', 
	            	(int) current_move[4] - '1', current_move[6])) 
	            {
	            	Sud_grid.writeNum((int) current_move[2] - '1', 
	            	(int) current_move[4] - '1', current_move[6]);
	            }
	            	
			}
			
			// if u, undo move
			else if (current_move[0] == 'u' && current_move.size() == 5) 
			{
				// check if user defined.
				// - '1' is needed to cast char to int and index at 1 
	            // rather than 0
				Sud_grid.undoNum((int) current_move[2] - '1', 
	            	(int) current_move[4] - '1');
			}

			// if q, quit
			else if (current_move[0] == 'q' && current_move.size() <= 2)
			{
				break;
			}

			// Anything else is invalid
			else
			{
				cout << "ERROR! Move: " << current_move;
				cout << " is not valid. ";
				cout << "Please try again." << endl;
			}

			Sud_grid.printSudoku();
			moves ++;
		}
		

		if (Sud_grid.isComplete())
		{
			cout << "Congratulaions!!!" << endl;
			cout << " You SOLVED this sudoku puzzle in ";
			cout << moves << " moves!" << endl;
		}
	}
}