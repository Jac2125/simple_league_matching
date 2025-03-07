#include "Group.h"

// Definition of the << operator
ostream& operator<<(ostream& os, const Group& group) {
    os << "Queue Number: " << group.queueNum << endl;
    os << "Total Players: " << group.totalPlayers << endl;
    os << "Preferred Roles: ";
    for (char role : group.preferRoles) {
        os << role << " ";
    }
    os << endl;
    return os;
}
