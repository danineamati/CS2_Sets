/**
 * @file pointers4.cpp
 * @author The CS2 TA Team <cs2tas@caltech.edu>
 * @date 2015
 * @copyright This code is in the public domain.
 *
 * @brief Pointer-fu Exercise 4: Typecasting vs. address-of
 */

// Daniel Neamati
// CS 2

#include <cstdlib>
#include <iostream>

using namespace std;

/**
 * @brief performs type castings
 */
int main(int argc, char *argv[])
{
	/*
	* The error was that "b = (int *) a;" does not actually point to a
	* instead it sets b to the address 0x5. We want b = &a because
	* then b will contain the address of a and hence point to it.

    * Next, as a generic pointer ("void *") c cannot correctly assign
    * the allocated memory to b. By setting c to int * type, b can 
    * be assigned the new memory.
	*/

    int a = 5, *b;
    int *c;

    // Now make `b` point to `a`.
    b = &a;

    /***** CHANGE NOTHING BELOW THIS LINE *****/
    cout << "The value pointed by `b` is " << *b;
    /***** CHANGE NOTHING ABOVE THIS LINE *****/

    // Allocate an array of 10 ints.
    c = (int *) malloc(10 * sizeof(int));

    // Get the address of the array.
    b = c;

    /***** CHANGE NOTHING BELOW THIS LINE *****/
    b[2] = 5;
    /***** CHANGE NOTHING ABOVE THIS LINE *****/

    free(c);

    return 0;
}
