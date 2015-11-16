#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <tuple>

using namespace std;

struct node{

    size_t minLabel;
    size_t maxLabel;
    size_t size;
    
    bool operator==(const node& rhs) const
    {
        return std::tie(minLabel, maxLabel) == std::tie(rhs.minLabel, rhs.maxLabel);
    }
    
    bool operator<(const node& rhs) const
    {
        return std::tie(minLabel, maxLabel) < std::tie(rhs.minLabel, rhs.maxLabel);
    }

 };
 
 struct comp{
    
        bool operator()(const node &e1, const node &e2){
            if( e1.minLabel != e2.minLabel)
                return (e1.minLabel < e2.minLabel);
            return (e1.maxLabel < e2.maxLabel);
        }
   
};

void radixSort(vector<node>& data){

    size_t size = data.size();

    vector<node> tmpData(size);
    
    vector<size_t> counters(size,0);
    
    size_t i,tot,oldCount;
    
    for(i=0;i<size;i++){
        counters[data[i].maxLabel-1]++;
    }
    tot = 0;
    for(i=0;i<size;i++){
        oldCount = counters[i];
        counters[i] = tot;
        tot += oldCount;
    }
    
    //sort everything by max label, use counters to find the right positions
    for(i=0;i<size;i++){
        tmpData[counters[data[i].maxLabel-1]] = data[i];
        counters[data[i].maxLabel-1]++;
    }
    
    for(i=0;i<size;i++){
        counters[i] = 0;
    }
    
    for(i=0;i<size;i++){
        counters[tmpData[i].minLabel-1]++;
    }
    
    tot = 0;
    for(i=0;i<size;i++){
        oldCount = counters[i];
        counters[i] = tot;
        tot += oldCount;
    }
    
    //sort everything by min label, use counters to find the right positions
    for(i=0;i<size;i++){
        data[counters[tmpData[i].minLabel-1]] = tmpData[i];
        counters[tmpData[i].minLabel-1]++;
    }
    
}

int main(void){

    size_t size = 198980;
    size_t max = size;
    vector<node> dataQuickSort(size);
    vector<node> dataRadixSort(size);
    srand(time(NULL));
    int i;
    for(i=0;i<size;i++){
    
        node n;
        n.minLabel = rand()%size+1;
        n.maxLabel = n.minLabel + rand()%(size-n.minLabel+1);
        n.size = 0;
        dataQuickSort[i] = n;
        dataRadixSort[i] = n;
    
    }
    sort(dataQuickSort.begin(), dataQuickSort.end(), comp());
 
    radixSort(dataRadixSort);
    
    bool ok = true;
    
    for(i=0;i<size;i++){
        if(!(dataQuickSort[i] == dataRadixSort[i])){
            ok = false;
            break;
        }
    }
    
    if(ok) cout<<"success"<<endl;
    else cout<<"failure"<<endl;
    
    return 0;
}