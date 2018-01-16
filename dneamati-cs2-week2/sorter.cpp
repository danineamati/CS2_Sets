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

/*
 * Daniel Neamati
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
 * For simplicity, the first element will be chosen as the pivot. The
 * rightmost element is checked. 
 *
 * If it is larger than the pivot, we skip it and check the next element.
 *
 * If it is smaller than the pivot, the value is moved to the left of 
 * the pivot. 
 * This happens by swapping the unchecked value (U) the to right of the pivot
 * (P) with the value being checked (V). Then swapping the pivot andthe value
 * being checked:
 *
 * 4 5 2 3 1 2 7 3
 * ^ ^         ^
 * P U         V
 *
 * 4 7 2 3 1 2 5 3
 * ^ ^         ^
 * P V         U
 *
 * 7 4 2 3 1 2 5 3
 * ^ ^         ^
 * V P         U
 * 
 * It then splits the two sides into two vectrors to be sorted.
 *
 * @param list: pointer to vector of arrays to by sorted
 * @return: the sorted list
 */
std::vector<int> quickSort(std::vector<int> &list)
{
    if (list.size() <= 1)
        return list;
    else
    {
        int pivot = list[0];
        int pivot_index = 0;
        for (int i = list.size() - 1; i > pivot_index; i--)
        {
            if (list[i] < pivot) // Swap needs to happen
            {
                // Swap 'U' with 'V'
                int temp = list[pivot_index + 1];
                list[pivot_index + 1] = list[i];
                list[i] = temp;

                // Swap pivot and 'V'
                temp = list[pivot_index];
                list[pivot_index] = list[pivot_index + 1];
                list[pivot_index + 1] = temp;

                i++; // Stay at same i, since value unchecked
                pivot_index++;
            }
        }

        // Now we split the vector in two
        // Start by making the left vector (not including the pivot)
        std::vector<int>::const_iterator left_start = list.begin();
        std::vector<int>::const_iterator left_end = 
            list.begin() + pivot_index;
        std::vector<int> left(left_start, left_end);

        // Recursively call quicksort on list
        left = quickSort(left);
        

        // Repeat with right vector
        std::vector<int>::const_iterator right_start =
            list.begin() + pivot_index + 1;
        std::vector<int>::const_iterator right_end = list.end();
        std::vector<int> right(right_start, right_end);

        // Recursively call quicksort on list
        right = quickSort(right);


        // Now we recombine the sorted lists
        list = quickmerge(left, pivot, right);
    }
    return list;
}


/**
 * @brief: appends the pivot and the contents in the right list to contents
 * in the left list
 */
std::vector<int> quickmerge(std::vector<int> &left, int pivot, 
    std::vector<int> &right)
{
    left.push_back(pivot);

    for (size_t i = 0; i < right.size(); i++)
    {
        left.push_back(right[i]);
    }
    return left;
}


/**
 * Merge Sort will split the vector in two and then call merge sort
 * followed by merge on each half.
 * It has the base case that if the size of the vector is one, it is
 * definitely sorted so it can return it directly.
 * By the time the sublists are merged, the sublists are sorted with
 * respect to itself.
 *
 * @param list: pointer to vector of arrays to by sorted
 * @return: the sorted list
 */
std::vector<int> mergeSort(std::vector<int> &list)
{
    if (list.size() <= 1)
        return list;

    // Split list in two

    // Left vector
    std::vector<int>::const_iterator left_start = list.begin();
    std::vector<int>::const_iterator left_end = 
        list.begin() + (list.size() / 2);
    std::vector<int> left(left_start, left_end);

    // Right vector
    std::vector<int>::const_iterator right_start = 
        list.begin() + (list.size() / 2);
    std::vector<int>::const_iterator right_end = 
        list.begin() + list.size();
    std::vector<int> right(right_start, right_end);


    // Recursively call mergesort on each list
    left = mergeSort(left);
    right = mergeSort(right);
    list = merge(left, right);

    return list;
}

/**
 * @ brief: Takes two sorted vectors and merges them together.
 */
std::vector<int> merge(std::vector<int> &left, std::vector<int> &right)
{
    std::vector<int> merged;

    while (!left.empty() && !right.empty())
    {
        if (left[0] <= right[0])
        {
            merged.push_back(left[0]);
            // now we remove first element of left so we do not repeat it
            left.erase(left.begin());
        }
           
        else if (right[0] < left[0]) 
        {
            merged.push_back(right[0]);
            // now we remove first element of right so we do not repeat it
            right.erase(right.begin());
        }
    }

    // Because of the "and" above left or right may not be empty.
    while (!left.empty())
    {
        merged.push_back(left[0]);
        // now we remove first element of left so we do not repeat it
        left.erase(left.begin());
    }

    while (!right.empty())
    {
        merged.push_back(right[0]);
        // now we remove first element of right so we do not repeat it
        right.erase(right.begin());
    }

    return merged;
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
    if (list.size() <= 1)
        return;
    else
    {
        int pivot = list[left];
        int pivot_index = left;
        for (int i = right; i > pivot_index; i--)
        {
            if (list[i] < pivot) // Swap needs to happen
            {
                // Swap 'U' with 'V'
                int temp = list[pivot_index + 1];
                list[pivot_index + 1] = list[i];
                list[i] = temp;

                // Swap pivot and 'V'
                temp = list[pivot_index];
                list[pivot_index] = list[pivot_index + 1];
                list[pivot_index + 1] = temp;

                i++; // Stay at same i, since value unchecked
                pivot_index++;
            }
        }

        // Now we split the vector in two
        // Start by making the left vector (not including the pivot)
        if (pivot_index > 0) {
            int left_start = 0;
            int left_end = pivot_index - 1;

            // Recursively call quicksort on sub-list
            quicksort_inplace(list, left_start, left_end);
        }
        

        // Repeat with right vector
        if (pivot_index < right - 1)
        {
            int right_start = pivot_index + 1;
            int right_end = right;

            // Recursively call quicksort on sub-list
            quicksort_inplace(list, right_start, right_end);
        }
    }
    return;
}

