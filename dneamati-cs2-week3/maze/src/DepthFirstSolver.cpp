/**
 * @file DepthFirstSolver.cpp
 * @author Ellen Price <<eprice@caltech.edu>>
 * @version 2.0
 * @date 2014-2015
 * @copyright see License section
 *
 * @brief Functions for maze solver that implements depth-first search.
 *
 * @section License
 * Copyright (c) 2014-2015 California Institute of Technology.
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

#include "DepthFirstSolver.hpp"

/**
 * @brief Initializes the solver.
 *
 * @param[in] app Pointer to the main MazeSolverApp class.
 */
DepthFirstSolver::DepthFirstSolver(class MazeSolverApp *app)
{
    stack = new CoordinateStack(app);
    init();
}

/**
 * @brief Initializes the solver (student-implemented).
 */
void DepthFirstSolver::init()
{
    for (int i = 0; i < WIDTH; i++)
    {
        for (int j = 0; j < HEIGHT; j++)
        {
            // Set every cell to not visited
            visited[i][j] = false;
        }
    }
}

/**
 * @brief Deinitializes the solver.
 */
DepthFirstSolver::~DepthFirstSolver()
{
    delete stack;
    deinit();
}


/**
 * @brief Deinitializes the solver (student-implemented).
 */
void DepthFirstSolver::deinit()
{
    for (int i = WIDTH - 1; i = 0; i--)
    {
        delete[] visited[i];
    }
}

/**
 * @brief Solves the maze given by `maze`.
 *
 * @param[in] maze MazeGrid object that stores the maze to be
 * solved.
 */
void DepthFirstSolver::solve(MazeGrid *maze)
{
    // Push the start onto the stack
    stack->push(Coordinate(MAZE_START_X, MAZE_START_Y));
    

    while(!stack->is_empty())
    {
        Coordinate current = stack->peek();

        // Mark the current coordinate as Visited
        visited[current.x][current.y] = true;

        if (current.x == MAZE_END_X && current.y == MAZE_END_Y)
        {
            // Solve has reached the end!
            break;
        }

        else
        {
            int potential = maze->get_possible_moves(current.x, current.y);

            // Start with East since the general direction of the end
            // is southeast.

            // Check that East is an option and the cell is not visited
            if (potential & E && !visited[current.x + 1][current.y]) 
            {
                /* We can move east from current.x to current.x + 1. */
                stack->push(Coordinate(current.x + 1, current.y));
            }

            // If not, check South
            else if (potential & S && !visited[current.x][current.y + 1]) 
            {
                /* We can move east from current.y to current.y + 1. */
                stack->push(Coordinate(current.x, current.y + 1));
            }

            // If not, check West
            else if (potential & W && !visited[current.x - 1][current.y]) 
            {
                /* We can move east from current.x to current.x - 1. */
                stack->push(Coordinate(current.x - 1, current.y));
            }

            // If not, check North
            else if (potential & N && !visited[current.x][current.y - 1])
            {
                /* We can move east from current.y to current.y - 1. */
                stack->push(Coordinate(current.x, current.y - 1));
            }

            // If NO OPTIONS remain
            else
            {
                stack->pop();
            }
        }
    }
}

/**
 * @brief Retrieves the current path through the maze.
 *
 * @return Vector storing the current path through the maze.
 */
vector<Coordinate> DepthFirstSolver::get_path()
{
    return stack->fullstack();
}

