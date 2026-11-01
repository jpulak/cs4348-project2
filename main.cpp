
#include "dining.h"

#include <iostream> //std::cout and cerr
#include <string>// std:;string and stoll
#include <stdexcept> //exception class
#include <limits>//numeric limits for int
#include<exception>//std::exception

/*
program entry point and execution coordinator.

Uses:
dining.h
runCoarse(int n)
runFine(int n)

Responsibilities:
Validate command-line arguments.
Reject invalid values of n.
Run coarse solution first.
wait for coarse completion.
Run fine solution second.
Report unrecoverable errors to stderr.
Return nonzero on failure.
 
 Standard output must contain ONLY required
 project event records and BEGIN/END markers.
 */

int main(int argc, char* argv[]) 
{
    //recive on argument, n, argc include executable name so 2
    if (argc!=2){
        std::cerr <<"error, format argument as ./my-dining n(n>=2)\n";
        return 1;//program failed
    }

    int n;//storesvalidaded nubmer of philosphers

    try{
        //stor arg as string for validaiton
        std::string input = argv[1];

        //reject empty arg
        if(input.empty()){
            throw std::invalid_argument ("n can't be empty");
        }

        //reject any chars other than decimal digits
        for (char c:input){
            if(c<'0'|| c>'9'){
                throw std::invalid_argument("n has to be an integer");
            }
        }

        long long value= std::stoll(input); //convert validated string to wide int type

        //need at least two philosophers
        if(value<2){
            throw std::invalid_argument("n has to be at least 2");
        }

        //number fit in the int parameter type
        if(value >std::numeric_limits<int>::max()){
            throw std::out_of_range("n is too big");
        }

        n= static_cast<int>(value); //convert after validating

        std::cout<<"BEGIN COARSE\n"; //begin course grained solution
        runCoarse(n); //returns after joining all course threads
        std::cout <<"END COARSE\n"; //mark completion of course grained solution

        std::cout<<"BEGIN FINE\n";//beign fine grained solution
        runFine(n); // return after joining all fine threads
        std::cout<<"END FINE\n"; //complete of fine grained solution
    }

    catch(const std::exception& error) {
        //handle conversion, allocaiton, perrors 
        std::cerr<<"Error message: "<< error.what() <<"\n";

        return 1; //failed
    }
}

