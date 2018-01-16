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

/*
 * Daniel Neamati
 */

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
 * @brief: Implements Gift Wrapping Algorithm of the Convex Hull
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
 * @brief: Prints a vector of points and angles
 */
void printPointsAngles(vector<Tuple*> points, vector<double> angles)
{
    for (int i = 0; i < (int) points.size(); i++)
    {
        points[i]->printTuple();
        cout << angles[i] << endl;
    }
    cout << endl;
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


/**
 * @brief: Finds the smallest angle between two vectors
 * @return: The index of the colinear point
 */
vector<double> calculateAngles(vector<Tuple*> &points, int index_small)
{
    vector<double> angles;
    double angle;
    for (int i = 0; i < (int) points.size(); ++i)
    {
        //angle = points[index_small]->angle_wrt_pt(points[i]);
        angle = points[i]->angle_wrt_x_axis();
        angles.push_back(angle);
    }

    return angles;
}

/**
 * @brief: Finds the smallest angle between two vectors
 * @return: The index of the colinear point
 */
bool testPoint(ConvexHullApp *app, vector<Tuple*> &points, int hull_pt, int test_pt)
{
    cout << hull_pt << endl;

    // The last sorted point is always in the hull, so we set the end of the
    // recursion as the last point
    if (test_pt == (int) points.size() - 1)
    {
        app->add_to_hull(points[test_pt]);
        return true;
    }

    for (int next_pt = test_pt + 1; next_pt < (int) points.size(); next_pt ++)
    {
        bool cross = crossproduct(points[test_pt], points[hull_pt],
                points[next_pt]);

        // If right turn discard test_pt and return false
        if (cross)
        {
            return false;
        }

        // Else (left turn) call testPoint (test the points thereafter)
        else
        {
            bool check = testPoint(app, points, test_pt, next_pt);
            if (!check)
            {
                cout << "Added to hull" << endl;
                app->add_to_hull(points[test_pt]);
                return true; // Now it can back track through the stack
            }
            // Else, we continue the loop
        }
    }
    return false;
}

/**
 * @brief: Implements Graham Scan Algorithm of the Convex Hull
 */
void DoGrahamScan(vector<Tuple*> points, ConvexHullApp *app)
{
    // Find Smallest Point
    int index_small = smallest_point(points);
    Tuple* smallest_pt = points[index_small];
    app->add_to_hull(smallest_pt);

    // Calculate Angles
    vector<double> angles = calculateAngles(points, index_small);

    // Sort Angles
    sort(points, angles, 0, (int) angles.size() - 1);
    cout << "Done" << endl;

    // Add the smallest angle to hull
    app->add_to_hull(points[points.size() - 1]);
    //printPointsAngles(points, angles);
    

    // Test Point for right turns
    // We use the program's stack as our stack
    // We add points to the stack as we test. If we confirm a point,
    // we add it to the hull.
    // This helper function is recursive.
    testPoint(app, points, index_small, 1);

    // Add the starting point to finish the loop
    app->add_to_hull(smallest_pt);
}
