
#include "dining.h"
#include "peterson_lock.h"
#include "tournament_tree_lock.h"

#include <thread>
#include <vector>
#include <random>
#include <chrono>
#include <cstdio>

/*
implements the two Dining Philosophers simulations.

Called by:
main.cpp

Uses:
etersonLock (fine-grained chopstick locking)
TournamentTreeLock (coarse-grained global locking)

Requirements:
n philosopher threads per simulation
five cycles per philosopher
random 1-500 ms thinking/eating delays
exact required output format
safe thread creation and joining
deadlock-free fine-grained solution

implement the simulations independently using
the public lock interfaces provided in the headers.
*/

//implement the coarse-grained simulation.
void runCoarse(int n) {
    (void)n;

    /*
    Use one TournamentTreeLock for all chopsticks.
    every philosopher must:
     think
     acquire the global lock
     simulate eating
     release the global lock
     Repeat five times and join all threads.
     */
}

// Implement the fine-grained simulation.
void runFine(int n) {
    (void)n;

    /*
    use one PetersonLock per chopstick.
    chopstick i is between philosophers
    i and (i + 1) % n.
    
    Philosopher i requires:
    chopstick i
    chopstick (i - 1 + n) % n
    
    Prevent deadlock using consistent
    chopstick acquisition ordering.

    Repeat five times per philosopher.
    Join all threads before returning.
     */
}
