/**
 * @file
 * @author The CS2 TA Team
 * @version 1.0
 * @date 2013-2014
 * @copyright This code is in the public domain.
 *
 * @brief Student implementation of line algorithm (header file).
 *
 */

/*
 * Daniel Neamati
 */

#ifndef __LINE_ALGORITHM_H__
#define __LINE_ALGORITHM_H__

#include <vector>
#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include "LineApp.hpp"
#include "structs.hpp"

using namespace std;

double calculateError(double slope, Tuple &p2, Tuple &ptest);
// Student implemented line algorithm
vector<Tuple> line(Tuple p1, Tuple p2);

#endif
