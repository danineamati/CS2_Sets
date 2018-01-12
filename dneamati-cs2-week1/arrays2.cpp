/**
 * @file arrays1.cpp
 * @author The CS2 TA Team <cs2tas@caltech.edu>
 * @date 2014-2015
 * @copyright This code is in the public domain.
 *
 * @brief An array example.
 */

// Daniel Neamati
// CS 2

#include <iostream>
#include <cstdlib>
#include <ctime>

#define TEST_SIZE 60

using namespace std;

/**
* @brief Prints out the elements of an integer array.
*
* @param arr the array to print
* @param n   the number of elements in the array
*/
void array_print(int * arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << *(arr + i);
        if (i < n - 1)
            cout << ", ";
    }
    cout << endl;
}

/**
* @brief Returns the largest value in the array.
*
* @param arr       the array to consider
* @param arr_size  the number of elements in the array
*/
int max_val(int * arr, int arr_size) 
{
    int max = *(arr);
    for (int i = 1; i < arr_size; i++)
    {
        if (*(arr + i) > max)
            max = *(arr + i);
    }
    return max;
}

/**
* @brief Returns the arithmetic mean of elements in the array.
*
* @param arr       the array to consider
* @param arr_size  the number of elements in the array
*/
double arith_mean(int * arr, int arr_size)
{
    double sum = 0;
    for (int i = 0; i < arr_size; i++)
    {
        sum += *(arr + i);
    }
    return sum / arr_size;
}

/**
* @brief No return. Puts array in ascending order from the first entry.
*
* @param arr       the array to consider
* @param arr_size  the number of elements in the array
*/
void ascending(int * arr, int arr_size)
{
    for (int i = 0; i < arr_size; i++)
    {
        *(arr + i) = i + *(arr);
    }
}

/**
 * @brief Sets up and runs an array example.
 */
int main(int argc, char ** argv)
{

    /*-------- CHANGE NOTHING BELOW THIS LINE FOR PART 1 --------*/
    int *test_values = new int [TEST_SIZE];
    int real_size;

    // seed the PRNG
    srand(time(nullptr));

    // initialize the test array to garbage
    for (int i = 0; i < TEST_SIZE; i++)
    {
        *(test_values + i) = rand();
    }

    // determine a real size
    real_size = TEST_SIZE - (rand() % 20);

    // initialize the meaningful part of the test array to random numbers
    // all of which are less than one million
    for (int i = 0; i < real_size; i++)
    {
        *(test_values + i) = rand() % 10000000;
    }
    /*-------- CHANGE NOTHING ABOVE THIS LINE FOR PART 1 --------*/

    //
    // TODO: do your stuff here with the array `test_values`
    // of dynamic size `real_size`
    //

    cout << "Maximum Value: ";
    cout << max_val(test_values, real_size) << endl;
    
    cout << "Arithmetic Mean: ";
    cout << arith_mean(test_values, real_size) << endl;

    // Print the array beforehand
    array_print(test_values, real_size);
    // Put the array in ascending sequence
    ascending(test_values, real_size);
    // Print the array after the change
    array_print(test_values, real_size);

    delete[] test_values;


}
