/**
 * @file
 * @author The CS2 TA Team
 * @version 1.0
 * @date 2013-2014
 * @copyright This code is in the public domain.
 *
 * @brief The bubble sort, quick sort, merge sort, and in-place quicksort
 * algorithms (implementation).
 *
 */
#include "sorter.hpp"

int main(int argc, char* argv[])
{
    // Set up buffers and data input
    std::vector<int> nums;
    std::string line;
    char *filename;
    int sort_type;

    // Ensure that at most one type of sort and at least a filename are specified.
    if (argc > 3 || argc < 2)
    {
        usage();
    }

    // default sort is bubble sort
    sort_type = BUBBLE_SORT;

    // Figure out which sort to use
    for (int i = 1; i < argc; ++i)
    {
        char *arg = argv[i];
        if (strcmp(arg, "-b") == 0) { sort_type = BUBBLE_SORT; }
        else if (strcmp(arg, "-q") == 0) { sort_type = QUICK_SORT; }
        else if (strcmp(arg, "-m") == 0) { sort_type = MERGE_SORT; }
        else if (strcmp(arg, "-qi") == 0) { sort_type = QUICK_SORT_INPLACE; }
        else { filename = argv[i]; }
    }

    // Read the file and fill our vector of integers
    // THIS FUNCTION IS STUDENT IMPLEMENTED
    readFile(filename, nums);

    switch (sort_type)
    {
        case BUBBLE_SORT:
        print_vector(bubbleSort(nums));
        break;

        case QUICK_SORT:
        print_vector(quickSort(nums));
        break;

        case MERGE_SORT:
        print_vector(mergeSort(nums));
        break;

        case QUICK_SORT_INPLACE:
        quicksort_inplace(nums, 0, nums.size() - 1);
        print_vector(nums);
        break;

        default:
        usage();
        break;
    }
    return 0;
}

/**
 * Usage    Prints out a usage statement and exits.
 */
void usage()
{
    std::cerr << usage_string << std::endl;
    exit(1);
}

/**
 * TO STUDENTS: In all of the following functions, feel free to change the
 * function arguments and/or write helper functions as you see fit. Remember to
 * add the function header to sorter.hpp if you write a helper function!
 */

/**
 * This function sort a list by bubbling up large elements to the right.
 * It does this by looping through a vector. If the element is larger than the
 * adjacent element after it, it swaps those numbers. After each iteration,
 * it no longer has to loop through the sorted elements.
 */
std::vector<int> bubbleSort(std::vector<int> &list)
{
    int remaining = list.size() - 1;
    while (remaining > 0)
    {
        int last_swap = 0; // No last swap yet
        for (int i = 0; i < remaining; i++)
        {
            if (list[i] > list[i + 1]) // Elements can switch
            {
                int temp = list[i + 1]; // Save next element
                list[i + 1] = list[i]; // Swap elements
                list[i] = temp; // Return next to current
                last_swap = i; // This is the new most recent swap
            }
        }
        remaining = last_swap; // If we get lucky, we don't need to loop the last
        // few elements.
    }
    return list;
}

/**
 * TODO: Implement this function.
 */
std::vector<int> quickSort(std::vector<int> &list)
{
    return list;
}

/**
 * TODO: Implement this function.
 */
std::vector<int> mergeSort(std::vector<int> &list)
{
    return list;
}

/**
 * TODO: Implement this function.
 */
std::vector<int> merge(std::vector<int> &left, std::vector<int> &right)
{
    return left;
}

/*
 * quicksort_inplace:  In-place version of the quicksort algorithm. Requires
 *              O(1) instead of O(N) space, same time complexity. Each call of
 *              the method partitions the list around the pivot (an item taken
 *              from the middle of the array) with items left of the pivot
 *              smaller than it and items to its right larger than it. Then the
 *              method recursively sorts the left and right portions of the list
 *              until it reaches its base case: a list of length 1 is already
 *              sorted.
 *
 * @param list: pointer to integer array to be sorted
 * @returns:    Nothing, the array is sorted IN-PLACE.
 *
 * TODO: Implement this function.
 */
void quicksort_inplace(std::vector<int> &list, int left, int right)
{
    return;
}

