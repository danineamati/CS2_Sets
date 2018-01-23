Caltech CS2 Assignment 3: Data Structures

See [assignment3.html](http://htmlpreview.github.io/?https://github.com/caltechcs2/maze/blob/master/assignment3.html)


Question 1.5 Analysis

Conditions in which BFS vs DFS may be faster.

The conditions are dependent on whether a tree is "bushy" or "deep".
This is to say: Consider two trees, one tree has depth significantly greater
than the other. We designate this tree as the "deep" tree. Now consider a
different tree that has the same number of nodes as the deep tree, but has a
far smaller depth.

Assume that the node we are searching for is deep enough in the deep tree. If we
now implement a breadth-first search, there is no probabilty of reaching the
target node until we reach that level of the tree. This means that for a deep
tree, we have to search a lot of nodes before we can possibly reach the node.
Contrastly, a depth-first search has the potential of reaching the node every
time that it reaches that level.
Evidently, in the worst case scenario, both BFS and DFS will have the same
time complexity (for a deep enough target node such as a leaf). However, in 
the average case, DFS will find a node faster than BFS in a deep tree.

Now assume we that we have a node that is not very deep in a bushy tree. On a
given path, the depth-first search may miss the target node level entirely and
have to backtrack to the root repeatedly. However, the breath-first search will
look at the entire level. So, for a shallow node, the breath-first search will
(on average) find the node more quickly.



Real-life Stack

News feed.
When you load a news feed, it shows the most recent news article/post/etc first. 
This news article/post/etc is the last element added to the "news stack." 
After an item is viewed, it notes that you have viewed the item (essentially
popping the item from your screen) and displays the next item. 


Real-life Queue

Amazon and online shopping. 
Say you have a sale on an online website. The first person to click the "Buy" button
must be the first person to acquire the purchase. This is to say the data structure
is "First in, first out" - a queue. This is particularly noticable in the limiting
case that a supply is in short stock. In this case the last person to "Buy" the item
may not get the item since he or she is at the end of the queue.


