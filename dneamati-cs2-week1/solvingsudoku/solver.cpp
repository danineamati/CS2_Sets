// Daniel Neamati
// CS 2
#include "sudoku.hpp"
#include "game.hpp"
#include <vector>
#include <iostream>

using namespace std;

/*
 * @ brief: This is a depth-first search algorithm
 *
 * time complexity: A lot harder for larger boards
 *  algorithm has to loop through the a good portion of the board
 *  for each cell. So based on number of cells n, the algorithm is
 *  worst case likey O(n^2)
 *
 * space complexity: At most the vector of paths holds the full board
 *  which is of size n. Thus O(n).
 */



/*
 * @ brief Create a class that can pass information about a cell between 
 * functions
 */
class Placed_cell {
public:
    // The row, column, and value of the cell
    int row;
    int col;
    char val;

    // Constructors for initializing cells
    Placed_cell(int row, int col, char val) : row(row), col(col), val(val) { }
    Placed_cell() : row(0), col(0), val(' ') { }
    ~Placed_cell() { }
    
    // Returns true if this cell is the same as the specified cell
    bool operator==(const Placed_cell &cell) const {
        return row == cell.row && col == cell.col && val == cell.val;
    }
    
    // Returns true if this cell is different from the specified cell
    bool operator!=(const Placed_cell &cell) const {
        return !(*this == cell);
    }
};

// Finds first empty cell
Placed_cell find_first(Sudoku & sud) {
	Placed_cell first; // Set to default

	for (int row = 0; row < 9; row ++)
		{
			for (int col = 0; col < 9; col ++) 
			{
				if (sud.grid[row][col] == ' ')
				{
					int val = 1;

					while (true)
					{
						if (sud.checkValid(row, col, static_cast<char>(val)))
	            		{
	            			first = Placed_cell(row, col, static_cast<char>(val));
	            			break;
	            		}

	            		if (val > 9)
	            			break;

	            		val ++;
	            	}
	            }
	        }
	    }

	return first;
}

/*
 * @ brief Attempts a Depth first search
 */
int main()

{
	// Initialize Sudoku
	Sudoku Sud_grid;

	// Initialize Path of visited cells
	vector<Placed_cell> path;

	// Load Grid from file
	string filename;
	cout << "Enter File to load: " << endl;
	cin >> filename;
	int loaded = Sud_grid.loadBoard(filename);

	// We proceed only if the loading worked
	if (loaded == 0)
	{
		// Find first empty cell
		path.push_back( find_first(Sud_grid));
		
		while (!path.empty()) {
			// Unfortunately I could not complete the rest in time
			// the rest is pseudocode
			path.pop_back(); // Included so it compiles

			// vector<char> options; // Make a vector to contain possible
			// numbers for a spot

			// for loop 0 to 9 to push back ones that work to options

			// if (options.size() == 0); we reached a problem. The empty cell
			// means that the board is invalid
				// path.pop_back() // removes the last cell

			// else
				// choose the lowest number
				// write to Sudoku
				// path.push_back() the placed_cell

		}
	}

	Sud_grid.printSudoku();

	return 0;
}