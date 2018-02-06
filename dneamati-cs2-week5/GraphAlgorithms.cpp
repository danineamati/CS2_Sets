/**
 * @file
 * @author The CS2 TA Team
 * @version 1.0
 * @date 2018
 * @copyright This code is in the public domain.
 *
 * @brief The MST and Shortest Path algorithms
 * (implementation).
 *
 */
#include "GraphAlgorithms.hpp"

/**
 * TO STUDENTS: In all of the following functions, feel free to change the
 * function arguments and/or write helper functions as you see fit. Remember to
 * add the function header to GraphAlgorithms.hpp if you write a helper
 * function!
 *
 */


Edge findSmallest(vector<Edge> &availEdge) {
    Edge closest = availEdge[0];
    double shortestDist = 100000000; // Abitrarily large as dummy value
    double dist;

    for (size_t i = 0; i < availEdge.size(); i++)
    {
        //cout << availEdge[i].id << ": ";
        dist = availEdge[i].weight;
        // cout << current->distance(*current->edges[i]) << endl;
        if (!availEdge[i].a->isVisited || !availEdge[i].b->isVisited) 
        {
            //cout << "Not visited" << endl;
            if (dist < shortestDist)
            {
                closest = availEdge[i];
                // cout << "Node A = " << availEdge[i].a->id << endl;
                shortestDist = dist;
            }
        }
        //cout << "Shortest Dist: " << shortestDist << endl;
    }
    //cout << "-------" << endl;
    // cout << "Node A = " << closest.a->id << endl;
    return closest;
}

/**
 * TODO: Implement Prim's Algorithm to build the MST.
 *
 * @brief Builds the MST of the given graph with Prim's algorithm
 *
 * @param g 	Graph object containing vector of nodes and edges
 * 				Definition for struct Graph in structs.hpp
 * @param app	Graphics application class
 * 				Class definition in GraphApp.hpp
 * 				You should not need to use this class other than passing app
 * 				as a parameter to drawEdge
 *
 * @attention 	Some hints for implementation and how to interact with our code
 * 				onMST and notOnMST are two vectors defined in
 *				GraphAlgorithms.hpp
 * 				that you can use to store which nodes are both in/not in the
 * 				MST. These are cleared at the start of the MST computation for 
 * 				you. To access the nodes that a specific node connects to
 *				you, you can use the vector<Node *> edges which is part
 *				of the Node struct in structs.hpp
 * 				You can compare two nodes to see if they are the same by
 * 				comparing the id attribute of a Node.
 *				You can calculate distance from one node to another by calling
 * 				the double distance(Node a) function of the Node struct.
 * 				Whenever you decide to add an edge between two nodes
 *				to the MST, you can use the provided drawEdge function
 *				in GraphAlgorithms.cpp
 *
 * You can assume that the graph is completely connected. Also, we only use
 * existing edges for the MST.
 *
 * Add your outline here
 *
 *
 */
void buildMSTPrim(Graph g, GraphApp *app) {
    onMST.erase(onMST.begin(), onMST.end());
    notOnMST.erase(notOnMST.begin(), notOnMST.end());

    // Set current to first point
    Node *current = g.nodes[0];
    Node *next;
    int count = 0;

    // Make vector of available edges and vector of visited nodes
    vector<Edge> availEdge;

    // We can loop through all of the nodes
    while (true)
    {
        // Set current as used up
        current->isVisited = true;

        // Loop through the connected nodes, and make edges to the nodes
        for (size_t i = 0; i < current->edges.size(); i ++)
        {
            // Consider each adjacent node
            next = current->edges[i];

            if (!next->isVisited) 
            {
                availEdge.push_back(Edge(count, current, current->edges[i],
                    current->distance(*current->edges[i])));
                count ++;
            }
        }

        // Choose the smallest edge.
        Edge shortest = findSmallest(availEdge);

        if (shortest.a->isVisited && shortest.b ->isVisited)
        {
            break;
        }

        drawEdge(shortest.a, shortest.b, g.edges, app, true);

        if (current->id == shortest.a->id)
        {
            current = shortest.b;
        }
        else
        {
            current = shortest.a;
        }
    }


/*
        // Loop through the remaining edges and check if any of the edges
        // contains the current node as a node.
        for (size_t i = 0; i < remaining.size(); i ++)
        {
            Edge *currentEdge = remaining[i];
            cout << "Edge: " << currentEdge->id << ", weight of " << currentEdge->weight;
            cout << " from node " << currentEdge->a->id << " to " << currentEdge->b->id << endl;

            // If we find a match, we add the edge
            if (currentEdge->a->id == current->id || currentEdge->b->id == current->id)
            {
                if (!isVisited(currentEdge->a->id, visited) || 
                    !isVisited(currentEdge->b->id, visited))
                {
                    cout << "Adding " << currentEdge->b->id << endl;
                    availEdge.push_back(currentEdge);
                    remaining.erase(remaining.begin() + i);
                }
            }
        }

        // While the available edge vector is not empty,

        // Find length of minimum edge weight
        Edge * closest = availEdge[0];
        size_t bestEdge = 0;

        for (size_t i = 0; i < availEdge.size(); i ++)
        {
            if (availEdge[i]->weight < closest->weight) 
            {
                closest = availEdge[i];
                bestEdge = i;
            }
        }

        cout << "closest edge is " << closest->id << ", weight of " << closest->weight;
        cout << " from node " << closest->a->id << " to " << closest->b->id << endl;

        if (closest->a->id == current->id) 
        {
            visited.push_back(closest->b->id);
            next = closest->b;
        }
        else 
        {
            visited.push_back(closest->a->id);
            next = closest->a;
        }

        drawEdge(current, next, g.edges, app, true);

        availEdge.erase(availEdge.begin() + bestEdge);

        current = next; */



    // Set node to current and add to visited

    // add all available edges

    // Set current to first point
    /*
    Node *current = g.nodes[0];
    Node *next;

    // Add current to vector of visited nodes and vector of path
    vector<int> visited;
    vector<Node *> path;

    visited.push_back(current->id);
    path.push_back(current);

    // While the graph has not been fully traversed:
    for (int i = 0; i < 10; i ++)
    {
        // Find closest node
        current = path.back();
        next = findClosestNode(current, visited);

        // If there are no nodes that are close, pop from path
        if (next == nullptr)
            path.pop_back();

        // draw Edge to closest node
        else {
            visited.push_back(next->id);

            // set that node as the current
            path.push_back(next);

            drawEdge(current, next, g.edges, app, true);

            cout << current << ' ' << next << endl;
        }
    }*/
}

