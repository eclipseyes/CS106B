#include "Amoebas.h"
#include "GUI/SimpleTest.h"
#include "Demos/Timer.h"
using namespace std;

PROVIDED_TEST("Works on the example from the description.") {
    Grid<bool> initial = {
       {  true, false,  true },
       { false, false, false },
       { false,  true, false }
    };

    Vector<Grid<bool>> sequence = {
        {
            {  true, false,  true },
            { false, false, false },
            { false,  true, false }
        },
        {
            {  true,  true,  true },
            { false, false, false },
            { false,  true, false }
        },
        {
            {  true,  true,  true },
            { false,  true, false },
            { false,  true, false }
        },
        {
            {  true,  true,  true },
            {  true,  true,  true },
            { false,  true, false }
        },
        {
            {  true,  true,  true },
            {  true,  true,  true },
            {  true,  true,  true }
        },
    };

    EXPECT_EQUAL(simulateAmoebas(initial), sequence);
}

PROVIDED_TEST("Works when no amoebas spread.") {
    Grid<bool> initial = {
       {  true, false, false },
       { false, false, false },
       { false, false,  true }
    };

    EXPECT_EQUAL(simulateAmoebas(initial), { initial });
}

PROVIDED_TEST("Stress Test: Works for slow amoeba growth.") {
    /* To illustrate how this works: Consider this initial grid,
     * where # indicates an amoeba and . denotes an empty square:
     *
     *          #################
     *          .................
     *          ................#
     *          .................
     *          #................
     *          .................
     *          ................#
     *          .................
     *          #................
     *
     * If you trace through a few steps of this process, you'll find
     * that it sweeps from the top-right to the top-left, then snakes
     * back and forth over the world until eventually everything ends
     * up filled in.
     *
     * Rather than 'hard-code' this grid in, we use the parameters
     * below to generate a very large world that has this shape.
     */
    const int numRows = 50;
    const int numCols = 50;

    static_assert(numRows >= 1, "Must have at least one row.");

    /* Top stripe. */
    Grid<bool> initial(numRows, numCols);
    for (int col = 0; col < numCols; col++) {
        initial[0][col] = true;
    }

    /* Snake back and forth. */
    for (int row = 2; row < numRows; row++) {
        /* Treat every other row differently. */
        if (row % 4 == 2) {
            initial[row][0] = true;
        } else {
            initial[row][numCols - 1] = true;
        }
    }

    Timing::Timer timer;
    timer.start();
    auto result = simulateAmoebas(initial);
    timer.stop();

    /* Should be a sequence of frames. */
    EXPECT(!result.isEmpty());

    /* First frame should match the original one. */
    EXPECT_EQUAL(result[0], initial);

    /* Last time step should be full of amoebas. */
    EXPECT_EQUAL(result[result.size() - 1], Grid<bool>(numRows, numCols, true));

    /* Everything should complete quickly. */
    EXPECT_LESS_THAN_OR_EQUAL_TO(timer.timeInSeconds(), 5);
}
