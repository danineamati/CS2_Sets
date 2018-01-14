/**
 * @file fileio.cpp
 * @author The CS2 TA Team
 * @version 1.0
 * @date 2013-2015
 * @copyright This code is in the public domain.
 *
 * @brief A brief example of file input (implementation).
 */

#include "fileio.hpp"
#include <iostream>
#include <fstream>
#include <string>

/**
 * @brief Reads the integers in file and fills nums with these integers.
 *
 * @param file: File containing integers, one per line.
 * @param nums: Vector to fill with the integers in file.
 *
 * Notice that the vector is passed by reference, so you should fill the vector
 * and not return anything from this function.
 */
void readFile(char const *file, std::vector<int> &nums)
{
    std::string line;
    std::ifstream currentFile(file);
    if (currentFile.is_open())
    {
    	while (getline(currentFile, line))
    	{
    		nums.push_back(stoi(line));
    	}
    }
    else 
    {
    	std::cout << "Could not open file. Verify this is yout file: ";
    	std::cout << file << std::endl;
    }
}