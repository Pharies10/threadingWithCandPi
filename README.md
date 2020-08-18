# threading using C

This project uses multithreading in order to produce the mote carlo method to reproduce pi.

The basis is that the programs, pi1 and pi2, throw "darts" or generate random point between a square with sides of length/height of two and points at (1,1), (1,-1), (-1,-1), and (-1,1) with an origin of (0,0). From that origin a circle is inside the square with origin at (0,0) and radius of 1. 

The process to dertermine pi is used by the formula 4 * (number of darts that landed inside or on the circle / number of darts that are thrown).

The difference between pi1 and pi2 is that pi1 uses a mutex in order to record the hits/misses and pi2 uses two different arrays.

see HW7 PDF to see full description of project.
