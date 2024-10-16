#include "ShiftScheduling.h"
#include "Shift.h"
#include <error.h>
using namespace std;

// int lengthOf(const Shift& shift);    // Returns the length of a shift.
// int valueOf(const Shift& shift);     // Returns the value of this shift.
// bool overlapsWith(const Shift& one,  // Returns whether two shifts overlap.
//                   const Shift& two);

int sumOfValue(const Set<Shift>& shifts){
    int sum=0;
    for(Shift shift:shifts){
        sum+=valueOf(shift);
    }
    return sum;
}

bool addLeadToOverlapping(Shift shift, const Set<Shift>& shifts){
    for(Shift current_shift:shifts){
        if(overlapsWith(shift,current_shift)){
            return true;
        }
    }
    return false;
}


Set<Shift> highestValueScheduleForHelper(const Set<Shift>& shifts_to_choose, const Set<Shift>& current, int remainHours) {
    if (shifts_to_choose.isEmpty()) {
        return current;
    }

    Shift task = shifts_to_choose.first();

    if (addLeadToOverlapping(task, current) || lengthOf(task) > remainHours) {
        return highestValueScheduleForHelper(shifts_to_choose - task, current, remainHours);
    } else {

        Set<Shift> withTask = highestValueScheduleForHelper(shifts_to_choose - task, current + task, remainHours - lengthOf(task));


        Set<Shift> withoutTask = highestValueScheduleForHelper(shifts_to_choose - task, current, remainHours);


        if (sumOfValue(withTask) > sumOfValue(withoutTask)) {
            return withTask;
        } else {
            return withoutTask;
        }
    }
}

Set<Shift> highestValueScheduleFor(const Set<Shift>& shifts, int maxHours) {
    if (maxHours < 0) {
        error("the max hour cannot be negative.");
    }

    Set<Shift> positive_shifts;
    for (Shift task : shifts) {
        if (valueOf(task) > 0) {
            positive_shifts.add(task);
        }
    }


    return highestValueScheduleForHelper(positive_shifts, {}, maxHours);
}



/* * * * * * Test Cases * * * * * */
#include "GUI/SimpleTest.h"
Set<Shift> asSet(const Vector<Shift>& shifts);

/* TODO: Add your own tests here. You know the drill - look for edge cases, think about
 * very small and very large cases, etc.
 */


STUDENT_TEST("handle some negative value shift"){
    Vector<Shift> shifts = {
        { Day::MONDAY,    10, 20, 500 }, // 10-hour shift, value is 500
        { Day::TUESDAY,   10, 15,  600 }, //  5-hour shift, value is 600
        { Day::WEDNESDAY, 10, 16,  -500 }, //  6-hour shift, value is -500
    };

    /* The correct strategy is to forgo the highest-value shift in favor of the two
     * shorter shifts.
     */
    auto schedule = highestValueScheduleFor(asSet(shifts), 30);

    EXPECT_EQUAL(schedule, { shifts[1], shifts[0] });
}


STUDENT_TEST("go on a strike lol"){
    Vector<Shift> shifts = {
        { Day::MONDAY,    10, 20, -500 }, // 10-hour shift, value is -500
        { Day::TUESDAY,   10, 15,  -600 }, //  5-hour shift, value is -600
        { Day::WEDNESDAY, 10, 16,  -500 }, //  6-hour shift, value is -500
    };

    /* The correct strategy is to forgo the highest-value shift in favor of the two
     * shorter shifts.
     */
    auto schedule = highestValueScheduleFor(asSet(shifts), 30);

    EXPECT_EQUAL(schedule, {});
}







/* * * * * * Test cases from the starter files below this point. * * * * * */
#include "vector.h"
#include "set.h"
#include "error.h"

/* This nice utility function lets you call highestValueScheduleFor, passing in
 * a Vector of shifts rather than a Set. This makes it a bit easier to test things.
 * You shouldn't need this function outside of these test cases.
 */
Set<Shift> asSet(const Vector<Shift>& shifts) {
    Set<Shift> result;
    for (Shift s: shifts) {
        result += s;
    }
    return result;
}

