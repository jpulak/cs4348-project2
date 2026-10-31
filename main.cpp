
#include "dining.h"

#include <iostream>
#include <string>
#include <exception>

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
    // Check the number of command-line arguments.

    // Convert argv[1] to an integer.

    // Reject non-integers, n < 2, and invalid values.

    // Call runCoarse(n) and runFine(n) in order.

    //Required order once validation is complete:

    //BEGIN COARSE
    //runCoarse(n)
    //END COARSE

    //BEGIN FINE
    //runFine(n)
    //END FINE

    (void)argc;
    (void)argv;

    std::cerr << "Project implementation not complete.\n";

    return 1;
}
