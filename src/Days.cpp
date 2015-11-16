/* -------------------------------------------------------------------------------------
** This software is implemented as part of the course
**     Algorithms in Bioinformatics - Trees and Structures Q2/2015
** at Aarhus Univerity Denmark.
**
** Days.cpp
** Implementation of the algorithm developed by Day as described in lecture 1 slide 23-27
**
** Author: Martin Storgaard, Konstantinos Mampentzidis and Henrik McQuoid Jespersen
** -----------------------------------------------------------------------------------*/
#include "Days.h"

/**
 * Reads the given input file and constructs the graph given as parameter. The file have to be on the following format:
 * n
 * 1 parent
 * 1 parent
 * 1 parent
 * ...
 * |adj| adj
 * |adj| adj
 * ...
 *
 * for example
 * 5
 * 1 2              4
 * 1 2             / \
 * 1 4            2   3
 * 3 0 1 4       / \
 * 2 2 3        0   1
 */
void Days::readFile(const char* file, vector<vector<size_t>> &graph) {
    ifstream fin;
    size_t size, i, j;
    bool expectInternalNode = false;

    fin.open(file,ios_base::in);
    if(!fin.is_open()) {
        cerr << "Could not open file " << file << endl;
        exit(EXIT_FAILURE);
    }
    fin>>size;
    graph.resize(size);

    for(i = 0; i < size; i++) {
        size_t tmpSize;
        fin >> tmpSize;
        if(tmpSize == 1 && expectInternalNode) {
            cerr << "All leaf nodes have to be first in the input file!" << endl;
            exit(EXIT_FAILURE);
        } else if(tmpSize == 1){
            numberOfLeaves++;
        } else {
            expectInternalNode = true;
        }
        for(j = 0; j < tmpSize; j++) {
            size_t tmpId;
            fin>>tmpId;
            graph[i].push_back(tmpId);
        }
    }
    fin.close();
   /*
    for(i=0;i<size;i++){
    
        for(j=0;j<graph[i].size();j++){
            cout<<graph[i][j]<<" ";
        }
        cout<<endl;
    
    }*/

}

/**
 * Sets the internal states corresponding to the two trees given as arguments
 */
void Days::initialize(const char *filename1, const char *filename2) {
  
    numberOfLeaves = 0;
    readFile(filename1, graph1);
    graph1NodeInfo.resize(graph1.size());
    readFile(filename2, graph2);
    graph2NodeInfo.resize(graph2.size());
    numberOfLeaves /= 2;
    dfsLabels.resize(numberOfLeaves, 0);

}

/**
 * Process the first tree (T1) according to Step 2 and Step 4 given in the slides in the first lecture, i.e. defines
 * the DF-numbering and calculating the intervals in all nodes.
 */
Days::node Days::step2(size_t curNode) {
    graph1NodeInfo[curNode].size = 0;
    graph1NodeInfo[curNode].minLabel = inf;
    graph1NodeInfo[curNode].maxLabel = 0;   //< Note that labeling starts at 1, thus no label can ever be 0

    if(curNode!=root && graph1[curNode].size() == 1) {
        // Set the DF-numbering/labeling at the given leaf
        dfsLabels[curNode] = step2Counter;
        // All leafs have size 1 and their label as minimum and maximum labels
        graph1NodeInfo[curNode].size = 1;
        graph1NodeInfo[curNode].minLabel = step2Counter;
        graph1NodeInfo[curNode].maxLabel = step2Counter;
        // Prepare for next leaf
        step2Counter++;
        return graph1NodeInfo[curNode];
    }
    visited[curNode] = true;


    for(size_t neighbour : graph1[curNode]){
        if(!visited[neighbour]){
            node info = step2(neighbour);
            // Update the current information
            graph1NodeInfo[curNode].minLabel = min(graph1NodeInfo[curNode].minLabel, info.minLabel);
            graph1NodeInfo[curNode].maxLabel = max(graph1NodeInfo[curNode].maxLabel, info.maxLabel);
            graph1NodeInfo[curNode].size += info.size;
        }
    }
    // The current node have now all information added
    return graph1NodeInfo[curNode];
    
}

