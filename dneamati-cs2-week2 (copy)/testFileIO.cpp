/**
 * @file testFileIO.cpp
 * @author The CS2 TA Team
 * @version 1.0
 * @date 2013-2015
 * @copyright This code is in the public domain.
 *
 * @brief A brief example of file input.
 */

#include "fileio.hpp"
#include <vector>

/**
 * @brief Read the file input and print out its contents
 *
 * Assumes that the file contains one integer per line.
 */
int main(int argc, char const *argv[])
{

    if (argc == 2)
    {
    	//instantiates a vector, calls the readFile and print_vector
    	std::vector<int> nums;
    	readFile(argv[1], nums);
    	print_vector(nums);
    }
    else
    {
    	std::cout << "Must include exactly one addition arguement." << std::endl;
    	std::cout << "Example: ./testFileIO nums" << std::endl;
    }

    return 0;
}
