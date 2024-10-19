#include "Pseudotautonyms.h"
#include "GUI/SimpleTest.h"
#include "Demos/Timer.h"
#include <string>
using namespace std;

PROVIDED_TEST("Works on example pseudotautonyms") {
    EXPECT(isPseudotautonym("intestines"));
    EXPECT(isPseudotautonym("pullup"));
    EXPECT(isPseudotautonym("reappear"));
    EXPECT(isPseudotautonym("redder"));
    EXPECT(isPseudotautonym("teammate"));
    EXPECT(isPseudotautonym("signings"));
}

PROVIDED_TEST("Is case-insensitive.") {
    EXPECT(isPseudotautonym("TeAmMaTe"));
}

PROVIDED_TEST("Works on symbols.") {
    EXPECT(isPseudotautonym("(-: ** :-("));
}

PROVIDED_TEST("Stress test: Handles a large ABBA string.") {
    /* This test case builds a string of length roughly
     * 100,000 of the general pattern ABBA, where each
     * A and each B represents a huge block of 'a' and 'b'
     * characters.
     *
     * If your solution does not pass this test, it may mean
     * that your solution does not make efficient use of the
     * string type or of our container types.
     */

    const int kBlockLength = 25000;
    string as(kBlockLength, 'a');
    string bs(kBlockLength, 'b');

    string testCase = as + bs + bs + as;

    Timing::Timer timer;
    timer.start();
    EXPECT(isPseudotautonym(testCase));
    timer.stop();

    /* This is a very comfortable safety margin on top of
     * what we think should be needed.
     */
    EXPECT_LESS_THAN(timer.timeInSeconds(), 3);
}

PROVIDED_TEST("Stress test: Handles a large ABAB string.") {
    /* This test case builds a string of length roughly
     * 100,000 of the general pattern ABAB, where each
     * A and each B represents a huge block of 'a' and 'b'
     * characters.
     *
     * If your solution does not pass this test, it may mean
     * that your solution does not make efficient use of the
     * string type or of our container types.
     */

    const int kBlockLength = 25000;
    string as(kBlockLength, 'a');
    string bs(kBlockLength, 'b');

    string testCase = as + bs + as + bs;

    Timing::Timer timer;
    timer.start();
    EXPECT(isPseudotautonym(testCase));
    timer.stop();

    /* This is a very comfortable safety margin on top of
     * what we think should be needed.
     */
    EXPECT_LESS_THAN(timer.timeInSeconds(), 3);
}

PROVIDED_TEST("Stress test: Handles a large ABBBAB string.") {
    /* This test case builds a string of length roughly
     * 100,000 of the general pattern ABBBAB, where each
     * A and each B represents a huge block of 'a' and 'b'
     * characters.
     *
     * If your solution does not pass this test, it may mean
     * that your solution does not make efficient use of the
     * string type or of our container types.
     */

    const int kBlockLength = 16000;
    string as(kBlockLength, 'a');
    string bs(kBlockLength, 'b');

    string testCase = as + bs + bs + bs + as + bs;

    Timing::Timer timer;
    timer.start();
    EXPECT(isPseudotautonym(testCase));
    timer.stop();

    /* This is a very comfortable safety margin on top of
     * what we think should be needed.
     */
    EXPECT_LESS_THAN(timer.timeInSeconds(), 3);
}