/**
 *  Almost the same as Days::step2, but this only processes the second tree (T2). Instead of using new labels, we
 *  label all leafs to be the same as in the first tree.
 */
Days::node Days::step4(size_t curNode) {
    
    graph2NodeInfo[curNode].size = 0;
    graph2NodeInfo[curNode].minLabel = inf;
    graph2NodeInfo[curNode].maxLabel = 0;
    
    if(curNode!=root && graph2[curNode].size() == 1){
        graph2NodeInfo[curNode].size = 1;
        graph2NodeInfo[curNode].minLabel = dfsLabels[curNode];
        graph2NodeInfo[curNode].maxLabel = dfsLabels[curNode];
        return graph2NodeInfo[curNode];
    }
    
    visited[curNode] = true;
    
    for(size_t neighbour : graph2[curNode]){
        if(!visited[neighbour]){
            node info = step4(neighbour);
            graph2NodeInfo[curNode].minLabel = min(graph2NodeInfo[curNode].minLabel, info.minLabel);
            graph2NodeInfo[curNode].maxLabel = max(graph2NodeInfo[curNode].maxLabel, info.maxLabel);
            graph2NodeInfo[curNode].size += info.size;
        }
    }
    // The current node have now all information added
    return graph2NodeInfo[curNode];

}

size_t Days::run() {
    // Step 1, pick a common root
    // The input files are required to have all leafs first in the file, sorted such that they have the same order,
    // thus graph1[0] == graph2[0] holds
    root = 0;
    // Step 2, label all leafs in T1 a DF manner
    // Step 3, label all corresponding leaf nodes in T2 as for T1 (no-ops)
    // Step 4 (part 1), set all splits in T1
    step2Counter = 1;
    visited.resize(graph1.size(), false);
    step2(root);
    // Step 4 (part 2), find all splits in T2
    fill(visited.begin(), visited.begin()+graph2.size(), false);
//    visited.assign(graph2.size(), false);
    step4(root);

    // Step 4 (part 3), find all shared splits between T1 and T2
    //TODO: use radix sort
    sort(graph1NodeInfo.begin(), graph1NodeInfo.end(), Days::comp());
    sort(graph2NodeInfo.begin(), graph2NodeInfo.end(), Days::comp());
    
//    size_t i;
//    for(i=0;i<graph1NodeInfo.size();i++){
//        cout<<"["<<graph1NodeInfo[i].minLabel<<","<<graph1NodeInfo[i].maxLabel<<","<<graph1NodeInfo[i].size<<"] ";
//    }
//    cout<<endl;
//    for(i=0;i<graph2NodeInfo.size();i++){
//        cout<<"["<<graph2NodeInfo[i].minLabel<<","<<graph2NodeInfo[i].maxLabel<<","<<graph2NodeInfo[i].size<<"] ";
//    }
//    cout<<endl;
    
    size_t t1, t2,sharedSplits = 0;
    const size_t size1 = graph1NodeInfo.size();
    const size_t size2 = graph2NodeInfo.size();

    t1=t2=0;
    while(t1 < size1 && t2 < size2){
    
        const node node1 = graph1NodeInfo[t1];
        const node node2 = graph2NodeInfo[t2];
        
        if(node1 == node2){
            if(node1.size == node2.size) {
                // node1 is always filled with consequently filled intervals, thus that size of node1 always indicates
                // a legal split
                sharedSplits++;
                t1++;
            }
            t2++;
        } else if(node1 < node2){
            t1++;
        } else{
            t2++;
        }
        
    }
    // The RF-distance is then "number of splits not found in both trees", which is equal to the number of splits
    // in both trees, minus all the shared splits between T1 and T2 minus all the shared splits in T2 and T1
    return size1 + size2 - 2*sharedSplits;
}
