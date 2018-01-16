/**
 * @file
 * @author The CS2 TA Team
 * @version 1.0
 * @date 2013-2014
 * @copyright This code is in the public domain.
 *
 * @brief Student implementation of line algorithm.
 *
 */

/*
 * Daniel Neamati
 */


#include "LineAlgorithm.hpp"

/**
 * @brief: Calculates the difference between a suggested point
 *         and the line
 * @return: The error value
 */
double calculateError(double slope, Tuple &p1, Tuple &ptest)
{
	// y = mx + b = mx + (y1 - mx1)
	// b = (y1 - mx1)
	double trueVal = slope * ptest.x + (p1.y - slope * p1.x);

	return trueVal - ptest.y;
}



/**
 * @brief: Implements line algorithm similar to Bresenham's line.
 * @return: A vector of adjacent points in the line
 */
vector<Tuple> line(Tuple p1, Tuple p2)
{
    vector<Tuple> v;


    // Takes care of verical edge case (slope undefined)
    if (p1.x == p2.x)
    {
    	Tuple lowest_p = p1;

	    if (p1.y > p2.y)
	    {
	    	lowest_p = p2;
	    }

	    Tuple new_pt(lowest_p.x, lowest_p.y);

    	for (int i = 1; i < abs(p2.y - p1.y); ++i)
    	{
    		new_pt.y++;
    		v.push_back(new_pt);
    	}

    	return v;
    }

    // slope formula
    double slope = (p2.y - p1.y) / ((double) p2.x - (double) p1.x);

    Tuple lowest_p = p1;
    Tuple highest_p = p2;

    if (p1.x > p2.x)
    {
    	lowest_p = p2;
    	highest_p = p1;
    }

    double error = calculateError(slope, p1, p1);

    Tuple new_pt(lowest_p.x, lowest_p.y);

    while (abs(new_pt.x - highest_p.x) > 1 || abs(new_pt.y - highest_p.y) > 1 )
	{
		error += calculateError(slope, lowest_p, new_pt);

		// According to Bresenham, |0.5| is the cut-off
		while (error > 0.5)
		{
			new_pt.y++;
			v.push_back(new_pt);
			error --;
		}

		while (error < -0.5)
		{
			new_pt.y--;
			v.push_back(new_pt);
			error ++;
		}

	    v.push_back(new_pt);

	    new_pt.x++;	
    }

    return v;
}
