Caltech CS2 Assignment 5: Graphs

See [assignment5.html](http://htmlpreview.github.io/?https://github.com/caltechcs2/graphs/blob/master/assignment5.html)

dfs:

The way the depth-first search is implemented, it gets stuck in infinite loop between points along an edge. Essentially it will visit a node, and then recursively call the dfs on the node from whence it came. 
