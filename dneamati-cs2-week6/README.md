Caltech CS2 Assignment 6: Multithreading and Concurrency

See [assignment6.html](http://htmlpreview.github.io/?https://github.com/caltechcs2/concurrency/blob/master/assignment6.html)

Why does the greedy solution deadlock?

Each philosopher has his/her own thread. The first line that they must run
in the greedy solution is phil->pickup_fork(LEFT). Thus, all of the 
philosophers will pick up the fork to their left and the fork will lock.
Then, all the philosophers try to pick up their right fork. But since their
right fork is used by the philosopher to their right, the right fork is
unavailable. Thus, the philosophers will inifitely wait for their neighboring
philosopher to release their fork, but this will never happen. Thus, the 
solution is in deadlock.



(Waiter) How many philosophers can sit at a table?

Consider n philosophers. Then, n - 1 philosophers can sit at a table at
any given time. It is clear that n philosopher cannot sit at a table
together since this would be the gready case. However, with n - 1 
philosophers, there will be one empty seat. Thus, all the seated philosophers
can acquire the fork on their left and exactly one seated philosopher can
acquire the fork on their right. This later philosopher can eat since he/she
has two forks. The philosopher eats, returns the forks, and stands up. This
leaves room for a new philosopher to eat. This the means that the philosophers
are not in deadlock if 4 philosophers are seated.

This is different from how many philosophers can be eating. For n
philosophers, the maximum number that can be eating is the floor of (n / 2).
This is an immediate result of each philospher needing 2 forks to eat. 
For one philosoher to eat, he/she has to deprive his/her neighbor from the
ability to eat. 

In the current case of 5 philosophers, only 2 philosophers can eat at a given
time. Namely, choose a philosopher. The philosopher to the left and right can
no longer eat. Thus, the philosopher two seats away can eat. But as a result,
the last philosopher cannot eat. Thus, only two philosophers can eat at a
given time.



(Chandy) Why will an asymmetric start state prevent deadlock?
