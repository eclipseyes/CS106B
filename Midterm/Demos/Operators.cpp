/* This file contains implementations of helper functions
 * that are needed for our custom types to work. You
 * aren't expected to read, modify, or directly use the
 * functions defined here.
 */

#include "CareTeams.h"
#include "vector.h"
using namespace std;

bool operator< (const Triad& lhs, const Triad& rhs) {
    if (lhs.doctor != rhs.doctor) {
        return lhs.doctor < rhs.doctor;
    }
    if (lhs.resident != rhs.resident) {
        return lhs.resident < rhs.resident;
    }
    return lhs.patient < rhs.patient;
}
bool operator> (const Triad& lhs, const Triad& rhs) {
    return rhs < lhs;
}
bool operator>= (const Triad& lhs, const Triad& rhs) {
    return !(lhs < rhs);
}
bool operator<= (const Triad& lhs, const Triad& rhs) {
    return !(rhs < lhs);
}
bool operator== (const Triad& lhs, const Triad& rhs) {
    return lhs.doctor   == rhs.doctor &&
           lhs.resident == rhs.resident &&
           lhs.patient  == rhs.patient;
}
bool operator!= (const Triad& lhs, const Triad& rhs) {
    return !(lhs == rhs);
}
ostream& operator<< (ostream& out, const Triad& t) {
    return out << Vector<string>{t.doctor, t.resident, t.patient};
}
