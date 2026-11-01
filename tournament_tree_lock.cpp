
#include "tournament_tree_lock.h"

#include<limits> //used to check for integer overflow
#include<memory> //std::make_unique needed
#include <stdexcept> //exceptions for invalid inputs

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

TournamentTreeLock::TournamentTreeLock(int n) 
    : nThread(n), capacity(1)// initialize threads and leaf capacity
{
    //need at least two threads, error handling
    if (n<2){
        throw std::invalid_argument("n has to be greater or equal to 2");
    }

    //keep doubling the capacity until it can hold all n threads
    while(capacity < static_cast<std::size_t>(nThread))
    {

        //error handle, doubling shouldnt overflow
        if(capacity> std::numeric_limits<std::size_t>::max() /2){
            throw std::length_error("tournament tree is too large");
        }
        capacity *=2;//dobule the nubmer of leaf positions
    }

    //allocate peterson locks for the internal tree nodes
    //index 0 is unused, valid lock indexes are 1 to capcity -1
    nodes= std::make_unique<PetersonLock[]>(capacity);
}


//aquire the tournament tree lock for one thread
void TournamentTreeLock::acquire(int threadId) {
    
    //verify that threadID is valid
    if(threadId<0 ||threadId>= nThread){
        throw std::out_of_range("invalid thread ID");
    }

    //find this threads leaf positon in the tree
    std::size_t current= capacity +static_cast<std::size_t>(threadId);

    //travel upward from leaf towards the root
    while(current>1){
        //even idnex, left participant,0
        //odd index, right participant, 1
        int participant= static_cast<int>(current %2);

        current /=2; //move to parent node
        nodes[current].acquire(participant); //acquire the peterson lock at this parent
    }
    //thread now holds every single peterson lock on its path
}


//release the tournament tree lock for one thread
void TournamentTreeLock::release(int threadId) {
    //verify that threadID is valid
    if(threadId<0 ||threadId>= nThread){
        throw std::out_of_range("invalid thread ID");
    }

    std::size_t current=1; //start at root of tree
    std::size_t mask= capacity /2; //start with highest relevent bit of the threadID

    //travel down from root toward leaf
    while(mask>0){
        //determine whter thread belong to left or right of subtree at this level
        // 0 for left 1 for right
        int participant= (static_cast<std::size_t>(threadId) & mask) ?1 :0;

        nodes[current].release(participant); //release this nodes peterson lock
        current=current *2 +static_cast<std::size_t>(participant);
        mask/=2; //move to the next bit of threadID

    }
}
