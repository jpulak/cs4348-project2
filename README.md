# CS/SE 4348 Project 2 

## Team Information

Team Number: 21

Member 1: Jana Pulak
Member 2: Cristina Lu


## Project Overview

This project implements Dining Philosophers problem in C++17 using
two synchromization approaches

1. A coarse-grained Tournament-Tree lock
one tournament tree lock protects all chopsticks

2. Fine-grained Peterson locks for individual chopsticks.
each chopstick has its own two participant peterson lock

Both of these solutions use our Peterson lock implementaion with std::atomic
without built in mutexes or semaphores

## Compilation
compile program 
```make```
produces the excutable my-dining

to remove executable
``` make clean ```

## Execution
./my-dining n
n must be an integer greater than or equal to 2.

The program runes the course grained solution first, and then fine grained solution
Each philosopher completes five thinking/eating cycles,
using new ranomd delays between 1 and 500 milliseconds for each thinking and eating operation

## Peterson Lock
Our peterson lock provides mutual exclusion between exactly two participants
- 0
- 1

It uses two atomic interest flags and an atomic turn variable
- aquire() announces interest and waits if the other participant has priority
- release() clears the current participants interest flag

The atomic vairable uses the defualt sequentially consistant memory ordering

## Tournament-Tree Lock
Our tournament-tree lock combines multiple Peterson locks to provide mutual exclusion for n threads

representthe tree as an arry with root at index 1

The nubmer of leaves i rounded up to the next power of 2, Thread is assigned to leaf capacity +i

When n is not a power of two, extra leaf positions remain unused

Threads acquire peterson locks form theri leaves toward the root and releases them in reverse order, form root toward leaf.

At each node, the leaf subtree uses Peterson participant 0, right subtree uses participant 1


## Course Grained Solution
Our Tournament tree lock protects access to all chopsticks
A philospher must acquire the global lock before eating and release it after eating
This makes sure there ismutal exclusion, only one philosopher cna eat a time

## Fine grained solution and deadlock prevention
Each chopstick is protected by a seperate Peterson lock
Chopstick i is shared by philosopher i and (i+1) %n.
Philospher i requires chopsticks i and (i-1+n) %n

To prevent deadlock, philosopher acquire the lower numbered nrequired chopstick befroe the higher nubmered one
So there is a consistnat globabl order for acquiring resoruces, prevent circular wait
Each philosopher releases both chopsticks locks after eating,
So it allows non neighboring philosophers to eat simultaneously while preventing neighboring philosophers from doing so. 


## Assumptions

## Limitations