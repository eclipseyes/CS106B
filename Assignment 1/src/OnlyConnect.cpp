/* File: OnlyConnect.cpp
 *
 * TODO: Edit these comments to describe anything interesting or noteworthy in your implementation.
 *
 * TODO: Edit these comments to leave a puzzle for your section leader to solve!
 */
#include "OnlyConnect.h"
#include "GUI/SimpleTest.h"
#include <string>
#include <ctype.h>
#include <strlib.h>
#include <stdbool.h>
#include <cstdlib>
#include <ctime>
#include <vector>


using namespace std;


/*          B   A   S   I   C          F   U  N  C  T  I  O  N  S       */

/* Helper function to check if a character is a vowel */
bool IsVowel(char ch){
    ch=tolower(ch);
    if(ch=='a'||ch=='e'||ch=='i'||ch=='o'||ch=='u'){
        return true;
    }
    else
        return false;
}

/* Function to transform a string into a consonant-only uppercase version, skipping vowels and non-letter characters. */
string onlyConnectize(string phrase) {
    /* TODO: The next few lines just exist to make sure you don't get compiler warning messages
     * when this function isn't implemented. Delete these lines, then implement this function.
     */
    if(phrase.empty()){
        return "";  //Base case:empty string
    }
    if(isalpha(phrase[0])){
        if(!IsVowel(phrase[0])){
            return charToString(toUpperCase(phrase[0])) + onlyConnectize(phrase.substr(1));
        }
        else{
            return onlyConnectize(phrase.substr(1));
        }
    }
    else{
        return onlyConnectize(phrase.substr(1));
    }
}

/*   E X T E N S I O N  1   :   R A N D O M   S P A C E   G E N E R A T O R   */

/* Helper function to insert random spaces in a string */
string insertRandomSpaces(string str) {
    // Base case: if the string is empty or contains only one character, return it as is.
    if (str.length() <= 1) {
        return str;
    }

    // Randomly decide whether to insert a space
    if (rand() % 2 == 0) {
        return charToString(str[0]) + insertRandomSpaces(str.substr(1));  // No space
    } else {
        return charToString(str[0]) + " " + insertRandomSpaces(str.substr(1));  // Insert space
    }
}
/* Extended onlyConnectize function with random spaces */
string onlyConnectizeWithSpaces(string phrase) {
    string result = onlyConnectize(phrase);  // First, transform to consonant-only uppercase
    return insertRandomSpaces(result);       // Then insert random spaces
}


/*   E  X  T  E  N  S  I  O   N    2   :   G   U   E   S   S       G    A    M    E    */
vector<string> phrases = {
    "To be or not to be",
    "A quick brown fox jumps over the lazy dog",
    "Elementary my dear Watson",
    "Houston we have a problem",
    "May the force be with you"
};

void startGuessingGame(){
    srand(time(0)); //seed for random number generator
    int randomIndex;
    randomIndex=rand()%phrases.size();
    string selectedPhrase=phrases[randomIndex];

    //Convert phrase using onlyConnectize
    string transformedPhrase= onlyConnectize(selectedPhrase);
    cout << "Can you guess the original phrase from this consonant-only version?\n";
    cout << transformedPhrase << endl;

    string userGuess;
    cout<<"Your guess:";
    getline(cin,userGuess);

    if(toLowerCase(userGuess)==toLowerCase(selectedPhrase)){
        cout<<"Correct! the original phrase was:"<<selectedPhrase<<endl;

    }else{
        cout<<"Sorry, the correct answer was:"<<selectedPhrase<<endl;

    }
}
/* * * * * * Provided Test Cases * * * * * */

PROVIDED_TEST("Converts lower-case to upper-case.") {
    EXPECT_EQUAL(onlyConnectize("lowercase"), "LWRCS");
    EXPECT_EQUAL(onlyConnectize("uppercase"), "PPRCS");
}

PROVIDED_TEST("Handles non-letter characters properly.") {
    EXPECT_EQUAL(onlyConnectize("2.718281828459045"), "");
    EXPECT_EQUAL(onlyConnectize("'Hi, Mom!'"), "HMM");
}

PROVIDED_TEST("Handles single-character inputs.") {
    EXPECT_EQUAL(onlyConnectize("A"), "");
    EXPECT_EQUAL(onlyConnectize("+"), "");
    EXPECT_EQUAL(onlyConnectize("Q"), "Q");
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

/* Student tests */

STUDENT_TEST("Handles an empty string.") {
    EXPECT_EQUAL(onlyConnectize(""), "");
}

STUDENT_TEST("Handles a string with all vowels.") {
    EXPECT_EQUAL(onlyConnectize("aeiouAEIOU"), "");
}

STUDENT_TEST("Handles a string with mixed vowels and consonants.") {
    EXPECT_EQUAL(onlyConnectize("Quick Brown Fox"), "QCKBRWNFX");
}

STUDENT_TEST("Handles non-letters at the start and end.") {
    EXPECT_EQUAL(onlyConnectize("!Welcome!"), "WLCM");
}

STUDENT_TEST("Handles long strings.") {
    EXPECT_EQUAL(onlyConnectize("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"), "BCDFGHJKLMNPQRSTVWXYZBCDFGHJKLMNPQRSTVWXYZ");
}

STUDENT_TEST("Randomly inserts spaces in consonant-only string.") {
    string result = onlyConnectizeWithSpaces("Quick Brown Fox");
    EXPECT(result.find("Q") != string::npos);  // make sure the original letter is still here
    EXPECT(result.find("C") != string::npos);  // make sure the original letter is still here
    EXPECT(result.find("K") != string::npos);  // make sure the original letter is still here
    EXPECT(result.find("N") != string::npos);  // make sure the original letter is still here
    EXPECT(result.find("B") != string::npos);  // make sure the original letter is still here
    EXPECT(result.find(" ") != string::npos);  // make sure spaces are inserted
}

STUDENT_TEST("TEST THE GUESS GAME") {
    // Start the guessing game
    startGuessingGame();
}





