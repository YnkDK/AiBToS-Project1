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
#include <fstream>
#include <iostream>
#include <algorithm>
#include <tuple>

#define inf 99999999
using namespace std;

class Days {
private:
    
    struct node{
        size_t minLabel;
        size_t maxLabel;
        size_t size;
        
        bool operator==(const node& rhs) const
        {
            return minLabel == rhs.minLabel && maxLabel == rhs.maxLabel;
        }
        
        bool operator<(const node& rhs) const
        {
            return minLabel < rhs.minLabel || (minLabel == rhs.minLabel && maxLabel < rhs.maxLabel);
        }

    };
    
    bool compare_entry( const node & e1, const node & e2) {
        if( e1.minLabel != e2.minLabel)
            return (e1.minLabel < e2.minLabel);
        return (e1.maxLabel < e2.maxLabel);
    }
    
    struct comp{
    
        bool operator()(const node &e1, const node &e2){
            if( e1.minLabel != e2.minLabel)
                return (e1.minLabel < e2.minLabel);
            return (e1.maxLabel < e2.maxLabel);
        }
   
    
    };
    
    std::vector<std::vector<size_t>> graph1,graph2;
    std::vector<node> graph1NodeInfo;
    std::vector<node> graph2NodeInfo;
    void readFile(const char *file, vector<vector<size_t>>& graph);
    size_t root;
    size_t numberOfLeaves;
    std::vector<size_t> dfsLabels;
    std::vector<bool> visited;
    node step2(size_t curNode);
    node step4(size_t curNode);
    size_t step2Counter;
    
public:
    ~Days() {
    }

    void initialize(const char *filename1, const char *filename2);
    size_t run();
};


#endif //AIBTOS_PROJECT1_DAYS_H
