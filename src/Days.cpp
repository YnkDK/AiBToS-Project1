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

void Days::readFile(const char* file, vector< vector< size_t > >& graph)
{
    ifstream fin;
    fin.open(file,ios_base::in);

    size_t size;
    fin>>size;
    graph.resize(size);

    size_t i,j;

    for(i=0;i<size;i++){

        size_t tmpSize;
        fin>>tmpSize;
        if(tmpSize == 1){
            numberOfLeaves++;
        }
        for(j=0;j<tmpSize;j++){
            
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

void Days::initialize(const char *filename1, const char *filename2) {
  
    numberOfLeaves = 0;
    readFile(filename1, graph1);
    graph1NodeInfo.resize(graph1.size());
    readFile(filename2, graph2);
    graph2NodeInfo.resize(graph2.size());
    numberOfLeaves /= 2;
    dfsLabels.resize(numberOfLeaves, 0);

}

Days::node Days::step2(size_t curNode)
{
    graph1NodeInfo[curNode].size = 0;
    graph1NodeInfo[curNode].minLabel = inf;
    graph1NodeInfo[curNode].maxLabel = 0;
    
    if(curNode!=root && graph1[curNode].size() == 1){
        dfsLabels[curNode] = step2Counter;
        graph1NodeInfo[curNode].size = 1;
        graph1NodeInfo[curNode].minLabel = step2Counter;
        graph1NodeInfo[curNode].maxLabel = step2Counter;
        step2Counter++;
        return graph1NodeInfo[curNode];
    }
    
    visited[curNode] = true;
    
    for(size_t neighBour : graph1[curNode]){
    
        if(!visited[neighBour]){
            
            node info = step2(neighBour);
            graph1NodeInfo[curNode].minLabel = min(graph1NodeInfo[curNode].minLabel, info.minLabel);
            graph1NodeInfo[curNode].maxLabel = max(graph1NodeInfo[curNode].maxLabel, info.maxLabel);
            graph1NodeInfo[curNode].size += info.size;
            
        }
        
    }
    
    return graph1NodeInfo[curNode];
    
}

Days::node Days::step4(size_t curNode)
{
    
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
    
    for(size_t neighBour : graph2[curNode]){
    
        if(!visited[neighBour]){
            node info = step4(neighBour);
            graph2NodeInfo[curNode].minLabel = min(graph2NodeInfo[curNode].minLabel, info.minLabel);
            graph2NodeInfo[curNode].maxLabel = max(graph2NodeInfo[curNode].maxLabel, info.maxLabel);
            graph2NodeInfo[curNode].size += info.size;
            
        }
        
    }
    
    return graph2NodeInfo[curNode];

}

size_t Days::run() {
    root = 0;
    step2Counter = 1;
    visited.resize(graph1.size(), false);
    step2(root);
    for(size_t i=0;i<graph2.size();i++)
        visited[i] = false;
    step4(root);
    
    //TODO: use radix sort
    sort(graph1NodeInfo.begin(), graph1NodeInfo.end(), Days::comp());
    sort(graph2NodeInfo.begin(), graph2NodeInfo.end(), Days::comp());
    
    size_t i;
    for(i=0;i<graph1NodeInfo.size();i++){
        cout<<"["<<graph1NodeInfo[i].minLabel<<","<<graph1NodeInfo[i].maxLabel<<","<<graph1NodeInfo[i].size<<"] ";
    }
    cout<<endl;
    for(i=0;i<graph2NodeInfo.size();i++){
        cout<<"["<<graph2NodeInfo[i].minLabel<<","<<graph2NodeInfo[i].maxLabel<<","<<graph2NodeInfo[i].size<<"] ";
    }
    cout<<endl;
    
    size_t t1, t2;
    size_t size1 = graph1NodeInfo.size();
    size_t size2 = graph2NodeInfo.size();
    size_t sharedSplits = 0;
    
    t1=t2=0;
    while(t1<size1 && t2<size2){
    
        node node1 = graph1NodeInfo[t1];
        node node2 = graph2NodeInfo[t2];
        
        if(node1 == node2){
            
            if(node1.size == node2.size)
                sharedSplits++;
            
            t1++;
            t2++;
            
        }else if(node1 < node2){
            
            t1++;
        
        }
        else{
            t2++;
        }
        
    }
    cout<<sharedSplits<<endl;
    cout<<"Distance: "<<size1+size2-2*sharedSplits<<endl;
    
    
    return 0;
}
