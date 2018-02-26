/**
 * @file test_solver.cpp
 * @author Ellen Price <<eprice@caltech.edu>>
 * @version 1.0
 * @date 2013-2014
 * @copyright see License section
 *
 * @brief Simple test suite for Solver.
 *
 * @section License
 * Copyright (c) 2013-2014 California Institute of Technology.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above
 *   copyright notice, this list of conditions and the following disclaimer
 *   in the documentation and/or other materials provided with the
 *   distribution.
 * * Neither the name of the  nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are those
 * of the authors and should not be interpreted as representing official policies,
 * either expressed or implied, of the California Institute of Technology.
 *
 */

#include "Solver.hpp"
#include <cstdio>
#include <iostream>

using namespace Solver;

double f0(double x)
{
	return x + 1;
}

double df0(double x)
{
	return 1;
}

double f1(double x)
{
	return pow(x, 3) + 5 * x + 10; 		
}

double df1(double x)
{
	return 3 * pow(x, 2) + 5;
}

double f2(double x)
{
	double numerator = (x + 12) * (x - 6) * x;
	double denominator = x + 10;
	return (numerator / denominator) - 4;
}

double df2(double x)
{
	return 2 * (pow(x, 3) + 18 * x * x + 60 *  x - 360) / (pow(x + 10, 2));
}

double f3(double x)
{
	return sin(20 * x) + 5 * x - 4.7;
}

double df3(double x)
{
	return 20 * cos(20 * x) + 5;
}

double f4(double x)
{
	return pow(x, 9) - pow(x, 8) + 2 + sin(50 * x);
}

double df4(double x)
{
	return 9 * pow(x, 8) - 8 * pow(x, 7) + 50 * cos(50 * x);
}


int main()
{
	std::cout << "TESTING BISECTION METHOD" << std::endl;
	std::cout << "--------------------------------------" << std::endl;
	// Test 0: Analytically solvable
	// x + 1
	std::cout << "Test 0" << std::endl;
	std::cout << "Should return -1. " << std::endl;
	std::cout << "Root at " << bisection(&f0, -5000, 5000) << std::endl;
	std::cout << std::endl;

	// Test 1: Analytically solvable
	// x^3 + 5x + 10
	std::cout << "Test 1" << std::endl;
	std::cout << "Should return -1.42332. " << std::endl;
	std::cout << "Root at " << bisection(&f1, -5000, 5000) << std::endl;
	std::cout << std::endl;

	// Test 2: Analytically solvable
	// [((x + 12) * (x - 6) * x) / (x + 10)] - 4
	std::cout << "Test 2" << std::endl;
	std::cout << "First root should return -12.0375 " << std::endl;
	std::cout << "Root at " << bisection(&f2, -11, -5000) << std::endl;
	std::cout << "Second root should return -0.507689 " << std::endl;
	std::cout << "Root at " << bisection(&f2, -9, 5) << std::endl;
	std::cout << "Third root should return 6.54523 " << std::endl;
	std::cout << "Root at " << bisection(&f2, 0, 5000) << std::endl;
	std::cout << std::endl;

	// Test 3: Numerically root finding needed
	// sin(20 x) + 5 x - 4.7
	std::cout << "Test 3" << std::endl;
	std::cout << "Should return 0.941982. " << std::endl;
	std::cout << "Root at " << bisection(&f3, -5000, 5000) << std::endl;
	std::cout << std::endl;

	// Test 4: Numerically root finding needed
	// x^9 - x^8 + 2 + sin(50 x)
	std::cout << "Test 4" << std::endl;
	std::cout << "Should return -1.00395. " << std::endl;
	std::cout << "Root at " << bisection(&f4, -5000, 5000) << std::endl;
	std::cout << std::endl;


	std::cout << "--------------------------------------" << std::endl;
	std::cout << "Newton-Raphson METHOD" << std::endl;
	std::cout << "--------------------------------------" << std::endl; 
	// Test 0: Analytically solvable
	// x + 1
	std::cout << "Test 0" << std::endl;
	std::cout << "Should return -1. " << std::endl;
	std::cout << "Root at " << newton_raphson(&f0, &df0, 0) << std::endl;
	std::cout << std::endl;

	// Test 1: Analytically solvable
	// x^3 + 5x + 10
	std::cout << "Test 1" << std::endl;
	std::cout << "Should return -1.42332. " << std::endl;
	std::cout << "Root at " << newton_raphson(&f1, &df1, 1) << std::endl;
	std::cout << std::endl;

	// Test 2: Analytically solvable
	// [((x + 12) * (x - 6) * x) / (x + 10)] - 4
	std::cout << "Test 2" << std::endl;
	std::cout << "First root should return -12.0375 " << std::endl;
	std::cout << "Root at " << newton_raphson(&f2, &df2, -11) << std::endl;
	std::cout << "Second root should return -0.507689 " << std::endl;
	std::cout << "Root at " << newton_raphson(&f2, &df2, 0) << std::endl;
	std::cout << "Third root should return 6.54523 " << std::endl;
	std::cout << "Root at " << newton_raphson(&f2, &df2, 30) << std::endl;
	std::cout << std::endl;

	// Test 3: Numerically root finding needed
	// sin(20 x) + 5 x - 4.7
	std::cout << "Test 3" << std::endl;
	std::cout << "Should return 0.941982. " << std::endl;
	std::cout << "Root at " << newton_raphson(&f3, &df3, -10) << std::endl;
	std::cout << std::endl;

	// Test 4: Numerically root finding needed
	// x^9 - x^8 + 2 + sin(50 x)
	std::cout << "Test 4" << std::endl;
	std::cout << "Should return -1.00395. " << std::endl;
	std::cout << "Root at " << newton_raphson(&f4, &df4, -1.5) << std::endl;
	std::cout << std::endl;
    return 0;
}
