/**
 * @file
 * @author The CS2 TA Team
 * @version 1.0
 * @date 2013-2014
 * @copyright This code is in the public domain.
 *
 * @brief The gift wrapping and Graham scan convex hull algorithms
 * (implementation).
 *
 */
#include "HullAlgorithms.hpp"

/**
 * @brief: Prints a vector of points
 */
void printPoints(vector<Tuple*> points)
{
    for (int i = 0; i < (int) points.size(); i++)
    {
        points[i]->printTuple();
    }
    cout << endl;
}

/**
 * @brief: Finds the smallest point in a vector
 * @return: The index of the smallest point
 */
int smallest_point(vector<Tuple*> points)
{
    int index_small = 0;
    Tuple* smallest_pt = points[index_small];
    for (size_t i = 1; i < points.size(); i++)
    {
        if (points[i]->x < smallest_pt->x)
        {
            smallest_pt = points[i];
            index_small = i;
        }
    }
    return index_small;
}

/**
 * @brief: Finds the cross product of two vector from a common known point
 * @return: true if the cross product is greater than 0.
 */
bool crossproduct(Tuple *pt_known, Tuple *pt_next, Tuple *pt_checking)
{
    int x1 = pt_next->x - pt_known->x;
    int x2 = pt_checking->x - pt_known->x;
    int y1 = pt_next->y - pt_known->y;
    int y2 = pt_checking->y - pt_known->y;

    double crossp = x1 * y2 - x2 * y1;
    if (crossp > 0)
        return true;
    return false;
}


/**
 * TO STUDENTS: In all of the following functions, feel free to change the
 * function arguments and/or write helper functions as you see fit. Remember to
 * add the function header to HullAlgorithms.hpp if you write a helper function!
 *
 * Our reference implementation has four helper functions and the function(s)
 * copied over from angleSort.cpp.
 */

/**
 * TODO: Implement this function.
 */
void DoGiftWrap(vector<Tuple*> points, ConvexHullApp *app)
{
    // First we need to find the leftmost point (point with smallest x)
    int index_small = smallest_point(points);
    Tuple* smallest_pt = points[index_small];
    app->add_to_hull(smallest_pt);

    int next_pt;
    int min = 0;
    if (index_small != 0)
        next_pt = 0;
    else
    {
        next_pt = 1;
        min ++;
    }

    Tuple* new_pt = smallest_pt;

    // Loop until we land at the initial point
    while (next_pt != index_small)
    {
        //Reset next point to minimum to check
        next_pt = min;

        // Loop through all of the points on the board
        for (unsigned int i = min + 1; i < points.size(); ++i)
        {
            bool cross = crossproduct(new_pt, points[next_pt], points[i]);

            // The cross product between the points is positive, we can set is
            // as the new next point
            if (cross)
            {
                next_pt = (int) i;
            }
        }
        if (next_pt == min)
            min++;

        // We have found the furthest out point, so we add it to the hull
        new_pt = points[next_pt];
        app->add_to_hull(points[next_pt]);
    }
}

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
    if (angles.size() <= 1)
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

/**
 * @brief: Finds the smallest angle between two vectors
 * @return: The index of the colinear point
 */
int smallest_angle(vector<Tuple*> points, int prev_pt, double prev_angle)
{
    int next_pt = 0;
    Tuple* smallest_pt = points[prev_pt];
    double low_diff = 10;

    // Check every point that is not the current point
    for (unsigned int i = 0; i < points.size(); ++i)
    {
        if ((int) i != prev_pt)
        {
            double diff = prev_angle - smallest_pt->angle_wrt_pt(points[i]);

            cout << "Angle: " << smallest_pt->angle_wrt_pt(points[i]) << endl;
            points[i]->printTuple();
            cout << ' ' << diff << endl;

            if (diff < low_diff && diff > 0) 
            {
                next_pt = (int) i;
                cout << "New low: " << next_pt << ' ' << diff << endl;
                low_diff = diff;
            }
        }
    }
    return next_pt;
}

 /**
 * TODO: Implement this function.
 */
void DoGrahamScan(vector<Tuple*> points, ConvexHullApp *app)
{
    for (unsigned int i = 0; i < points.size(); ++i)
    {
        app->add_to_hull(points[i]);
    }
    app->add_to_hull(points[0]);
}
