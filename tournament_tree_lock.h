#pragma once

#include "peterson_lock.h"

/*
purpose: declares an n-thread mutual exclusion lock built using 
two participant peterson locks

used by
tournamnet_tree_lock.cpp
dining.cpp (course-grained solution)

-n must be >=2
threadId must be between 0 and n-1
aquire() locks the path from leaf to root
release() unloskc the path from root ot leaf

*/
class TournamentTreeLock 
{
public:
    explicit TournamentTreeLock(int n);

    //threadId is in the range 0 through n-1.
    void acquire(int threadId);
    void release(int threadId);

private:
    /*
    declare the interal tree representation

    consider
    number of participating thread
    leaf capacity
    colleciton of peterson nodes
    mapping form thread IDs to leaf positions

    the strcutures must support n values that are not powers of two

    remember atomic consiting petersonLock objects should not be assumed ot be copyable
    */
};