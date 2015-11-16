/* -------------------------------------------------------------------------------------
** This software is implemented as part of the course
**     Algorithms in Bioinformatics - Trees and Structures Q2/2015
** at Aarhus Univerity Denmark.
**
** main.cpp
** TODO: Describe usage
**
** Author: Martin Storgaard, Konstantinos Mampentzidis and Henrik McQuoid Jespersen
** -----------------------------------------------------------------------------------*/

#include "Days.h"
#include <time.h>

#define PERFORMANCE
int main(int argc, char** argv) {
    Days days = Days();

    days.initialize(argv[1], argv[2]);
    // TODO: Use parameters to determine what the algorithm should output etc
#if PERFORMANCE 0
    cout << days.run();
#else
    clock_t start, stop;
    size_t distance;
    start = clock();
    distance = days.run();
    stop = clock();
    cout << (double) (stop - start) / CLOCKS_PER_SEC << " " << distance;

#endif
}