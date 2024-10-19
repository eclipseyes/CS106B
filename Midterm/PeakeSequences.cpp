#include "PeakeSequences.h"
#include <map.h>
using namespace std;


int numPeakeSequencesForRec(int n,Map<int,int>& saved) {
    if(n<=0){
        return 0;
    }
    if(n==1){
        return 1;   // 1
    }
    if(saved.containsKey(n)){
        return saved[n];
    }

    //recursive case:
    int ways=0;
    for(int i=1;i<n;i++){   //add to n: e.g.（1）+ 4  （2）+ 3  （3）+ 2  （4）+ 1
        ways+=numPeakeSequencesForRec(i,saved);
    }
    for(int i=1;i<n;i++){  //multiple to n: e.g. 1*5
        if(n%i==0){
            ways+=numPeakeSequencesForRec(i,saved);
        }
    }
    ways++;  //5
    saved[n]=ways;
    return ways;
}

int numPeakeSequencesFor(int n){
    Map<int,int> saved;
    return numPeakeSequencesForRec(n,saved);
}

/************************************************************************
 * You are encouraged to - but not required to - add custom tests here. *
 ************************************************************************/

#include "GUI/SimpleTest.h"
