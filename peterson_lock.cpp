
#include "peterson_lock.h" // petersonlcok class definition

/*
implements the two-participant Peterson lock.
  Used by-
  TournamentTreeLock
  Dining Philosophers fine-grained solution
 
  The shared variables are declared in peterson_lock.h.
 
  Restrictions:
  Use std::atomic for shared Peterson state.
  Do not use std::mutex or ready-made lock primitives.
 */

//implement and initialize Peterson's atomic state.

PetersonLock::PetersonLock() = default; //constructor, atomic member is alr initialized in the header

// implement Peterson's entry protocol.
void PetersonLock::acquire(int participant) 
{
    int other = 1-participant; //determine the other participant
    interest[participant].store(true); //announce this participant wants lock/ critical seciton

    turn.store(other); //give other participant priorty if they both compete

    //wiat while the other partcipant want shte lock
    //then turn currently favors the other participant
    while(interest[other].load() && turn.load() == other){
        //busy waiting, keep checking until entry is ready
    }
}

//release the lock for participant 0 or 1
void PetersonLock::release(int participant) 
{
    interest[participant].store(false); //announce this particment doesnt want lock
}
