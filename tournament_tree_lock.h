#pragma once

#include "peterson_lock.h"
#include <cstddef>
#include <memory>


/*
purpose: declares an n-thread mutual exclusion lock built using 
two participant peterson locks

used by
tournamnet_tree_lock.cpp
dining.cpp (course-grained solution)

n must be >=2
threadId must be between 0 and n-1
aquire() locks the path from leaf to root
release() unloskc the path from root ot leaf

*/
class TournamentTreeLock 
{
public:
    explicit TournamentTreeLock(int n); //constructor, creasts a Tournament Tree for n threads

    void acquire(int threadId); //aquire locsk from threads leaf toward root
    void release(int threadId); //release locks form root toward threads leaf

private:
    int nThread; //number of actual partiicpating threads
    std::size_t capacity; //number of leaf positions, rounded to power of 2

    //arry of peterson locsk used as internal tree nodes
    //index 0 is unused because th etree root is index 1
    std::unique_ptr<PetersonLock[]> nodes; 
};