Caltech CS2 Assignment 8: Numerics

See [assignment8.html](http://htmlpreview.github.io/?https://github.com/caltechcs2/numerics/blob/master/assignment8.html)


_______________________________________________________________________________

Part 0: Stable summation with the Kahan Algorithm

What is wrong with the naive summation?

The computer cannot easily keep track of such large (10^8) or such small
numbers (10^-8). The naive summation does the described multiplication by
adding small numbers (10^-8) a total of (10^8). In class we discussed that
since the running sum is much bigger than the next term, the computer has to
round (there are a lot of zeros in the mantissa). In adding 
1 + 10^-8 + 10^-8 + 10^-8 + ....
so many times, it simply rounds to 1. 


Advantages and Disadvantages of Pairwise Summation

A clear advantage is that it can use naive summation below a certain threshold
and still obtain the same answer. The pairwise summation also has fewer
total computations per element in the vector. A disadvantage is that it takes
up room on the stack since every division is a new function call. More
importantly, the user may set an incorrect cut-off. If the cut-off is too
large, the error will build up and cause an imprecise summation.

_______________________________________________________________________________

Part 1: Solving a physical system numerically (planetary orbits!)

Describe the three distinct end cases for the three methods.

The forward euler method is not very good. The orbit starts by looking fairly
elliptical, but the ellipse starts growing and changing. The planet quite
literally flys off the screen and the energy gets closer and closer to 0
(from -0.5) indicating a less bound orbit. Thus, the forward euler method is
not very accurate. (36 seconds to rise above -0.3)

The symplectic euler method is much better. The orbit maintains its elliptical 
properties for an extended period of time. After a solid 3 min and 30 seconds, 
the energy of the orbit is still roughly -0.5. The energy will occassionally 
dip below -0.5. 

Since the backward euler method is assumed to be circular, it is not as 
straight forward to compare the shape of this orbit to the previous orbits. 
None the less, we can again compare the energies. After 3 min and 30 seconds, 
the energy of the orbit is still roughly -0.5 - just like the symplectic euler 
method. However, while the symplectic euler method occassionally dips below 
-0.5, this is rarer in the backward euler method. More importantly, the error 
in the backward euler method is very very small, typically not exceeding 0.001.


Which one produces the most accuarate long-term behavior?

The backward euler method appears to produce the most accurate long-term
behavior. The symplectic method is the next best, though it still does a good
job. The forward euler method is by far the worst. 


_______________________________________________________________________________

Part 2: Discrete and Fast Fourier Transforms.

What should the Fourier Transform of a pure sine wave look like?

A pure sine wave has exactly one frequency. Thus the fourier transform should
only recognize this one frequency, all other terms should vanish.


How would the DFT of the same signal look if it was discrete?

The DFT would look different depending on the phase of the function at the end
of the data set with respect to the initial phase. As seen in class, if the
phase is off the date looks more like there is a peak. The top of the peak 
matches the frequency of the pure sine wave fairly well. However, there is a
residual decay on either side of the peak where the frequencies near the peak
are not zero. Note that the frequencies much higher or much lower than the 
expected frequencies are negligible.


What would you reasonably expect to happen as the function becomes more and
more complicated?

As the function becomes more and more complex, more frequencies are needed to
effectively describe the function. I would expect to observe more peaks.

***************************
Note on the spectral synthesizer.
Run as bin/fourier for mountains
Run as bin/fourier 1 for oceans

Thank you,
Daniel








