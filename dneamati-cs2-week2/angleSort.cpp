/**
 * @file
 * @author The CS2 TA Team
 * @version 1.0
 * @date 2013-2014
 * @copyright This code is in the public domain.
 *
 * @brief An example of sorting (x, y) pairs by angle.
 *
 */
#include "structs.hpp"
#include <vector>


/**
 * @brief: This is a modification of the in-place quick sort algorithm that
 *         will sort a vector of angles and points based on the angle.
 * @param: points: A vector of 2D Cartesian Coordinates
 *         angles: A vector of point angles with the x-axis
 *         left: Left bound to be sorted
 *         right: Right bound to be sorted
 */
void sort(vector<Tuple*> &points, vector<double> &angles, int left, int right)
{
    if (right - left <= 1)
        return;
    else
    {
        double pivot = angles[left];
        int pivot_index = left;
        for (int i = right; i > pivot_index; i--)
        {
            if (angles[i] < pivot) // Swap needs to happen
            {
                // Swap value right of pivot with large angle
                double temp = angles[pivot_index + 1];
                Tuple* temp_point = points[pivot_index + 1];

                angles[pivot_index + 1] = angles[i];
                points[pivot_index + 1] = points[i];
                angles[i] = temp;
                points[i] = temp_point;

                // Swap pivot and large angle
                temp = angles[pivot_index];
                temp_point = points[pivot_index];

                angles[pivot_index] = angles[pivot_index + 1];
                points[pivot_index] = points[pivot_index + 1];
                angles[pivot_index + 1] = temp;
                points[pivot_index + 1] = temp_point;

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
            sort(points, angles, left_start, left_end);
        }
        

        // Repeat with right vector
        if (pivot_index < right - 1)
        {
            int right_start = pivot_index + 1;
            int right_end = right;

            // Recursively call quicksort on sub-list
            sort(points, angles, right_start, right_end);
        }
    }
    return;
}

int main(int argc, char const *argv[])
{
    vector<double> angles {4.2, 2.8, 1.4, 5.0, 3.3};
    vector<Tuple*> points;
    // Print the initial points and angles
    for (unsigned int i = 0; i < angles.size(); ++i)
    {
        points.push_back(new Tuple(i, i));
    }
    for (vector<Tuple*>::iterator i = points.begin(); i != points.end(); ++i)
    {
        (*i)->printTuple();
    }
    for (vector<double>::iterator i = angles.begin(); i != angles.end(); ++i)
    {
        cout << *i << endl;
    }

    // Now sort them with respect to angle (points[i] corresponds to angle[i])

    /** THIS IS THE ONLY LINE OF THE MAIN LOOP YOU NEED TO MODIFY. */
    sort(points, angles, 0, (int) angles.size() - 1);
    /** REPLACE THE LINE ABOVE WITH A CALL TO YOUR SORTING FUNCTION. */

    // and print out the new points and angles
    for (vector<Tuple*>::iterator i = points.begin(); i != points.end(); ++i)
    {
        (*i)->printTuple();
    }
    for (vector<double>::iterator i = angles.begin(); i != angles.end(); ++i)
    {
        cout << *i << endl;
    }

    // Don't want to leak memory...
    // Either of the below implementations works
    // for (std::vector<Tuple*>::iterator i = points.begin(); i != points.end(); ++i)
    // {
    //     delete (*i);
    // }
    for (unsigned int i = 0; i < points.size(); ++i)
    {
        delete points[i];
    }
    return 0;
}
