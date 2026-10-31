
#include "tournament_tree_lock.h"

/*
implements an n-thread Tournament-Tree lock

using PetersonLock objects as internal nodes.

Used by-
dining.cpp through TournamentTreeLock's interface

Requirements-
 Support all n >= 2.
 Support non-power-of-two n.
 Acquire locks leaf to root.
 Release locks root to leaf.
 */

TournamentTreeLock::TournamentTreeLock(int n) {
    (void)n;

    /*
    Validate or establish the thread count.
    Determine tree capacity.
    Allocate Peterson nodes.
    Establish the leaf mapping.
     */
}

void TournamentTreeLock::acquire(int threadId) {
    (void)threadId;

    /*
    Locate the requesting thread's leaf.
     Determine its path toward the root.
     Determine its local Peterson participant
     identity at each node.
     Acquire each path lock, bottom to top.
     */
}

void TournamentTreeLock::release(int threadId) {
    (void)threadId;

    /*
     Locate the corresponding lock path.
     Release locks in reverse acquisition order.
     Return after the full path is released.
     */
}
