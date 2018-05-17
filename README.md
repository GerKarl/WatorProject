# Wator Simulation 4th Yr Project

### Project Overview
Joint Project for 4th Year Distributed and Concurrent Devices, Software Development IT Carlow. 

This project is a Wa-tor simulation https://en.wikipedia.org/wiki/Wa-Tor. 

The initial goal is to produce a sequential implementation of the well known Wa-tor world
simulation.

The 2nd problem will be to implement OpenMP to speed up the processing by utilizing threads.

Benchmarking will also take place to indicate the speed increase/decrease when manipulating thread count with OpenMP.

Finally, the code will be profiled using gprof profiler. 
This will give an indication into where the processor is spending the 
most amount of time, thus leading to code refactoring.

### Design

For the design & implementation of this project, the world is monitored using two 3D arrays. The two arrays are called ocean and oceanCopy. ocean is used by sfml to displat the current locations of the Wa-tor denizens. The oceanCopy array is used to store the moves for each iteration before displaying. When each iteration is complete, the oceanCopy is transferred to ocean.
The three layers can be described as follows:
          ocean[][][0] is used to store the ascii representation of the denizen (0 for shark, . for fish).
          ocean[][][1] is used to store the breed times.
          ocean[][][2] is used to store the starve time for the shark.
The same description can be applied to ocean copy.

### Tools & Environment

Code written in C++.

Emacs environment was used for production.

g++ compiler used with sfml libraries and flags.

Documents produced utilizing Doxygen.

#### Hardware

MacBook Pro(Retina, 15-inch, Early 2013) (Ubuntu 14.04 booted from USB)

Processor: 2.4 Ghz Intel Core i7

Memory: 8GB 1600 MHz DDR3

Quad Core

### How to run & dependencies

This project requires that the sfml libraries are installed on the machine and that the sfml environment is setup.

Assuming that your environment is setup correctly, the project can be run by using the following command in a bash terminal:
         
         make SFML
         
         ./watorMainSFML

Documentation for the project can be produced using Doxegen as follows(assumes existing installation of Doxygen):
          
          make doc $L = "Whatever you want to call the project" $B = "Brief for your project"
          
The make doc command requires that a template Doxyfile exists on the root directory of your machine, the Doxyfile parameters for project name and project brief will be overwritten by $L and $B.

### Benchmarking for sequential implementation

The purpose of the benchmarking is to compare the speed of the each iteration against different grid sizes. The grid sizes used are 20 x 20, 40 x 40, 80 x 80, 160 x 160, 320 x 320. Data is collected for 10,000 iterations for each grid size. This produced the following data:

![alt text](https://raw.githubusercontent.com/GerKarl/WatorProject/master/RawData.png)

A visual representation:

![alt text](https://raw.githubusercontent.com/GerKarl/WatorProject/master/SeqGraph2.png)

### Benchmarking for concurrent implementation

This part of the project would not work for us. We spent 8 hours trying to get it to work. The Virtual Machine gave errors involving OpenGL and would not run the SFML window.
To get around this we used the MacOS which ran it no problem, however openMP would not work on the MacOs.

We then tried booting ubuntu from a USB which worked fine, we installed SFML dependencies and were able to run the Wa-tor simulation with a single thread using:
                    #pragma omp parallel for num_threads(1)
This was put above our for loops and nested for loops and ran fine (with #include <omp.h>)

The problem occurred when we increased the number of threads to any value above one. We kept getting floating point exceptions and could not figure out why. 

Like I said, we spent about 8 hours trying to resolve this, alas, to no avail.

### Aha!! We Found The Problem

While giving it one last shot an error message pointed us to the problem and we were able to fix it. 

We tested our concurrency speed using 10,000 iterations. This was placed in a strategic place to give us the most potential speed increase. Essentially we broke our threads up on one nested for loop, however this for loop calls every other method(almost). Here are our results:

Visual display with max, min, average time for each of the 10,000 iterations.

![alt text](https://raw.githubusercontent.com/GerKarl/WatorProject/master/ConcurrencyBenchmark.png)

The exponential line(dotted orange) looks fairly flat and it is not obvious as to the speed up. We are dealing with milliseconds here so we made an additional graph to simply show the average:

![alt text](https://raw.githubusercontent.com/GerKarl/WatorProject/master/ConcurrencyAverage.png)

It can be ascertained from the average graph that the running of openmp with one thread produces a similar result to the sequential implementation, while not exactly the same at 0.007282804 sequential vs 0.0079545, they are close enough. It could be said that perhaps the overhead of creating a thread with openmp caused this overhead.

There is a clear speed displayed on the average graph, whereby it would appear that 3 threads/6 threads seems to be the optimum. Could this be because of our implementation of a 3 dimensional array? Maybe. The overhead of creating more threads becomes apparent after the 6th thread, but it is interesting to note that this is a quad core implementation, or rather was implemented on a quad core machine. You would think that moving past the 4th thread would create more overhead, but even up to the 10th thread there is a definite increase in efficiency compared to the sequential implementation.... curious.