PROVIDED_TEST("Pick only shift if you have time for it.") {
    Set<Shift> shifts = {
        { Day::MONDAY, 9, 17, 1000 },  // Monday, 9AM - 5PM, value is 1000
    };

    EXPECT_EQUAL(highestValueScheduleFor(shifts, 24).size(), 1);
    EXPECT_EQUAL(highestValueScheduleFor(shifts, 24), shifts);
}

PROVIDED_TEST("Don't pick only shift if ou don't have time for it.") {
    Set<Shift> shifts = {
        { Day::MONDAY, 9, 17, 1000 },  // Monday, 9AM - 5PM, value is 1000
    };

    EXPECT_EQUAL(highestValueScheduleFor(shifts, 3).size(), 0);
}

PROVIDED_TEST("Don't pick overlapping shifts.") {
    Vector<Shift> shifts = {
        { Day::MONDAY, 9, 17, 1000 },  // Monday,  9AM - 5PM, value is 1000
        { Day::MONDAY, 8, 18, 2000 },  // Monday, 10AM - 6PM, value is 2000
    };

    EXPECT_EQUAL(highestValueScheduleFor(asSet(shifts), 100), { shifts[1] });
}

PROVIDED_TEST("Doesn't always use highest-value shift.") {
    Vector<Shift> shifts = {
        { Day::MONDAY,    10, 20, 1000 }, // 10-hour shift, value is 1000
        { Day::TUESDAY,   10, 15,  500 }, //  5-hour shift, value is 500
        { Day::WEDNESDAY, 10, 16,  501 }, //  6-hour shift, value is 501
    };

    /* The correct strategy is to forgo the highest-value shift in favor of the two
     * shorter shifts.
     */
    auto schedule = highestValueScheduleFor(asSet(shifts), 11);

    EXPECT_EQUAL(schedule, { shifts[1], shifts[2] });
}

PROVIDED_TEST("Doesn't always use the shift with the highest value per unit time.") {
    Vector<Shift> shifts = {
        { Day::MONDAY,    10, 17, 21 }, //  7-hour shift, value is 21 ($3 / hour)
        { Day::TUESDAY,   10, 16, 12 }, //  6-hour shift, value is 12 ($2 / hour)
        { Day::WEDNESDAY, 10, 16, 12 }, //  6-hour shift, value is 12 ($2 / hour)
    };

    /* If you have 12 hours, the correct strategy is to pick the two six-hour shifts
     * for a total of $24 value. Picking the shift with the highest value per unit
     * time (the seven-hour shift) produces only $21 value.
     */
    auto schedule = highestValueScheduleFor(asSet(shifts), 12);

    EXPECT_EQUAL(schedule, { shifts[1], shifts[2] });
}

PROVIDED_TEST("Passes the example from the assignment description.") {
    Vector<Shift> shifts = {
        { Day::MONDAY,     8, 12, 27 },  // Mon  8AM - 12PM, value 27 *
        { Day::MONDAY,    12, 16, 28 },  // Mon 12PM -  4PM, value 28 *
        { Day::MONDAY,    16, 20, 25 },  // Mon  4PM -  8PM, value 25 *
        { Day::MONDAY,     8, 14, 39 },  // Mon  8AM -  2PM, value 39
        { Day::MONDAY,    14, 20, 31 },  // Mon  2PM -  8PM, value 31
        { Day::TUESDAY,    8, 12,  7 },  // Tue  8AM - 12PM, value  7
        { Day::TUESDAY,   12, 16,  7 },  // Tue 12PM -  4PM, value  7
        { Day::TUESDAY,   16, 20, 11 },  // Tue  4PM -  8PM, value 11
        { Day::TUESDAY,    8, 14, 10 },  // Tue  8AM -  2PM, value 10
        { Day::TUESDAY,   14, 20,  8 },  // Tue  2PM -  8PM, value  8
        { Day::WEDNESDAY,  8, 12, 10 },  // Wed  8AM - 12PM, value 10
        { Day::WEDNESDAY, 12, 16, 11 },  // Wed 12PM -  4PM, value 11
        { Day::WEDNESDAY, 16, 20, 13 },  // Wed  4PM -  8PM, value 13
        { Day::WEDNESDAY,  8, 14, 19 },  // Wed  8AM -  2PM, value 19
        { Day::WEDNESDAY, 14, 20, 25 },  // Wed  2PM -  8PM, value 25 *
    };

    /* Get back the solution. */
    Set<Shift> computedSolution = highestValueScheduleFor(asSet(shifts), 20);

    /* Form the correct answer. It's the starred entries. */
    Set<Shift> actualSolution = {
        shifts[0], shifts[1], shifts[2], shifts[14]
    };

    EXPECT_EQUAL(computedSolution, actualSolution);
}

