/* File: PlayingFair.cpp
 *
 * TODO: Edit these comments to describe anything interesting or noteworthy in your implementation.
 */
#include "PlayingFair.h"
#include "GUI/SimpleTest.h"
#include "error.h"
#include <cstdlib>
#include <ctime>

using namespace std;


string aSequenceOfOrder(int n) {
    /* TODO: Delete this line and the next two lines, then implement this function. */
    if(n<0){
        error("a string containing your error message");
    }
    else{
        if(n==0){
            return "A";
        }
        else{
            return aSequenceOfOrder(n-1)+bSequenceOfOrder(n-1);
        }
    }
}

string bSequenceOfOrder(int n) {
    /* TODO: Delete this line and the next two lines, then implement this function. */
    if(n<0){
        error("a string containing your error message");
    }
    else{
        if(n==0){
            return "B";
        }
        else{
            return bSequenceOfOrder(n-1)+aSequenceOfOrder(n-1);
        }
    }
}



//EXTENSION  :GENERATE MORE THAN TWO MUTURAL RECURSIVE SEQUENCES

string selectTeamA(int n);
string selectTeamB(int n);
string selectTeamC(int n);

string selectTeamA(int n){
    if(n<0){
        error("a string containing your error message");
    }
    else{
        if(n==0){
            return "A";
        }
        else{
            return selectTeamA(n-1)+selectTeamB(n-1)+selectTeamC(n-1);
        }
    }

}

string selectTeamB(int n){
    if(n<0){
        error("a string containing your error message");
    }
    else{
        if(n==0){
            return "B";
        }
        else{
            return selectTeamB(n-1)+selectTeamC(n-1)+selectTeamA(n-1);
        }
    }

}

string selectTeamC(int n){
    if(n<0){
        error("a string containing your error message");
    }
    else{
        if(n==0){
            return "C";
        }
        else{
            return selectTeamC(n-1)+selectTeamA(n-1)+selectTeamB(n-1);
        }
    }

}









/* * * * * * Provided Test Cases * * * * * */

PROVIDED_TEST("Sequences of order 3 are correct.") {
    /* Some very basic checks. */
    EXPECT_EQUAL(aSequenceOfOrder(3), "ABBABAAB");
    EXPECT_EQUAL(bSequenceOfOrder(3), "BAABABBA");
}

PROVIDED_TEST("Only characters should be As and Bs.") {
    for (int i = 0; i < 10; i++) {
        for (char ch: aSequenceOfOrder(i)) {
            EXPECT(ch == 'A' || ch == 'B');
        }
    }
}

PROVIDED_TEST("A-sequence of positive order should have equal As and Bs.") {
    /* Exclude the sequence of order 0, which is just a single character. */
    for (int i = 1; i < 10; i++) {
        int as = 0;
        int bs = 0;
        for (char ch: aSequenceOfOrder(i)) {
            if (ch == 'A') as++;
            else bs++;
        }

        EXPECT_EQUAL(as, bs);
    }
}

PROVIDED_TEST("Triggers error on negative inputs.") {
    /* The EXPECT_ERROR macro expects the given expression to call error(). Remember that
     * you need to guard against invalid inputs.
     */
    EXPECT_ERROR(aSequenceOfOrder(-137));
    EXPECT_ERROR(bSequenceOfOrder(-137));
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

STUDENT_TEST("Try more cases"){
        EXPECT_EQUAL(aSequenceOfOrder(4), "ABBABAABBAABABBA");
        EXPECT_EQUAL(bSequenceOfOrder(4), "BAABABBAABBABAAB");
}

STUDENT_TEST("Generate recursive sequences for Team A, B, and C for fairness") {

    EXPECT_EQUAL(selectTeamA(2), "ABCBCACAB");
    EXPECT_EQUAL(selectTeamB(2), "BCACABABC");
    EXPECT_EQUAL(selectTeamC(2), "CABABCBCA");
}

STUDENT_TEST("Generate sequences of order 3 for Team A, B, and C") {
    EXPECT_EQUAL(selectTeamA(3), "ABCBCACABBCACABABCCABABCBCA");
    EXPECT_EQUAL(selectTeamB(3), "BCACABABCCABABCBCAABCBCACAB");
    EXPECT_EQUAL(selectTeamC(3), "CABABCBCAABCBCACABBCACABABC");
}


STUDENT_TEST("Check equal number of A, B, C characters in sequences of order 3") {
    string sequence = selectTeamA(10);
    int countA = 0, countB = 0, countC = 0;

    for (char ch : sequence) {
        if (ch == 'A') countA++;
        if (ch == 'B') countB++;
        if (ch == 'C') countC++;
    }

    EXPECT_EQUAL(countA, countB);
    EXPECT_EQUAL(countB, countC);
}







