// Write a C++ program that implements the FIFO and LRU page-replacement algorithms presented in this chapter. First, generate a random page reference string where page numbers range from 0 to 9. Apply the random page-reference string to each algorithm,and record the number of page faults incurred by each algorithm.

// The random page-reference string should consist of at least 10000 numbers. Using the same reference string, obtain the number of faults for each algorithm (FIFO and LRU) for each of the following number of page frames: 1, 2, 3, 4, 5, 6, 7, 8.

#include<bits/stdc++.h>
using namespace std;
 
// function for fifo
int fifo(int pagesArray[], int numOfPages, int frameSize){
    // declaring set for storing unique pages
    unordered_set<int> setUsed;
 
    //store page in fifo fashion
    queue<int> queueIndexes;
 
    // initially fault = 0
    int faults = 0;
    for(int i=0; i<numOfPages; i++){

        // if page exist in set
        if (setUsed.size() < frameSize){
            // if not insert else no
            if (setUsed.find(pagesArray[i])==setUsed.end()){
                setUsed.insert(pagesArray[i]);
 
                // page fault increases
                faults++;
 
                // push current page in queue
                queueIndexes.push(pagesArray[i]);
            }
        }
 
        // if page frame full that is set full perform deque
        else{
            if (setUsed.find(pagesArray[i]) == setUsed.end()){
                int value = queueIndexes.front();
                  
                // pop first  
                queueIndexes.pop();
 
                // removed the first came page
                setUsed.erase(value);
 
                // now insert the page in set
                setUsed.insert(pagesArray[i]);
                
                // and in queue
                queueIndexes.push(pagesArray[i]);
 
                // increase fault
                faults++;
            }
        }
    }
    return faults;
}

// lru function
int lru(int pagesArray[], int numOfPages, int frameSize){
    // set for frames
    unordered_set<int> setUsed;

    unordered_map<int, int> mapIndexes;
      // initilally fault = 0
    int faults = 0;
    for (int i=0; i<numOfPages; i++){
        // check if set full
        if (setUsed.size() < frameSize){
            if (setUsed.find(pagesArray[i])==setUsed.end()){
                setUsed.insert(pagesArray[i]);
 
                // increase fault
                faults++;
            }
            mapIndexes[pagesArray[i]] = i;
        }

        else{
            // if page exist
            if (setUsed.find(pagesArray[i]) == setUsed.end()){
                int LRU = INT_MAX, value;
                for (auto itr=setUsed.begin(); itr!=setUsed.end(); itr++){
                    if (mapIndexes[*itr] < LRU){
                        LRU = mapIndexes[*itr];
                        value = *itr;
                    }
                }

                // remove
                setUsed.erase(value);

                // insert current
                setUsed.insert(pagesArray[i]);

                // increase fault
                faults++;
            }
            // upadte
            mapIndexes[pagesArray[i]] = i;
        }
    }
    return faults;
}

// main method execution starts here
int main(){
    int pagesArray[10000];
    // generating random page numbers in range 0 to 9
    for(int i=0;i<10000;i++){
        pagesArray[i] = rand()%10;
    }
    
    // call fifo for different pageframesize
    for(int i=0;i<8;i++){
        int frameSize = (i+1);
        cout <<"Page Faults in FIFO for n = 10000 and frameSize = "<<fifo(pagesArray,10000,frameSize)<<endl;
    }
    cout<<endl;

    // call lru for different pageframesize
    for(int i=0;i<8;i++){
        int frameSize = (i+1);
        cout <<"Page Faults in LRU for n = 10000 and frameSize = "<<lru(pagesArray,10000,frameSize)<<endl;
    }

    return 0;
}