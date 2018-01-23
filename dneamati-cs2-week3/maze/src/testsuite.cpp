/**
 * @file testsuite.cpp
 * @author Ellen Price <<eprice@caltech.edu>>
 * @version 1.0
 * @date 2014-2015
 * @copyright see License section
 *
 * @brief Performs tests of the CoordinateQueue and CoordinateStack classes.
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

/**
 * Daniel Neamati
 */

#include <cstdio>
#include <iostream>
#include "CoordinateStack.hpp"
#include "CoordinateQueue.hpp"

bool testStack(CoordinateStack *stack)
{
    Coordinate c = Coordinate(0,0);
    stack->push(c);

    std::cout << "Peeking at Coordinate (0,0)." << std::endl;
    Coordinate topPeek = stack->peek();
    std::cout << "Peeked Value: ";
    std::cout << topPeek.x << " " << topPeek.y << std::endl;

    stack->push(Coordinate(1, 1));
    std::cout << "Peeking at Coordinate (1,1)." << std::endl;
    topPeek = stack->peek();
    std::cout << "Peeked Value: ";
    std::cout << topPeek.x << " " << topPeek.y << std::endl;

    std::cout << "Popping Coordinate (1,1)." << std::endl;
    Coordinate topPop = stack->pop();
    std::cout << "Popped Value: ";
    std::cout << topPop.x << " " << topPop.y << std::endl;

    for (int i = 0; i < 11; ++i)
    {
        stack->push(Coordinate(i, i + 4));
    }

    for (int i = 10; i >= 0; --i)
    {
        std::cout << "Peeking at Coordinate (" << i << ',' << i + 4 << ')';
        std::cout << std::endl;
        topPeek = stack->peek();
        std::cout << "Peeked Value: ";
        std::cout << topPeek.x << " " << topPeek.y << std::endl;

        std::cout << "Popping Coordinate (" << i << ',' << i + 4 << ')';
        std::cout << std::endl;
        topPop = stack->pop();
        std::cout << "Popped Value: ";
        std::cout << topPop.x << " " << topPop.y << std::endl;
    }

    std::cout << "Popping Coordinate (0,0)." << std::endl;
    topPop = stack->pop();
    std::cout << "Popped Value: ";
    std::cout << topPop.x << " " << topPop.y << std::endl;

    std::cout << "Attempt to Pop Last Coordinate (nullptr)";
    std::cout << std::endl;
    topPop = stack->pop();
    std::cout << "Popped Value: ";
    std::cout << topPop.x << " " << topPop.y << std::endl;

    return true;
}

bool testQueue(CoordinateQueue *queue)
{
    queue->enqueue(Coordinate(0,0));
    std::cout << "Peeking at Coordinate (0,0)." << std::endl;
    Coordinate frontPeek = queue->peek();
    std::cout << "Peeked Value: ";
    std::cout << frontPeek.x << " " << frontPeek.y << std::endl;

    std::cout << "Dequeuing Coordinate (0,0)." << std::endl;
    Coordinate frontPop = queue->dequeue();
    std::cout << "Dequeued Value: ";
    std::cout << frontPop.x << " " << frontPop.y << std::endl;

    queue->enqueue(Coordinate(1,1));
    std::cout << "Peeking at Coordinate (1,1)." << std::endl;
    frontPeek = queue->peek();
    std::cout << "Peeked Value: ";
    std::cout << frontPeek.x << " " << frontPeek.y << std::endl;

    std::cout << "Dequeuing Coordinate (1,1)." << std::endl;
    frontPop = queue->dequeue();
    std::cout << "Dequeued Value: ";
    std::cout << frontPop.x << " " << frontPop.y << std::endl;

    for (int i = 0; i < 11; ++i)
    {
        queue->enqueue(Coordinate(i, i + 4));
    }

    for (int i = 0; i < 11; ++i)
    {
        std::cout << "Peeking at Coordinate (" << i << ',' << i + 4 << ')';
        std::cout << std::endl;
        frontPeek = queue->peek();
        std::cout << "Peeked Value: ";
        std::cout << frontPeek.x << " " << frontPeek.y << std::endl;

        std::cout << "Dequeuing Coordinate (" << i << ',' << i + 4 << ')';
        std::cout << std::endl;
        frontPop = queue->dequeue();
        std::cout << "Dequeued Value: ";
        std::cout << frontPop.x << " " << frontPop.y << std::endl;
    }

    return true;
}


int main()
{
    
    CoordinateQueue *queue = new CoordinateQueue();
    CoordinateStack *stack = new CoordinateStack();

    if (testStack(stack) && testQueue(queue))
    {
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "All tests Passed" << std::endl;
        
    }

    delete queue;
    delete stack;

    return 0;
}