PROVIDED_TEST("Handles no shifts.") {
    EXPECT_EQUAL(highestValueScheduleFor({}, 137).size(), 0);
}

PROVIDED_TEST("Reports an error with negative hours.") {
    /* From the assignment description. */
    Vector<Shift> shifts = {
        { Day::MONDAY,     8, 12, 27 },  // Mon  8AM - 12PM, value 27
        { Day::MONDAY,    12, 16, 28 },  // Mon 12PM -  4PM, value 28
        { Day::MONDAY,    16, 20, 25 },  // Mon  4PM -  8PM, value 25
        { Day::MONDAY,     8, 14, 39 },  // Mon  8AM -  2PM, value 39
        { Day::MONDAY,    14, 20, 31 },  // Mon  2PM -  8PM, value 31
        { Day::TUESDAY,    8, 12,  7 },  // Tue  8AM - 12PM, value  7
        { Day::TUESDAY,   12, 16,  7 },  // Tue 12PM -  4PM, value  7
        { Day::TUESDAY,   16, 20, 11 },  // Tue  4PM -  8PM, value 11
        { Day::TUESDAY,    8, 14, 10 },  // Tue  8AM -  2PM, value 10
        { Day::TUESDAY,   14, 20,  8 },  // Tue  2PM -  8PM, value  8
        { Day::WEDNESDAY,  8, 12, 10 },  // Wed  8AM - 12PM, value 10
        { Day::WEDNESDAY, 12, 16, 11 },  // Wed 12PM -  4PM, value 11
        { Day::WEDNESDAY, 16, 20, 13 },  // Wed  4PM -  8PM, value 13
        { Day::WEDNESDAY,  8, 14, 19 },  // Wed  8AM -  2PM, value 19
        { Day::WEDNESDAY, 14, 20, 25 },  // Wed  2PM -  8PM, value 25
    };

    /* Should be an error. */
    EXPECT_ERROR(highestValueScheduleFor(asSet(shifts), -1));

    /* Still an error even if there are no shifts. */
    EXPECT_ERROR(highestValueScheduleFor({}, -1));
}

PROVIDED_TEST("Handles zero free hours.") {
    /* From the assignment description. */
    Vector<Shift> shifts = {
        { Day::MONDAY,     8, 12, 27 },  // Mon  8AM - 12PM, value 27
        { Day::MONDAY,    12, 16, 28 },  // Mon 12PM -  4PM, value 28
        { Day::MONDAY,    16, 20, 25 },  // Mon  4PM -  8PM, value 25
        { Day::MONDAY,     8, 14, 39 },  // Mon  8AM -  2PM, value 39
        { Day::MONDAY,    14, 20, 31 },  // Mon  2PM -  8PM, value 31
        { Day::TUESDAY,    8, 12,  7 },  // Tue  8AM - 12PM, value  7
        { Day::TUESDAY,   12, 16,  7 },  // Tue 12PM -  4PM, value  7
        { Day::TUESDAY,   16, 20, 11 },  // Tue  4PM -  8PM, value 11
        { Day::TUESDAY,    8, 14, 10 },  // Tue  8AM -  2PM, value 10
        { Day::TUESDAY,   14, 20,  8 },  // Tue  2PM -  8PM, value  8
        { Day::WEDNESDAY,  8, 12, 10 },  // Wed  8AM - 12PM, value 10
        { Day::WEDNESDAY, 12, 16, 11 },  // Wed 12PM -  4PM, value 11
        { Day::WEDNESDAY, 16, 20, 13 },  // Wed  4PM -  8PM, value 13
        { Day::WEDNESDAY,  8, 14, 19 },  // Wed  8AM -  2PM, value 19
        { Day::WEDNESDAY, 14, 20, 25 },  // Wed  2PM -  8PM, value 25
    };

    /* Shouldn't be an error if time is zero - that means we just don't pick anything. */
    EXPECT_EQUAL(highestValueScheduleFor(asSet(shifts), 0).size(), 0);
}

