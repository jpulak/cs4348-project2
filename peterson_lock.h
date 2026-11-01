#pragma once

#include <atomic> //std::atomic

/*
declare two participant Peterson mutal excluson lock

use by-
peterson_lock.cpp
tournament_tree_lock.h/.cpp
dining.cpp (fine grained solution)

particiment must be 0 or 1
partcipent arguemtn is local lock idneity
so nto the philosophers global id
*/

class PetersonLock 
{
public:

    PetersonLock(); //constrctor initialize lock when its unlocked state

    void acquire(int participant); //request lock for participant 0 or participant 1
    
     
    void release(int participant); //release lock held by specified participant
private:
    //each participant has a flag that indicicates if they want the lock
    //interest[0] belong to participant 0
    //interest[1] belong to particpant 1
    std::atomic<bool> interest[2]{{false},{false}};

    //resoleve the ocmpeition if both particpant request lock
    //intiially set to 0, both interested flags begin as false
    std::atomic<int> turn{0};
};