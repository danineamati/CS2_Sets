/**
 * @file qfsolve.cpp
 * @author Daniel Neamati
 * @date 6 Jan. 2018
 *
 * @brief Solver of quadratic equations.
 */

#include <iostream>
#include <cmath>

using namespace std;

/**
 * @brief Solves the given quadratic equation.
 *
 * This function, given real coefficients A, B, C to the equation
 * A*x*x + B*x + C = 0, returns the real part of a solution to the
 * equation thus defined. Where two real solutions exist, the one
 * closer to positive infinity is chosen.
 *
 * @param a the quadratic coefficient.
 * @param b the linear coefficient.
 * @param c the constant coefficient.
 *
 * @return the real part of a solution to the defined quadratic equation,
 *         as described.
 */
 double qfsolve(double a, double b, double c) 
 {
 	double discriminant = (b * b) - (4 * a * c);

 	if (discriminant >= 0) {
 		// + rather than - will ensure the more positive solution
 		// unless a is negative
 		if (a >= 0)
 			return (-b + sqrt(discriminant)) / (2 * a);
 		else
 			return (-b - sqrt(discriminant)) / (2 * a);
 	}
 	else {
 		// The discriminant is negative 
 		// so sqrt(discriminant) will be purely imaginary
 		return (-b) / (2 * a);
 	}
 }


/*
 * @ brief Runs the quadratic function through 6 tests.
 *
 */

 int main()
 {
 	// Test 1: Should return -5
 	cout << "The most positive root of x^2 + 10 x + 25 is "; 
 	cout << qfsolve(1, 10, 25) << endl;
 	// Test 2: Should return 5
 	cout << "The most positive root of x^2 - 10 x + 25 is ";
 	cout << qfsolve(1, -10, 25) << endl;
 	// Test 3: Should return 4
 	cout << "The most positive root of 0.25 x^2 - 0.25 x - 3 is ";
 	cout << qfsolve(0.25, -0.25, -3) << endl;
 	// Test 4: Should return 0.5
 	cout << "The most positive root of 0.25 x^2 - 0.25 x + 1 is ";
 	cout << qfsolve(0.25, -0.25, 1) << endl;
 	// Test 5: Should return 0.926....
 	cout << "The most positive root of -5 x^2 - 4 x + 8 is ";
 	cout << qfsolve(-5, -4, 8) << endl;
 	// Test 6: Should return -2
 	cout << "The most positive root of - x^2 -4 x - 6.5 is ";
 	cout << qfsolve(-1, -4, -6.5) << endl;
 	return 0;
 }