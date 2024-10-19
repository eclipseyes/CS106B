#include "CareTeams.h"
#include "GUI/SimpleTest.h"
#include "Demos/Timer.h"
using namespace std;

PROVIDED_TEST("Works for groups of size one.") {
    EXPECT_EQUAL(allCareTeamsFor({"AA"}, {"BB"}, {"CC"}),
                 { { { "AA", "BB", "CC" } } });
}

PROVIDED_TEST("Works for groups of size two.") {
    EXPECT_EQUAL(allCareTeamsFor({"AA", "BB"}, {"CC", "DD"}, {"EE", "FF"}),
                 { { { "AA", "CC", "EE" }, { "BB", "DD", "FF" } },
                   { { "AA", "CC", "FF" }, { "BB", "DD", "EE" } },
                   { { "AA", "DD", "EE" }, { "BB", "CC", "FF" } },
                   { { "AA", "DD", "FF" }, { "BB", "CC", "EE" } } });
}

PROVIDED_TEST("Works for groups of size three.") {
    EXPECT_EQUAL(allCareTeamsFor({"AA", "BB", "CC"},
                                 {"DD", "EE", "FF"},
                                 {"GG", "HH", "II"}),
                 {{{"AA", "DD", "GG"}, {"BB", "EE", "HH"}, {"CC", "FF", "II"}},
                  {{"AA", "DD", "GG"}, {"BB", "EE", "II"}, {"CC", "FF", "HH"}},
                  {{"AA", "DD", "GG"}, {"BB", "FF", "HH"}, {"CC", "EE", "II"}},
                  {{"AA", "DD", "GG"}, {"BB", "FF", "II"}, {"CC", "EE", "HH"}},
                  {{"AA", "DD", "HH"}, {"BB", "EE", "GG"}, {"CC", "FF", "II"}},
                  {{"AA", "DD", "HH"}, {"BB", "EE", "II"}, {"CC", "FF", "GG"}},
                  {{"AA", "DD", "HH"}, {"BB", "FF", "GG"}, {"CC", "EE", "II"}},
                  {{"AA", "DD", "HH"}, {"BB", "FF", "II"}, {"CC", "EE", "GG"}},
                  {{"AA", "DD", "II"}, {"BB", "EE", "GG"}, {"CC", "FF", "HH"}},
                  {{"AA", "DD", "II"}, {"BB", "EE", "HH"}, {"CC", "FF", "GG"}},
                  {{"AA", "DD", "II"}, {"BB", "FF", "GG"}, {"CC", "EE", "HH"}},
                  {{"AA", "DD", "II"}, {"BB", "FF", "HH"}, {"CC", "EE", "GG"}},
                  {{"AA", "EE", "GG"}, {"BB", "DD", "HH"}, {"CC", "FF", "II"}},
                  {{"AA", "EE", "GG"}, {"BB", "DD", "II"}, {"CC", "FF", "HH"}},
                  {{"AA", "EE", "GG"}, {"BB", "FF", "HH"}, {"CC", "DD", "II"}},
                  {{"AA", "EE", "GG"}, {"BB", "FF", "II"}, {"CC", "DD", "HH"}},
                  {{"AA", "EE", "HH"}, {"BB", "DD", "GG"}, {"CC", "FF", "II"}},
                  {{"AA", "EE", "HH"}, {"BB", "DD", "II"}, {"CC", "FF", "GG"}},
                  {{"AA", "EE", "HH"}, {"BB", "FF", "GG"}, {"CC", "DD", "II"}},
                  {{"AA", "EE", "HH"}, {"BB", "FF", "II"}, {"CC", "DD", "GG"}},
                  {{"AA", "EE", "II"}, {"BB", "DD", "GG"}, {"CC", "FF", "HH"}},
                  {{"AA", "EE", "II"}, {"BB", "DD", "HH"}, {"CC", "FF", "GG"}},
                  {{"AA", "EE", "II"}, {"BB", "FF", "GG"}, {"CC", "DD", "HH"}},
                  {{"AA", "EE", "II"}, {"BB", "FF", "HH"}, {"CC", "DD", "GG"}},
                  {{"AA", "FF", "GG"}, {"BB", "DD", "HH"}, {"CC", "EE", "II"}},
                  {{"AA", "FF", "GG"}, {"BB", "DD", "II"}, {"CC", "EE", "HH"}},
                  {{"AA", "FF", "GG"}, {"BB", "EE", "HH"}, {"CC", "DD", "II"}},
                  {{"AA", "FF", "GG"}, {"BB", "EE", "II"}, {"CC", "DD", "HH"}},
                  {{"AA", "FF", "HH"}, {"BB", "DD", "GG"}, {"CC", "EE", "II"}},
                  {{"AA", "FF", "HH"}, {"BB", "DD", "II"}, {"CC", "EE", "GG"}},
                  {{"AA", "FF", "HH"}, {"BB", "EE", "GG"}, {"CC", "DD", "II"}},
                  {{"AA", "FF", "HH"}, {"BB", "EE", "II"}, {"CC", "DD", "GG"}},
                  {{"AA", "FF", "II"}, {"BB", "DD", "GG"}, {"CC", "EE", "HH"}},
                  {{"AA", "FF", "II"}, {"BB", "DD", "HH"}, {"CC", "EE", "GG"}},
                  {{"AA", "FF", "II"}, {"BB", "EE", "GG"}, {"CC", "DD", "HH"}},
                  {{"AA", "FF", "II"}, {"BB", "EE", "HH"}, {"CC", "DD", "GG"}}});
}

PROVIDED_TEST("Stress test: Works for groups of size five.") {
    Set<string> all = {"AA", "BB", "CC", "DD", "EE"};

    Timing::Timer timer;
    timer.start();
    EXPECT_EQUAL(allCareTeamsFor(all, all, all).size(), 14400);
    timer.stop();

    /* Comfortable margin of safety above our reference solution. */
    EXPECT_LESS_THAN(timer.timeInSeconds(), 15);
}
