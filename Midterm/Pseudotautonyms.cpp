#include "Pseudotautonyms.h"
using namespace std;
#include <string>
#include <strlib.h>

bool isPseudotautonym(const string& str) {
    if(str.length()%2){
        return false;
    }

    int half=str.length()/2;
    string head=str.substr(0,half);
    head=toLowerCase(head);
    string tail=str.substr(half);
    tail=toLowerCase(tail);
    while(!head.empty()){
        for(int i=0;i<half;i++){
            if(head[0]==tail[i]){
                head=head.substr(1);
                tail=tail.substr(0,i)+tail.substr(i+1);
                break;
            }
            if(i==half-1){
                return false;
            }
        }
    }
    return true;

}

/************************************************************************
 * You are encouraged to - but not required to - add custom tests here. *
 ************************************************************************/

#include "GUI/SimpleTest.h"
