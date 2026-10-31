#pragma once

/* 
declare the two dining philosphers simulations

used by-
main.cpp ,calling these functions
dining.cpp, implements these functions


Both of the simulations have to create n philospher threads
exectue five thinking/easting cycle per philosopher
and then join all threads before returning

any eroors reprot back to main
after safely managing all created threads

*/


//run dining philosphers using one tournament tree-lock
void runCoarse(int n);

//run dining philosophers using individual peterson locks for each chopstick
void runFine(int n);