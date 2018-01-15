/**
 * @file
 * @author The CS2 TA Team
 * @version 1.0
 * @date 2013-2014
 * @copyright This code is in the public domain.
 *
 * @brief The gift wrapping and Graham scan convex hull algorithms
 * (header file).
 *
 */

#include <vector>
#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include "ConvexHullApp.hpp"
#include "structs.hpp"

using namespace std;


void printPoints(vector<Tuple*> points);
int smallest_point(vector<Tuple*> points);
bool crossproduct(Tuple *pt_known, Tuple *pt_next, Tuple *pt_checking);
void DoGiftWrap(vector<Tuple*> points, ConvexHullApp *app);

void sort(vector<Tuple*> &points, vector<double> &angles, int left, int right);
int smallest_angle(vector<Tuple*> points, int prev_pt, double prev_angle);
void DoGrahamScan(vector<Tuple*> points, ConvexHullApp *app);
