#include "HumanPyramids.h"
#include <error.h>
#include <stdbool.h>
#include <gridlocation.h>
#include <map.h>

using namespace std;

/* TODO: Refer to HumanPyramids.h for more information about what this function should do.
 * Then, delete this comment.
 */

bool inBounds(int row, int col, int height){
    if(row<0 || col<0){
        return false;
    }else if(col>row){
        return false;
    }else if(row>=height){
        return false;
    }
    return true;
}

double weightOnBackOfHelper(int row, int col, int pyramidHeight, Map<GridLocation,double> & table) {
    GridLocation location={row,col};
    if(!inBounds(row,col,pyramidHeight)){
        error("invalid input position!");
    }

    if(pyramidHeight < 0){
        error("invalid pyramid height");
    }

    if(row==0&&col==0){
        return 0;
    }else if(table.containsKey(location)){
        return table[location];
    }

    double leftweight=0;
    if(inBounds(row-1,col-1,pyramidHeight-1)){
        leftweight=80.0+0.5*weightOnBackOfHelper(row-1,col-1,pyramidHeight,table);
    }
    double rightweight=0;
    if(inBounds(row-1,col,pyramidHeight-1)){
        rightweight=80.0+0.5*weightOnBackOfHelper(row-1,col,pyramidHeight,table);
    }

    double weight=leftweight+rightweight;
    table[location]=leftweight+rightweight;
    return weight;


}


double weightOnBackOf(int row, int col, int pyramidHeight){
    Map<GridLocation,double> table;
    return weightOnBackOfHelper(row,col,pyramidHeight,table);
}





/* * * * * * Test Cases * * * * * */
#include "GUI/SimpleTest.h"

/* TODO: Add your own tests here. You know the drill - look for edge cases, think about
 * very small and very large cases, etc.
 */

















/* * * * * * Test cases from the starter files below this point. * * * * * */

PROVIDED_TEST("Check Person E from the handout.") {
    /* Person E is located at row 2, column 1. */
    EXPECT_EQUAL(weightOnBackOf(2, 1, 5), 240);
}

PROVIDED_TEST("Function reports errors in invalid cases.") {
    EXPECT_ERROR(weightOnBackOf(-1, 0, 10));
    EXPECT_ERROR(weightOnBackOf(10, 10, 5));
    EXPECT_ERROR(weightOnBackOf(-1, 10, 20));
}

PROVIDED_TEST("Stress test: Memoization is implemented (should take under a second)") {
    /* TODO: Yes, we are asking you to make a change to this test case! Delete the
     * line immediately after this one - the one that starts with SHOW_ERROR - once
     * you have implemented memoization to test whether it works correctly.
     */

    /* Do not delete anything below this point. :-) */

    /* This will take a LONG time to complete if memoization isn't implemented.
     * We're talking "heat death of the universe" amounts of time. :-)
     *
     * If you did implement memoization but this test case is still hanging, make
     * sure that in your recursive function (not the wrapper) that your recursive
     * calls are to your new recursive function and not back to the wrapper. If you
     * call the wrapper again, you'll get a fresh new memoization table rather than
     * preserving the one you're building up in your recursive exploration, and the
     * effect will be as if you hadn't implemented memoization at all.
     */
    EXPECT(weightOnBackOf(100, 50, 200) >= 10000);
}

/* TODO: Add your own tests here. You know the drill - look for edge cases, think about
 * very small and very large cases, etc.
 */


STUDENT_TEST("try 1 test"){
    EXPECT_EQUAL(weightOnBackOf(3, 2, 5), 340);
}


STUDENT_TEST("try another test"){
    EXPECT_EQUAL(weightOnBackOf(4, 2, 5), 500);
}
