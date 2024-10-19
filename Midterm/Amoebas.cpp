#include "Amoebas.h"
#include "grid.h"
#include <gridlocation.h>
#include <queue.h>
#include <vector.h>
using namespace std;

Vector<Grid<bool>> simulateAmoebas(const Grid<bool>& world) {
    Vector<Grid<bool>> sequence;
    auto status=world;
    sequence.add(world);
    int rowNum=world.numRows();
    int colNum=world.numCols();
    if(rowNum<=0||colNum<=0){
        return sequence;
    }
    while(1){
        Queue<GridLocation> toBePainted;
        for(int row=0;row<rowNum;row++){
            for(int col=0;col<colNum;col++){
                if(status[row][col]==false){
                    int calculated=0;
                    if(status.inBounds(row,col-1)&&status[row][col-1]) calculated++;
                    if(status.inBounds(row,col+1)&&status[row][col+1]) calculated++;
                    if(status.inBounds(row-1,col)&&status[row-1][col]) calculated++;
                    if(status.inBounds(row+1,col)&&status[row+1][col]) calculated++;
                    if(calculated>=2){
                        toBePainted.enqueue({row,col});
                    }
                }
            }
        }
        if(toBePainted.isEmpty()){
            break;
        }
        while(!toBePainted.isEmpty()){
            GridLocation location=toBePainted.dequeue();
            status[location.row][location.col]=true;
        }
        sequence.add(status);
    }
    return sequence;
}

/************************************************************************
 * You are encouraged to - but not required to - add custom tests here. *
 ************************************************************************/

#include "GUI/SimpleTest.h"


STUDENT_TEST("Works on the example designed by the example") {
    Grid<bool> initial = {
        {  false,true,false,false,true,false },
        { true,false,false,false,false,true },
        { false,false,false,false,false,false },
        { false,false,false,false,false,false },
        { true,false,false,false,false,true },
        {  false,true,false,false,true,false }
    };

    Vector<Grid<bool>> sequence = {
        {
            {  false,true,false,false,true,false },
            { true,false,false,false,false,true },
            { false,false,false,false,false,false },
            { false,false,false,false,false,false },
            { true,false,false,false,false,true },
            {  false,true,false,false,true,false }
        },

        {
            {  true,true,false,false,true,true },
            { true,true,false,false,true,true },
            { false,false,false,false,false,false },
            { false,false,false,false,false,false },
            { true,true,false,false,true,true },
            {  true,true,false,false,true,true }
        }

                                   };

    EXPECT_EQUAL(simulateAmoebas(initial), sequence);
}
