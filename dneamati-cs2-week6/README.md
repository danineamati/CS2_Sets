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
together since this would be the greedy case. However, with n - 1 
philosophers, there will be one empty seat. Thus, all the seated philosophers
can acquire the fork on their left and exactly one seated philosopher can
acquire the fork on their right. This later philosopher can eat since he/she
has two forks. The philosopher eats, returns the forks, and stands up. This
leaves room for a new philosopher to eat. This the means that the philosophers
are not in deadlock if n - 1 philosophers are seated. Logically, the maximum
number of seated philosophers is n - 1. Any number less than or equal to 
n - 1 will work, but any number greater than n - 1 will not. In the case of
5 philosophers, 4 can be seated.

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

Thus, maximize the number of seated philosophers with n - 1. Maximize the
number of eating philosophers by seating the roof of half the philosophers.



(Chandy) Why will an asymmetric start state prevent deadlock?

We can see this clearly with contradiciton. Assume to the contrary that a
symmetric start is possible. In this implementation, every philosopher will
reach for his or her dirty LEFT fork. Since none of them have a RIGHT fork,
they will all request for a right fork. Since all of the forks are dirty,
the philosophers will clean his/her fork and hand it to his/her neighbor. Now
everyone has one clean fork that they do not want to release. This is a
deadlock. Therefore, a symmetric start is not possible and the state must
start asymmetrically.
