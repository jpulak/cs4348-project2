#pragma once

#include <atomic>

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
    //aquaire eclusive access fo rparticipant 0 or 1
    void acquire(int participant);

    //release exclusive access fo rsam eparitcipant
    void release(int participant);

private:
    /*
    declare the atomic state requred by ptersons two thread algorithm
    desing represent
    wehter particpant 0 wantsthe lock
    whtheter participatnt 1 wants the lock
    which particpant has priority during contention

    all shared peterson state must use std::atomic
    
    */
};