/* debugging example */

#include <iostream>
#include <vector>

class Node
{
    int value;
    bool visited;
    std::vector<Node*> edges;
public:
    // insert constructors, destructors,
    Node(int val) {
        value = val;
        visited = false;
    }

    ~Node() {}
    // accessors, and mutators here
    bool dfs(int to_find);
    int getValue();
    void addEdge(Node *A);
    void printEdge();
    void setVisited(bool visit);
};

// true indicates that the value was found, and false indicates that the value was not found.
bool Node::dfs(int to_find)
{
    visited = true;
    if(this->value == to_find)
    {
        return true;
    }
    std::vector<Node*>::iterator i;
    // std::cout << edges.size() << std::endl;
    for(i = this->edges.begin(); i != this->edges.end(); i++)
    {
        Node * n = *i;
        // We can proceed only if a node has not already been visited.
        if (!n->visited)
        {
            bool r = n->dfs(to_find);
            if(r)
            {
                return r;
            }
        }
    }
    return false;
}

// Returns the node's value
int Node::getValue()
{
    return value;
}

// Adds edge to node
void Node::addEdge(Node *A)
{
    edges.push_back(A);
}

// Print nodes in Edge
void Node::printEdge()
{
    for (size_t i = 0; i < edges.size(); i++)
        std::cout << edges[i]->getValue() << ' ';
    std::cout << std::endl;
}

void Node::setVisited(bool visit)
{
    visited = visit;
}


int main(void)
{
    srand(time(nullptr));

    // Make tree
    int arr[8] = {7, 4, 15, 5, 8, 12, 1, 6};
    std::vector<Node *> tree;
    tree.push_back(new Node(9));

    // Add all nodes to tree
    for (int i = 0; i < 8; i ++)
    {
        std::vector<Node *> edges;
        tree.push_back(new Node(arr[i]));
    }

    // Make random edges
    for (int i = 0; i < 9; i ++) {
        int num;
        do {
            num = rand() % 9;
        } while (num == i);

        tree[i]->addEdge(tree[num]);
        tree[num]->addEdge(tree[i]);
    }

    // Visualize the tree
    for (int i = 0; i < 9; i ++)
    {
        std::cout << tree[i]->getValue() << " has an edge to ";
        tree[i]->printEdge();
    }

    std::cout << "----------" << std::endl;

    std::cout << "3 is not in the graph, it should not find the node: ";
    if (tree[0]->dfs(3))
        std::cout << "Found!" << std::endl;
    else
        std::cout << "Not Found" << std::endl;

    for (int i = 0; i < 9; i ++)
    {
        tree[i]->setVisited(false);
    }

    std::cout << "8 is in the graph. Now it should find the node: ";
    if (tree[0]->dfs(8))
        std::cout << "Found!" << std::endl;
    else
        std::cout << "Not Found" << std::endl;

    while (!tree.empty()) {
        delete tree[0];
        tree.erase(tree.begin());
    }
    

    return 0;

}