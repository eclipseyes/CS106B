#pragma once

#include "set.h"
#include <string>
#include <ostream>

/* Type representing a triad of a doctor, a
 * resident, and a patient.
 */
struct Triad {
    std::string doctor;
    std::string resident;
    std::string patient;
};

Set<Set<Triad>> allCareTeamsFor(const Set<std::string>& doctors,
                                const Set<std::string>& residents,
                                const Set<std::string>& patients);


/* These operators are needed to store Triads in a Set or as a
 * key in a Map. You aren't expected to use or modify this code
 * directly.
 */
bool operator< (const Triad& lhs, const Triad& rhs);
bool operator> (const Triad& lhs, const Triad& rhs);
bool operator>= (const Triad& lhs, const Triad& rhs);
bool operator<= (const Triad& lhs, const Triad& rhs);
bool operator== (const Triad& lhs, const Triad& rhs);
bool operator!= (const Triad& lhs, const Triad& rhs);
std::ostream& operator<< (std::ostream& out, const Triad& t);
