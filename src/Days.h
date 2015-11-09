/* -------------------------------------------------------------------------------------
** This software is implemented as part of the course
**     Algorithms in Bioinformatics - Trees and Structures Q2/2015
** at Aarhus Univerity Denmark.
**
** Days.h
** Defines the algorithm developed by Day as described in lecture 1 slide 23-27
**
** Author: Martin Storgaard, Konstantinos Mampentzidis and Henrik McQuoid Jespersen
** -----------------------------------------------------------------------------------*/
#ifndef AIBTOS_PROJECT1_DAYS_H
#define AIBTOS_PROJECT1_DAYS_H


#include <cstddef>
#include <vector>

class Days {
private:
    std::vector<std::vector<size_t>> graph;
public:
    ~Days() {
        delete[] graph;
    }

    void initialize(const char *filename);
    size_t run();
};


#endif //AIBTOS_PROJECT1_DAYS_H
