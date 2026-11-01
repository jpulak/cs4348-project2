
#include "dining.h"
#include "peterson_lock.h"
#include "tournament_tree_lock.h"

#include <thread>
#include <vector>
#include <random>
#include <chrono>
#include <cstdio>
#include <iostream>
#include <exception>
#include <atomic>

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
    // create a TournamentTreeLock for n philosophers
    TournamentTreeLock lock(n);
    // create a vector to hold the philosopher threads
    std::vector<std::thread> philosophers;
    // reserve space for n philosopher threads
    philosophers.reserve(n);

    //checks for errors within threads
    std::exception_ptr threadError = nullptr;
    //keep track of whether any thread has thrown an exception
    std::atomic<bool> errorOccurred(false);

    for(int i = 0; i < n; ++i) {
        try{
            philosophers.emplace_back([&, i](){
                //track wether thread owns a lock that needs to be relased in case of an exception
                bool ownsLock = false;
                //variable used to check if an exception has already been recorded in another thread
                bool expected = false;

                try{
                    //random number genrator for delays
                    std::mt19937 generator(std::random_device{}());
                    std::uniform_int_distribution<int> delay(1, 500);

                    //each philosopher thinks and eatsfive times
                    for(int j=0; j < 5; ++j) {
                            
                        std::printf("COARSE %d %d THINK_START\n", i, j);

                        std::this_thread::sleep_for(
                            std::chrono::milliseconds(delay(generator))
                        );

                        std::printf("COARSE %d %d THINK_END\n", i, j);

                        //acquire the lock before eating
                        lock.acquire(i);
                        ownsLock = true;

                        std::printf("COARSE %d %d EAT_START\n", i, j);

                        std::this_thread::sleep_for(
                            std::chrono::milliseconds(delay(generator))
                        );
                        
                        std::printf("COARSE %d %d EAT_END\n", i, j);

                        //relrease the lock after eating
                        lock.release(i);
                        ownsLock = false;
                    }
                } catch(...) {
                    // if an exception occurs, record it and release the lock if held
                    std::exception_ptr currentError = std::current_exception();

                    if(ownsLock) {
                        try{
                            lock.release(i);
                            ownsLock = false;
                        } catch(...) {
                            // releasing the lock fails, go to the original exception
                        }
                    }

                    // record the first exception that occurs across all threads
                    if(errorOccurred.compare_exchange_strong(expected, true)){
                        threadError = currentError;
                    }
                }
            });
        } catch(...) {
            // if thread creation fails, join all previously created threads and rethrow the exception
            std::cerr << "Error creating philosopher thread " << i << "\n";

            for(std::thread& t : philosophers) {
                if(t.joinable()){
                    t.join();
                }
            }

            throw;
        }
    }

    // join all philosopher threads before returning
    for(std::thread& t : philosophers) {
        if(t.joinable()){
            t.join();
        }
    }

    // if any thread threw an exception, rethrow it in the main thread
    if(errorOccurred.load() && threadError) {
        std::rethrow_exception(threadError);
    }
    
}

// Implement the fine-grained simulation.
void runFine(int n) {
   // create an array of PetersonLocks for the chopsticks
    std::unique_ptr<PetersonLock[]> chopsticks =
        std::make_unique<PetersonLock[]>(n);

    // create a vector to hold the philosopher threads
    std::vector<std::thread> philosophers;
    // reserve space for n philosopher threads
    philosophers.reserve(n);

    //checks for errors within threads
    std::exception_ptr threadError = nullptr;
    //keep track of if any thread has thrown an exception
    std::atomic<bool> errorOccurred(false);

    for(int i = 0; i < n; ++i) {
        try{
            philosophers.emplace_back([&, i](){
                // track whether the thread owns any of the chopstick locks, and release them in the case of an exception
                bool ownsFirst = false;
                bool ownsSecond = false;
                bool expected = false;

                // determine the left and right chopstick indices for the philosopher
                int right = i;
                int left = (i - 1 + n) % n;

                // determine the order of acquiring locks to avoid deadlock in acending order
                int first = std::min(left, right);
                int second = std::max(left, right);

                // determine the participant index for each chopstick lock based on the where the philosopher is sitting
                int firstParticipant = (i == first) ? 0 : 1;
                int secondParticipant = (i == second) ? 0 : 1;

                try{
                    // create random number generator for delays
                    std::mt19937 generator(std::random_device{}());
                    std::uniform_int_distribution<int> delay(1, 500);

                    // each philosopher thinks and eats five times
                    for(int j=0; j < 5; ++j) {
                            
                        std::printf("FINE %d %d THINK_START\n", i, j);

                        std::this_thread::sleep_for(
                            std::chrono::milliseconds(delay(generator))
                        );

                        std::printf("FINE %d %d THINK_END\n", i, j);

                        // acquire the chopstick locks in the determined order to avoid deadlock
                        chopsticks[first].acquire(firstParticipant);
                        ownsFirst = true;

                        chopsticks[second].acquire(secondParticipant);
                        ownsSecond = true;

                        std::printf("FINE %d %d EAT_START\n", i, j);

                        std::this_thread::sleep_for(
                            std::chrono::milliseconds(delay(generator))
                        );
                        std::printf("FINE %d %d EAT_END\n", i, j);

                        // release the chopstick locks in the reverse order of acquisition
                        chopsticks[second].release(secondParticipant);
                        ownsSecond = false;

                        chopsticks[first].release(firstParticipant);
                        ownsFirst = false;

                    }
                } catch(...) {
                    // if an exception occurs, record it and release any locks held by the thread in order
                    std::exception_ptr currentError = std::current_exception();
                    if(ownsSecond) {
                        try{
                            chopsticks[second].release(secondParticipant);
                            ownsSecond = false;
                        } catch(...) {
                            // releasing the lock fails, go to the original exception
                        }
                    }
                    if(ownsFirst) {
                        try{
                            chopsticks[first].release(firstParticipant);
                            ownsFirst = false;
                        } catch(...) {
                            // releasing the lock fails, go to the original exception
                        }
                    }

                    // record the first exception that occurs across all threads
                    if(errorOccurred.compare_exchange_strong(expected, true)){
                        threadError = currentError;
                    }
                }
            });
        } catch(...) {
            // if thread creation fails, join all previously created threads and rethrow the exception
            std::cerr << "Error creating philosopher thread " << i << "\n";
            for(std::thread& t : philosophers) {
                if(t.joinable()){
                    t.join();
                }
            }
            throw;
        }
    }

    // join all philosopher threads before returning
    for(std::thread& t : philosophers) {
        if(t.joinable()){
            t.join();
        }
    }

    // if any thread threw an exception, rethrow it in the main thread
    if(errorOccurred.load() && threadError) {
        std::rethrow_exception(threadError);
    }
}
