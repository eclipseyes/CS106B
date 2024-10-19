#include "PeakeSequences.h"
#include "GUI/SimpleTest.h"
#include "Demos/Timer.h"
using namespace std;

PROVIDED_TEST("Counts Peake sequences for small numbers.") {
    EXPECT_EQUAL(numPeakeSequencesFor(3), 6);
    EXPECT_EQUAL(numPeakeSequencesFor(10), 1008);
}

PROVIDED_TEST("Stress Test: Handles large inputs.") {

    Timing::Timer timer;
    timer.start();
    EXPECT_EQUAL(numPeakeSequencesFor(31), 2123121900);
    timer.stop();

    /* Computing the above value should be essentially instantaneous. */
    EXPECT_LESS_THAN_OR_EQUAL_TO(timer.timeInSeconds(), 0.1);
}
