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

// Daniel Neamati


#include "GraphAlgorithms.hpp"


/**
 * @brief Searches the list of available edges and returns the edge with
 *        the smallest distance.
 */

Edge findSmallest(vector<Edge> &availEdge) {
    Edge closest = availEdge[0];
    double shortestDist = 100000000; // Abitrarily large as dummy value
    double dist;

    for (size_t i = 0; i < availEdge.size(); i++)
    {
        dist = availEdge[i].weight;
        if (!availEdge[i].a->isVisited || !availEdge[i].b->isVisited) 
        {
            if (dist < shortestDist)
            {
                closest = availEdge[i];
                shortestDist = dist;
            }
        }
    }
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
 * General idea: loop through graph and add the smallest of available edges
 *
 * 1) Initialize a list of available edges. These will be the edges that
 *    connect a node to another node.
 *    For the first iteration, the first node is the zeroth node.
 *    From here, we add the edges that connect the zeroth node to its
 *    adjacent nodes.
 * 2) Now we need set the current node as visited
 *    and loop through all of the current node's adjacent nodes.
 *    If the end node is not on the MST (not visited), we add the edge.
 * 3) In the looping, we need to find which is the next smallest available
 *    edge. Then draw that edge and add the end node to the MST.
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
 * General idea: Make trees of two nodes, then combine the trees at the smallest
 *        edge distance to creat one tree. Stop when the tree spans the graph.
 *
 * 1) Initialize the first tree with the smallest edge.
 * 2) Find the next smallest edge and make a tree
 * 3) Continue looping. If an edge combines two trees, update the tree id
 *    to the smaller id and consider the tree as a new tree.
 *    It is very imporant that edges containing both endpoints on a single tree
 *    are NOT considered! This would create a cycle.
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
 * @ brief Searches the possibile nodes and finds the one that is
 *         closest to the starting node.
 */
Node findClosestNode(vector<Node *> &path) {
    Node closest = *path[0];
    double shortestDist = 10000000;

    for (size_t i = 0; i < path.size(); i++)
    {
        if (path[i]->distance_to_start < shortestDist) 
        {
            closest = *path[i];
            shortestDist = closest.distance_to_start;
        }
    }

    return closest;
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
 * 1) Set start distance to 0 and everything else arbitrarly large.
 * 2) Look at each neighbor of the current node (starting at the start)
 *    and determine which path has the smallest distance.
 * 3) Go to that node and update all of the neighbors to the new lowest
 *    path.
 * 4) We repeat the process of search, recalculate, and move until we
 *    arrive at the destination.
 */
void findShortestPath(int start, int end, Graph g, GraphApp *app) {
    vector<Node *> path;

    // Iterate through all of the nodes to set everything except the starting
    // node to infinity.
    // This is the initialization step.
    for (size_t i = 0; i < g.nodes.size(); i ++)
    {
        if ((int) i != start) 
        {
            g.nodes[i]->distance_to_start = 1000000000;
            g.nodes[i]->previous = nullptr;
        }
        else
        {
            g.nodes[start]->distance_to_start = 0;
            g.nodes[start]->previous = nullptr;
        }
        path.push_back(g.nodes[i]);
    }

    // Now we try to find the path
    while (!path.empty())
    {
        // We first need to find the closest node
        Node closest = findClosestNode(path);

        // Mark it as used up by removing it from the path
        for (size_t i = 0; i < path.size(); i++)
        {
            if (path[i]->id == closest.id)
            {
                path.erase(path.begin() + i);
                break;
            }
        }

        // Now we want to add adjust the min distance to the start
        // of all of the neighbors of the closest node
        for (size_t i = 0; i < closest.edges.size(); i ++)
        {
            double dist = closest.distance_to_start + 
                            closest.edges[i]->distance(closest);

            // If the new distance is smaller than the current
            if (dist < closest.edges[i]->distance_to_start)
            {
                closest.edges[i]->distance_to_start = dist;
                closest.edges[i]->previous = g.nodes[closest.id];
            }
        }

        // When we reach the end, we can stop the loop
        if (closest.id == end)
        {
            cout << "destination found!" << endl;
            break;
        }
    }

    // Now we need to traceback in order to display the path.
    Node * current = g.nodes[end];
    cout << "Path found in length of " << current->distance_to_start << endl;
    while (current->previous->id != start) 
    {
        drawEdge(current, current->previous, g.edges, app, false);
        current = current->previous;
    }

    drawEdge(current, g.nodes[start], g.edges, app, false);

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
