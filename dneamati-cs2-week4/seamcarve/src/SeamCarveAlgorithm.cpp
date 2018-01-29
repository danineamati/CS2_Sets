/*
 * SeamCarveAlgorithm.cpp
 * Defines the seam carving algorithm.
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
 *
 */

#include "SeamCarveApp.hpp"

#define min(x, y)           ((x) < (y) ? (x) : (y))


/**
 * @brief Fills the cost table with values from the saliency map. Note that
 *        this occues in place.
 */
void fillCostTable(unsigned int **costTable, unsigned **smap, int w, int h)
{
	// We can easily fill the first row since it stays the same
    for (int j = 0; j < w; j ++)
    	costTable[j][0] = smap[j][0];

    unsigned int minNeighbor;

    // Now we need to fill the cost table one row at a time (from left to
    // right).
    for (int j = 1; j < h; j++)
    {
    	for (int i = 0; i < w; i++)
    	{
    		// We have three cases:
    		// The pixel is at the left edge.
    		if (i == 0)
    		{
    			//std::cout << "Left ";
    			minNeighbor = min(costTable[i][j - 1], 
    				costTable[i + 1][j - 1]);
    			//std::cout << "Min:" << minNeighbor << " Current: " << costTable[i][j];
    			costTable[i][j] = smap[i][j] + minNeighbor;
    			//std::cout << " Now: " << costTable[i][j] << std::endl;
    		}

    		// The pixel is at the right edge.
    		else if (i == w - 1)
    		{
    			//std::cout << "Right ";
    			minNeighbor = min(costTable[i - 1][j - 1],
    				costTable[i][j - 1]);
    			//std::cout << "Min:" << minNeighbor << std::endl;
    			costTable[i][j] = smap[i][j] + minNeighbor;
    		}

    		// The pixel is somewhere in the middle of the picture.
    		else
    		{
    			//std::cout << "Middle ";
    			minNeighbor = min(
    				min(costTable[i - 1][j - 1], costTable[i][j - 1]),
    				min(costTable[i][j - 1], costTable[i + 1][j - 1])
    				);
    			//std::cout << "Min:" << minNeighbor << std::endl;
    			costTable[i][j] = smap[i][j] + minNeighbor;
    		}
    	}
    }
}

/**
 * @brief Finds the best seam by choosing the best value from the bottom row
 *        and bactracks through the cost table to find the corresponding seam.
 *
 * @return Nothing. Modifies seam in place.
 */
void mapSeam(unsigned int *seam, unsigned int **costTable, int w, int h)
{
	// First finds the lowest value
	int bestCol = 0;
	unsigned int lowest = costTable[bestCol][h - 1];

	for (int i = 0; i < w; i++)
	{
		if (costTable[i][h - 1] < lowest)
		{
			bestCol = i;
			lowest = costTable[i][h - 1];
		}
	}

	//std::cout << "lowest: " << lowest << std::endl;

	seam[h - 1] = bestCol;

	for (int j = h - 2; j >= 0; j--)
    {
    	// We have three cases:
		// The pixel is at the left edge.
		if (bestCol == 0)
		{
	    	int col2 = costTable[bestCol][j - 1];
			int col3 = costTable[bestCol + 1][j - 1];
			if (col3 < col2)
				bestCol ++;
		}

		// The pixel is at the right edge.
		else if (bestCol == w - 1)
		{
	    	int col1 = costTable[bestCol - 1][j - 1];
    		int col2 = costTable[bestCol][j - 1];
			if (col1 < col2)
				bestCol--;
		}

		// The pixel is somewhere in the middle of the picture.
		else
		{
			int col1 = costTable[bestCol - 1][j - 1];
    		int col2 = costTable[bestCol][j - 1];
			int col3 = costTable[bestCol + 1][j - 1];
			int best = min(min(col1, col2), min(col2, col3));

			if (best == col1)
				bestCol--;
			else if (best == col3)
				bestCol++;
    	}

    	seam[j] = bestCol;
    }
}

/**
 * @brief Peforms the seam carving algorithm.
 *
 * @param smap 2-d saliency map with width `w` and height `h`; can be
 * indexed by `smap[i][j]` where 'i' is the column and 'j' is the row.
 *
 * @param w Width of the saliency map
 *
 * @param h Height of the saliency map
 *
 * @return An array of the x-coordinates of the seam, starting from the top of
 * the image.
 */
unsigned int *DoSeamCarve(unsigned int **smap, int w, int h)
{
	// We first need to allocate the memory for the cost table
	// Note that the cost table will be the same dimensions as the
	// photo a saliency maps.
    unsigned int **costTable = new unsigned int*[w];
    for (int i = 0; i < w; i ++)
    	costTable[i] = new unsigned int[h];

    fillCostTable(costTable, smap, w, h);

    // This is the array corresponding to the x-coordinates of the seam.
    unsigned int *seam = new unsigned int[h]; 

    /*std::cout << "First Row" << std::endl;
    for (int i = 0; i < w; i++)
    {
    	std::cout << costTable[i][0] << ' ';
    } 
    std::cout << std::endl << "Next Row" << std::endl;
    for (int i = 0; i < w; i++)
    {
    	std::cout << costTable[i][1] << ' ';
    }
    std::cout << std::endl; */
    /*std::cout << std::endl << "Last Row" << std::endl;
    for (int i = 0; i < w; i++)
    {
    	std::cout << costTable[i][h - 1] << ' ';
    }
    std::cout << std::endl;*/

    mapSeam(seam, costTable, w, h);

    /* A very bad seam carving algorithm... 
    for (int i = 0; i < h; i++)
    {
        seam[i] = 0;
    }*/


    // Before we return the best seam, we need to delete the cost table
    // to prevent a memory leak.
    for (int i = 0; i < w; i ++)
    	delete[] costTable[i]; // Here we delete every colums
    delete[] costTable; // Now we delete the overall array itself

    return seam;
}

