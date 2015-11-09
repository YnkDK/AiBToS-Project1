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

int main(int argc, char** argv) {
    Days days = Days();

    days.initialize(argv[1], argv[2]);
    // TODO: Use parameters to determine what the algorithm should output etc
    cout << days.run() << endl;
}