/**
 * TODO: Implement Kruskal's Algorithm to build the MST.
 *
 * @brief Builds the MST of the given graph with Kruskal's algorithm
 *
 * @param g 	Graph object containing vector of nodes and edges
 * 				Definition for struct Graph in structs.hpp
 * @param app	Graphics application class
 * 				Class definition in GraphApp.hpp
 * 				You should not need to use this class other than
 *passing app
 * 				as a parameter to drawEdge
 *
 * @attention 	Some hints for implementation and how to interact with our code
 * 				You'll want to use a priority queue to determine which edges
 * 				to add first. We've created the priority queue for you
 * 				along with the compare function it uses. All you need to do
 * 				is call edge_queue.top(), edge_queue.pop(), edge_queue.push()
 * 				The data type that this priority queue stores, KruskalEdge 
 *              is defined in GraphAlgorithms.hpp and is an edge between
 *              any two trees. Each Node has a kruskal_edges attribute to store
 *              all the nodes it connects to in the MST. Make sure to use this
 *				to be able to join trees later!
 * 				To know which tree a node is in, use the which_tree attribute.
 * 				You can still use the edges, distance, and id
 *				attributes of a Node.
 * 				When connecting trees, you can call the
 *				kruskalFloodFill function
 * 				defined in structs.hpp on a node to convert it and its
 * 				MST connected nodes to a different tree number recursively.
 *				As in Prim's algorith, call drawEdge to add a connection between
 * 				two nodes to the MST
 *
 * You can assume that the graph is completely connected. Also, we only use
 * existing edges for the MST.
 *
 * Add your outline here
 *
 *
 */
void buildMSTKruskal(Graph g, GraphApp *app) {
    auto compare_func = [](KruskalEdge *a, KruskalEdge *b) {
        return (a->weight > b->weight);
    };
    std::priority_queue<KruskalEdge *, std::vector<KruskalEdge *>,
                        decltype(compare_func)>
        edge_queue(compare_func);

    // Write code here
}

/**
 * TODO: Implement Djikstra's shortest path algorithm.
 *
 * @brief Find the shortest path between start and end nodes with Djikstra's
 * 		  shortest path algorithm
 *
 * @param start	Index of start node of path to find
 * 				Can access the Node * element by using
 *				g.nodes[start]
 * @param end	Index of end node of path to find
 * 				Can access the Node * element by using g.nodes[end]
 * @param g 	Graph object containing vector of nodes and edges
 * 				Definition for struct Graph in structs.hpp
 * @param app	Graphics application class
 * 				Class definition in GraphApp.hpp
 * 				You should not need to use this class other than passing app
 * 				as a parameter to drawEdge
 *
 * @attention 	Some hints for implementation and how to interact with our code
 * 				You can use the distance_to_start attribute of the Node struct
 * 				in structs.hpp to keep track of what the distance from each
 * 				Node to the start node during computation
 * 				You can use the previous attribute of the Node struct
 *				in structs.hpp to keep track of the path you are taking to
 *				later backtrack.
 *				To access the nodes that a specific node connects to you, you
 * 				can use the vector<Node *> edges which is part of the Node struct
 * 				in structs.hpp
 *				Whenever you decide to add an edge between two nodes
 *				to the MST, you can use the provided drawEdge function in
 *				GraphAlgorithms.cpp
 *
 * Add your outline here
 *
 *
 */
void findShortestPath(int start, int end, Graph g, GraphApp *app) {
    // Write code here
}

/**
 * @brief Adds an edge to either the MST or the shortest path based on the
 * 			nodes to connect given. This is done by iterating through the edges
 * 			to find the correct edge given the nodes.
 *
 * @param pt1	One side of edge to draw
 * @param pt2	Other side of edge to draw
 * @param edges	Vector of edges in the graph
 * @param app	Graphics application class
 * @param mst	True if we are adding edge to MST, False if we are adding edge
 * 				to shortest path
 **/

void drawEdge(Node *pt1, Node *pt2, vector<Edge *> edges, GraphApp *app,
              bool mst) {
    for (unsigned int i = 0; i < edges.size(); i++) {
        if ((edges[i]->a == pt1 && edges[i]->b == pt2) ||
            (edges[i]->a == pt2 && edges[i]->b == pt1)) {
            if (mst)
                app->add_to_mst(edges[i]);
            else
                app->add_to_path(edges[i]);
            break;
        }
    }
    return;
}