PROVIDED_TEST("Stress test: Don't generate shift combinations with overlapping shifts.") {
    /* All of these shifts overlap one another. If you try producing all combinations
     * of these shifts and only check at the end whether they're valid, you'll be
     * checking 2^100 ~= 10^30 combinations of shifts, which will take so long the
     * sun will have burnt out before you're finished.
     *
     * Instead, as you're going through your decision tree and building up your shifts,
     * make sure not to include any shifts that clearly conflict with something you
     * picked earlier.
     */
    Set<Shift> trickySet;
    for (int i = 0; i < 100; i++) {
        trickySet += Shift{ Day::MONDAY, 1, 2, i };
    }
    EXPECT_EQUAL(trickySet.size(), 100);

    auto result = highestValueScheduleFor(trickySet, 1);
    EXPECT_EQUAL(result.size(), 1);
}

PROVIDED_TEST("Stress test: Don't generate shift combinations that exceed time limits.") {
    /* Here's a collection of one shift per hour of the week. Your worker has exactly
     * one hour free. If you try all possible combinations of these shifts, ignoring time
     * constraints, you will have to check over 2^100 = 10^30 combinations, which will
     * take longer than the length of the known universe to process.
     *
     * Instead, as you're exploring the decision tree to generate shift combinations,
     * make sure not to add shifts that would exceed the time limit.
     */
    Set<Shift> trickySet;
    for (Day day: { Day::SUNDAY,
                    Day::MONDAY,
                    Day::TUESDAY,
                    Day::WEDNESDAY,
                    Day::THURSDAY,
                    Day::FRIDAY,
                    Day::SATURDAY}) {
        for (int start = 0; start < 24; start++) {
            trickySet += Shift{ day, start, start + 1, 10 };
        }
    }
    EXPECT_EQUAL(trickySet.size(), 7 * 24);

    auto result = highestValueScheduleFor(trickySet, 1);
    EXPECT_EQUAL(result.size(), 1);
}

PROVIDED_TEST("Stress test: Can handle a decent number of shifts (should take at most 10-15 seconds)") {
    /* Available shifts. */
    Vector<Shift> shifts = {
        { Day::SUNDAY,  8, 14, 12 },
        { Day::SUNDAY, 12, 18, 36 },

        { Day::MONDAY,  8, 12, 44 },
        { Day::MONDAY, 12, 16, 32 },
        { Day::MONDAY, 16, 20,  0 },
        { Day::MONDAY,  8, 16, 16 },
        { Day::MONDAY, 12, 20, 22 },

        { Day::TUESDAY,  8, 12, 48 },
        { Day::TUESDAY, 12, 16, 20 },
        { Day::TUESDAY, 16, 20, 24 },
        { Day::TUESDAY,  8, 16, 24 },
        { Day::TUESDAY, 12, 20, 80 },

        { Day::WEDNESDAY,  8, 12, 20 },
        { Day::WEDNESDAY, 12, 16,  8 },
        { Day::WEDNESDAY, 16, 20,  8 },
        { Day::WEDNESDAY,  8, 16, 40 },
        { Day::WEDNESDAY, 12, 20, 16 },

        { Day::THURSDAY,  8, 12, 40 },
        { Day::THURSDAY, 12, 16,  0 },
        { Day::THURSDAY, 16, 20, 24 },
        { Day::THURSDAY,  8, 16, 56 },
        { Day::THURSDAY, 12, 20, 32 },

        { Day::FRIDAY,  8, 12,  4 },
        { Day::FRIDAY, 12, 16,  8 },
        { Day::FRIDAY, 16, 20, 40 },
        { Day::FRIDAY,  8, 16, 72 },
        { Day::FRIDAY, 12, 20, 40 },

        { Day::SATURDAY,  8, 14, 18 },
        { Day::SATURDAY, 12, 18, 66 },
    };

    auto answer = highestValueScheduleFor(asSet(shifts), 30);
    EXPECT_EQUAL(answer, { shifts[2], shifts[7], shifts[11], shifts[17], shifts[24], shifts[28] });
}
