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

void printPointsAngles(vector<Tuple*> points, vector<double> angles);
//void sort(vector<Tuple*> &points, vector<double> &angles, int left, int right);
vector<double> mergeSort(vector<Tuple*> &points, vector<double> &angles);
vector<double> merge(vector<double> &left, vector<double> &right);

vector<double> calculateAngles(vector<Tuple*> &points, int smallest_pt);
bool testPoint(ConvexHullApp *app, vector<Tuple*> &points, int hull_pt, int test_pt);
void DoGrahamScan(vector<Tuple*> points, ConvexHullApp *app);
