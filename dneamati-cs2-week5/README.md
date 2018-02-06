Caltech CS2 Assignment 5: Graphs

See [assignment5.html](http://htmlpreview.github.io/?https://github.com/caltechcs2/graphs/blob/master/assignment5.html)


Daniel Neamati

dfs:

The way the depth-first search is implemented, it gets stuck in infinite loop
between points along an edge. Essentially it will visit a node, and then
recursively call the dfs on the node from whence it came. 

We can fix this by allowing the nodes to keep track of their visited state.
In my implementation, I added a boolean to the Node class that is true if the
node has been visited and false if the node has not been visited.


Prim Algorithm Pseudocode;

General idea: loop through graph and add the smallest of available edges

1) Initialize a list of available edges. These will be the edges that
   connect a node to another node.
   For the first iteration, the first node is the zeroth node.
   From here, we add the edges that connect the zeroth node to its
   adjacent nodes.
2) Now we need set the current node as visited
   and loop through all of the current node's adjacent nodes.
   If the end node of the edge is not on the MST (not visited), 
   we add the edge.
3) In the looping, we need to find which is the next smallest available
   edge. Then draw that edge and add the end node to the MST.
4) Lastly, we change the current node the the end node of the edge we just
   displayed.


Kruskal's Algortihm Psuedocode;

General idea: Make trees of two nodes, then combine the trees at the smallest
	edge distance to creat one tree. Stop when the tree spans the graph.

1) Initialize the first tree with the smallest edge.
2) Find the next smallest edge and make a tree
3) Continue looping. If an edge combines two trees, update the tree id
   to the smaller id and consider the tree as a new tree.
   It is very imporant that edges containing both endpoints on a single tree
   are NOT considered! This would create a cycle.
