Caltech CS2 Assignment 6: Multithreading and Concurrency

See [assignment6.html](http://htmlpreview.github.io/?https://github.com/caltechcs2/concurrency/blob/master/assignment6.html)

Why does the greedy solution deadlock?

Each philosopher has his/her own thread. The first line that the must run
in the greedy solution is phil->pickup_fork(LEFT). Thus, all of the 
philosophers will pick up the fork to their left and the fork will lock.
Then all the philosophers try to pick up their right fork. But since their
right fork is used by the philosopher to their right, the right fork is
unavailable. Thus, the philosophers will inifitely wait for their neighboring
philosopher to release their fork, but this will never happen. Thus, the 
solution is in deadlock.
