/**
 * @file debugging1.cpp
 * @author The CS2 TA Team <cs2tas@caltech.edu>
 * @date 2014-2015
 * @copyright This code is in the public domain.
 *
 * @brief An example of the utility of print statements in debugging.
 */

// Daniel Neamati
// CS 2

/*
* What is being computed with a and b?
* a and b are being mulitplied. The value x is the product of a and b. 
* x is the product of a and b. Essentially it reduces the multiplication
* to a series of multiplication by 2 and adding a remaining term if b 
* is odd.
*/

#include <iostream>

using namespace std;

/**
 * @brief Does a thing.
 *
 * Does a thing, I dunno, you tell me.
 */
int main(int argc, char ** argv)
{
    // Much of the following is intentionally undocumented.
    // Part of the assignment is to figure out what is going on.
    // You may need to look up some operators!
    unsigned int a = 174, b = 85, x = 0;

    // This construct is known as a 'while loop'.
    // The interior of the loop is run if, and while,
    // the given condition is true.
    // The program proceeds past the loop if, and when,
    // the given condition is found to be false just before any iteration
    // of the interior of the loop.
    while (b != 0)
    {   
        // This construct is known as a conditional statement
        // ('if' statement).
        // The interior of the statement is run exactly once in its entirety
        // if the given condition is found to be true.
        // Note that 'true' is defined as nonzero,
        // and 'false' is defined as zero.

        // If b is odd, we need to add a to x
        if ((b & 1) != 0)
        {   
            x += a;
            // cout << "x: " << x << endl;
        }
        
        // Now we multiply a by 2 and divide b by 2. Note that if b is odd,
        // we round down.
        a <<= 1; 
        b >>= 1; // After sufficient iterations, b goes to 0.
        
        /*
        cout << "a: " << a << endl;
        cout << "b: " << b << endl;
        cout << "x: " << x << endl;
        cout << "-------" << endl; // Used to clarify the end of the loop.
        */
    }
    cout << "The product of 174 and 85 is " << x << endl;

    // Question for you now: so what is x anyway?
    // x is the product of a and b. Essentially it reduces the multiplication
    // to a series of multiplication by 2 and adding a remaining term if b 
    // is odd.

    return 0;
}
