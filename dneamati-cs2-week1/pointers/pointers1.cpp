/**
 * @file pointers1.cpp
 * @author The CS2 TA Team <cs2tas@caltech.edu>
 * @date 2015
 * @copyright This code is in the public domain.
 *
 * @brief Pointer-fu Exercise 1: Pointer declarations
 */

// Daniel Neamati
// CS 2

#include <cstdlib>
#include <iostream>

using namespace std;

/**
 * @brief Declares and sets values of pointers.
 */
int main(int argc, char *argv[])
{
    /* TODO: Put your declarations here.
     * Variable `a` is of type `int`. Only use one line! */
	int a;
	int *b;
	int c;
	int **d;
    /***** CHANGE NOTHING BELOW THIS LINE *****/
    a = 5;
    b = &a;
    c = *b;
    d = &b;
    /***** CHANGE NOTHING ABOVE THIS LINE *****/

    return 0;
}
