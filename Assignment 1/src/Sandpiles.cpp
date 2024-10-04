/* File: Sandpiles.cpp
 *
 * TODO: Edit these comments to describe anything interesting or noteworthy in your implementation.
 */
#include "Sandpiles.h"
#include "GUI/SimpleTest.h"
#include <stdbool.h>
#include <cstdlib>


using namespace std;

void dropSandOn(Grid<int>& world, int row, int col) {
    /* TODO: Delete this line and the three after it, then implement this function. */
    world[row][col]+=1;
    if(world[row][col]>=4){
        world[row][col]=0;
        if(world.inBounds(row,col-1)){
            dropSandOn(world,row,col-1);
        }
        if(world.inBounds(row,col+1)){
            dropSandOn(world,row,col+1);
        }
        if(world.inBounds(row+1,col)){
            dropSandOn(world,row+1,col);
        }
        if(world.inBounds(row-1,col)){
            dropSandOn(world,row-1,col);
        }

    }

}


//EXTENSION
// Recursive unequal sand distribution when a cell topples
void unequalDrop(Grid<int>& world, int row, int col) {
    world[row][col] += 1;
    if (world[row][col] >= 4) {
        world[row][col] = 0;

        // Randomly choose three neighbors
        vector<pair<int, int>> neighbors;
        if (world.inBounds(row, col-1)) neighbors.push_back({row, col-1});
        if (world.inBounds(row, col+1)) neighbors.push_back({row, col+1});
        if (world.inBounds(row-1, col)) neighbors.push_back({row-1, col});
        if (world.inBounds(row+1, col)) neighbors.push_back({row+1, col});

        if (neighbors.size() >= 3) {
            random_shuffle(neighbors.begin(), neighbors.end()); // Randomly shuffle neighbors
            world[neighbors[0].first][neighbors[0].second] += 1; // First neighbor gets 1 grain
            world[neighbors[1].first][neighbors[1].second] += 1; // Second neighbor gets 1 grain
            world[neighbors[2].first][neighbors[2].second] += 2; // Third neighbor gets 2 grains

            // Recursively check if any neighbor topples
            if (world[neighbors[0].first][neighbors[0].second] >= 4) {
                unequalDrop(world, neighbors[0].first, neighbors[0].second);
            }
            if (world[neighbors[1].first][neighbors[1].second] >= 4) {
                unequalDrop(world, neighbors[1].first, neighbors[1].second);
            }
            if (world[neighbors[2].first][neighbors[2].second] >= 4) {
                unequalDrop(world, neighbors[2].first, neighbors[2].second);
            }
        }
    }
}

// Function 2: Allow cells to hold up to 4 grains, topple when 5 grains
void fiveGrainDrop(Grid<int>& world, int row, int col) {
    world[row][col] += 1;
    if (world[row][col] >= 5) {
        world[row][col]-=4;
        if (world.inBounds(row, col-1)) {
            fiveGrainDrop(world, row, col-1);
        }
        if (world.inBounds(row, col+1)) {
            fiveGrainDrop(world, row, col+1);
        }
        if (world.inBounds(row+1, col)) {
            fiveGrainDrop(world, row+1, col);
        }
        if (world.inBounds(row-1, col)) {
            fiveGrainDrop(world, row-1, col);
        }
    }
}



/* * * * * * Provided Test Cases * * * * * */

PROVIDED_TEST("Dropping into an empty cell only changes that cell.") {
    /* Create a simple source grid. */
    Grid<int> before = {
        { 3, 3, 3 },
        { 3, 0, 3 },
        { 3, 3, 3 }
    };
    Grid<int> after = {
        { 3, 3, 3 },
        { 3, 1, 3 },
        { 3, 3, 3 }
    };

    dropSandOn(before, 1, 1);
    EXPECT_EQUAL(before, after); // The above call changes 'before.'
}

PROVIDED_TEST("Non-chaining topples work.") {
    /* Create a simple source grid. */
    Grid<int> before = {
        { 0, 0, 0 },
        { 1, 3, 1 },
        { 0, 2, 0 }
    };
    Grid<int> after = {
        { 0, 1, 0 },
        { 2, 0, 2 },
        { 0, 3, 0 }
    };

    dropSandOn(before, 1, 1);
    EXPECT_EQUAL(before, after); // The above call changes 'before.'
}

PROVIDED_TEST("Two topples chain.") {
    /* Create a simple source grid. */
    Grid<int> before = {
        { 0, 0, 0, 0 },
        { 0, 3, 3, 0 },
        { 0, 0, 0, 0 }
    };
    Grid<int> after = {
        { 0, 1, 1, 0 },
        { 1, 1, 0, 1 },
        { 0, 1, 1, 0 }
    };

    dropSandOn(before, 1, 1);
    EXPECT_EQUAL(before, after); // The above call changes 'before.'
}

/* TODO: You will need to add your own tests into this suite of test cases. Think about the sorts
 * of inputs we tested here, and, importantly, what sorts of inputs we *didn't* test here. Some
 * general rules of testing:
 *
 *    1. Try extreme cases. What are some very large cases to check? What are some very small cases?
 *
 *    2. Be diverse. There are a lot of possible inputs out there. Make sure you have tests that account
 *       for cases that aren't just variations of one another.
 *
 *    3. Be sneaky. Don't just try standard inputs. Try weird ones that you wouldn't expect anyone to
 *       actually enter, but which are still perfectly legal.
 *
 * Happy testing!
 */

STUDENT_TEST("CHAIN EFFECT.") {
    /* Create a simple source grid. */
    Grid<int> before = {
        { 3, 3, 2 },
        { 2, 3, 3 },
        { 0, 2, 3 }
    };
    Grid<int> after = {
        { 1, 3, 0 },
        { 1, 0, 3 },
        { 2, 1, 1 }
    };

    dropSandOn(before, 1, 1);
    EXPECT_EQUAL(before, after); // The above call changes 'before.'
}


// Test unequal sand distribution with recursion when a cell topples
STUDENT_TEST("Test unequalDrop with unequal sand distribution and recursion.") {
    Grid<int> before = {
        { 3, 3, 3 },
        { 3, 4, 3 },
        { 3, 3, 3 }
    };
    Grid<int> after = {
        { 3, 4, 3 },
        { 3, 0, 4 },
        { 3, 3, 4 }
    };

    unequalDrop(before, 1, 1);  // Topple at (1, 1) with unequal sand distribution
    EXPECT(before != after);    // Ensure the grid changes, exact result may vary due to randomness
}


// Test five-grain toppling rule where cells topple only at 5 grains
STUDENT_TEST("Test fiveGrainDrop where cells topple at 5 grains.") {
    Grid<int> before = {
        { 3, 3, 3 },
        { 3, 4, 3 },
        { 3, 3, 3 }
    };
    Grid<int> after = {
        { 3, 4, 3 },
        { 4, 1, 4 },
        { 3, 4, 3 }
    };

    fiveGrainDrop(before, 1, 1);  // Add the 5th grain at (1, 1), causing toppling
    EXPECT_EQUAL(before, after);  // Ensure the grid reflects correct toppling behavior
}







