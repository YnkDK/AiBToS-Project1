#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <tuple>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]){

    size_t sizeP2 = atoi(argv[1]);
    
    ofstream fout; 
    fout.open("adj"+to_string(sizeP2)+".adj", ios_base::out);
    
    size_t numLeafs = pow(2,sizeP2);
    size_t size = 2*numLeafs-1;
    vector<vector<size_t>> adj(size);
    
    size_t i,j;
    i=0;
    size_t next = numLeafs;
    while(i<size){
    
        j = i;
        
        while(j<i+numLeafs-1){
        
            adj[next].push_back(j);
            adj[next].push_back(j+1);
            adj[j].push_back(next);
            adj[j+1].push_back(next);
            j += 2;
            next += 1;
            
        }
        
        i += numLeafs;
        numLeafs /= 2;
        
    
    }
    
    fout<<adj.size()<<endl;
    for(i=0;i<size;i++){
        fout<<adj[i].size()<<" ";
        for(j=0;j<adj[i].size();j++){
            fout<<adj[i][j]<<" ";
        }
        fout<<endl;
    }
    fout.close();
    
    return 0;
}
