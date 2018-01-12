/**
 * @file pointers2.cpp
 * @author The CS2 TA Team <cs2tas@caltech.edu>
 * @date 2015
 * @copyright This code is in the public domain.
 *
 * @brief Pointer-fu Exercise 2: Uninitialized pointers
 */

// Daniel Neamati
// CS 2

#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace std;

/**
 * @brief Allocates and frees an array of 10 ints if timestamp is odd.
 */
int main(int argc, char *argv[])
{
    // There were two errors, first 'a' was not set to the nullptr
    // so the program cannot be sure if it needs to free the allocated
    // memory if (t % 2 != 0). I fixed this by setting 'a' to the 
    // nullptr.
    
    // The second error was that <ctime> was not included so the
    // program could not have know the current Unix timestamp.

    int *a = nullptr;
    time_t t = time(nullptr); // Get the current Unix timestamp

    /***** CHANGE NOTHING BELOW THIS LINE *****/
    if (t % 2)
    {
        // Allocate an array of 10 ints if the timestamp is an odd number.
        // This is a contrived way to conditionally allocate some memory.
        a = (int *) malloc(10 * sizeof(int));
        cout << "allocating some memory!\n";
    }
    /***** CHANGE NOTHING ABOVE THIS LINE *****/

    // If we allocated memory, free it!
    if (a) 
    {
        free(a);
        cout << "freeing the memory." << endl;
    }

    return 0;
}
