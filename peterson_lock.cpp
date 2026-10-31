
#include "peterson_lock.h"

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

PetersonLock::PetersonLock() {

}

// implement Peterson's entry protocol.
void PetersonLock::acquire(int participant) {
    (void)participant;

    /*
      Steps to implement:
      Express this participant's intention to enter.
      Set the contention tie-breaker correctly.
      Wait while the other participant has priority.
      Return once exclusive access is guaranteed.
     */
}

//implement Peterson's release protocol.
void PetersonLock::release(int participant) {
    (void)participant;

    /*
      Update the appropriate shared atomic state
      to announce that this participant has left
      the critical section.
     */
}
