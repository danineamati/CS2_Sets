/**
 * @file
 * @author The CS2 TA Team
 * @version 1.0
 * @date 2013-2014
 * @copyright This code is in the public domain.
 *
 * @brief Example of a linked list class and usage.
 *
 */

#include "linked_list.hpp"
#include <iostream>
#include <vector>

/**
 * List constructor.
 */
List::List()
{
    head = nullptr;
    num_elements = 0;
}

/**
 * List destructor.
 */
List::~List()
{
    Node *current_node = head;
    if (detectLoop())
    {
        while (current_node->next != nullptr) 
        {
            Node *next_node = current_node->next;
            delete current_node;
            current_node = next_node;
        }
        delete current_node;
    }
    else
    {
        std::vector<Node*> checked; // A vector of visted addresses
        Node *current = head;
        Node *prev;
        bool end_loop = false;

        while (!end_loop)
        {
            for (int i = 0; i < (int) checked.size(); i++)
                {
                    if (current == checked[i])
                    {
                        end_loop = true;
                        for (int j = 0; j < (int) checked.size(); j++)
                        {
                            checked.pop_back();
                        }
                        break;
                    }
                }

            if (!end_loop)
            {
                // If the address is unique, add it to checked
                checked.push_back(current);

                // Move to next node and delete current
                prev = current;
                current = current->next;
                delete prev;
            }
        }
    }
}

/**
 * insert   Insert an integer at the end of the list.
 * @param   item integer to be inserted at the end of the list
 */
void List::insert(int item)
{
    // If we have elements...
    if (num_elements > 0)
    {
        // Set up a pointer to get to end of current list
        Node *temp = head;
        for (int i = 0; i < num_elements - 1; ++i)
        {
            temp = temp->next;
        }
        // temp now points to node at end of list

        // Construct our new node, it doesn't point to anything yet
        Node *new_node = new Node(item, nullptr);

        // Make the old tail point to the new tail
        temp->next = new_node;

        // and update the number of elements in the list
        num_elements++;
    }
    else
    {
        head = new Node(item, nullptr);
        num_elements++;
    }
    return;
}

/**
 * insert   Insert an integer at the end of the list that points to previous element.
 * @param   item integer to be inserted at the end of the list
 */
Node* List::badInsert(int item)
{
    // If we have elements...
    if (num_elements > 0)
    {
        // Set up a pointer to get to end of current list
        Node *temp = head;
        Node *after = temp->next; // Points to second element
        for (int i = 0; i < num_elements - 1; ++i)
        {
            temp = temp->next;
        }
        // temp now points to node at end of list

        // Construct our new node, it doesn't point to anything yet
        Node *new_node = new Node(item, nullptr);

        // Make the old tail point to the new tail
        temp->next = new_node;

        // Set new tail to previous element
        new_node->next = after;

        // and update the number of elements in the list
        num_elements++;

        // Make new tail
        Node *last_node = new Node(item + 1, nullptr);
        return last_node;
    }
    else
    {
        head = new Node(item, nullptr);
        num_elements++;
        return head;
    }
    
}

/**
 * printList    Prints the contents of our list out, one integer per line.
 */
void List::printList()
{
    Node *temp = head;
    while (temp != nullptr)
    {
        std::cout << temp->data << std::endl;
        temp = temp->next;
    }
    return;
}

/*
 * @brief: detects a loop in a singlely linked list
 * @return: true if no loops are detected. false if a loop
 *          is detected.
 */
bool List::detectLoop()
{
    std::vector<Node*> checked; // A vector of visted addresses
    Node *current = head;

    while (current != nullptr)
    {
        for (int i = 0; i < (int) checked.size(); i++)
        {
            if (current == checked[i])
                return false;
        }
        // If the address is unique, add it to checked
        checked.push_back(current);

        // Move to the next node
        current = current->next; 
    }
    // Otherwise, we safely say that there are no loops
    return true;
}

