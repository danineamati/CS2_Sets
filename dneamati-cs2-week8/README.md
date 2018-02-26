Caltech CS2 Assignment 8: Numerics

See [assignment8.html](http://htmlpreview.github.io/?https://github.com/caltechcs2/numerics/blob/master/assignment8.html)


Part 0: Stable summation with the Kahan Algorithm

What is wrong with the naive summation?

The computer cannot easily keep track of such large (10^8) or such small
numbers (10^-8). The naive summation does the described multiplication by
adding small numbers (10^-8) a total of (10^8). But in adding 
1 + 10^-8 + 10^-8 + 10^-8 + ....
so many times, it simply rounds to 1.




Part 1: Solving a physical system numerically (planetary orbits!)
