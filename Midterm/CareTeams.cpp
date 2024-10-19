#include "CareTeams.h"
#include <error.h>
#include <vector.h>
using namespace std;

Set<Set<Triad>> allCareTeamsFor(const Set<string>& doctors,
                                const Set<string>& residents,
                                const Set<string>& patients) {
    /* Check for balance. */
    if (doctors.size() != residents.size() ||
        residents.size() != patients.size()) {
        error("Can't form triads from everyone in this setup.");
    }

    /* If there are no people, there is exactly one partition, namely,
     * a partition that involves no people.
     */
    if (doctors.isEmpty()) {
        return { { } };        //{ {方法1}{方法2}}
    }                             //{ {triad1,triad2,triad3,triad4},{e,d,f}}

    Set<Set<Triad>> result;

    /* Otherwise, pick a doctor and form all possible triads around
     * them.
     */
    string doctor = doctors.first();
    for (string resident: residents) {
        for (string patient: patients) {
            Triad triad = { doctor, resident, patient };
            /* Now, recursively find all partitions of everyone
             * except for these three people.
             */
            auto rest = allCareTeamsFor(doctors - doctor,
                                        residents - resident,
                                        patients - patient);
            /* Each of these options exactly leaves out the triad
             * from above. So add those back in!
             */
            for (Set<Triad> partition: rest) {
                result.add(partition + triad);
            }
        }
    }

    /* We've now gathered all possible options, since the
     * doctor we singled out has to appear in all of them.
     */
    return result;
}

/************************************************************************
 * You are encouraged to - but not required to - add custom tests here. *
 ************************************************************************/

#include "GUI/SimpleTest.h"
