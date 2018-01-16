#include <iostream>

/*
 * Daniel Neamati
 * detectLoop function is at the end of linked_list.cpp
 * To run warmup, compile the linked_list.cpp file in this directory
 * with warmup.
 * 
 * Time complexity: Output dependent. If the loop is at the start (best case),
 * 			the algorithm is O(2) (second element loops to first). If the loop
 *			is at the end (worst case), the algorithm checks every address
 *			before it. Thus, O(n^2).
 *
 * Space complexity: Worst case it has to store the whole linked list. Thus,
 *			the algorithm is O(n).
 */

#include "linked_list.hpp"


int main(int argc, char const *argv[])
{
    List lst;
    for (int i = 0; i < 10; ++i)
    {
        lst.insert(i);
    }

    bool check = lst.detectLoop();
    if (check == true)
    	std::cout << "No loop detected." << std::endl;
    else
    	std::cout << "Loop detected." << std::endl;

    List bad_lst;
    for (int i = 0; i < 10; ++i)
    {
        bad_lst.insert(i);
    }
    // Otherwise the unlinked node is lost in memory
    Node* last_node = bad_lst.badInsert(10); 

    check = bad_lst.detectLoop();
    if (check == true)
    	std::cout << "No loop detected." << std::endl;
    else
    	std::cout << "Loop detected." << std::endl;

    delete last_node; // Prevent memory leak!

    return 0;
}