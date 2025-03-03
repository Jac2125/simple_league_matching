#ifndef GROUP_H
#define GROUP_H

#include <vector>
using namespace std;

class Group {
    int queueNum;
    int totalPlayers = 0;
    vector<char> preferRoles;

public:
    // Constructor
    Group(int queueNum, int tot, vector<char> first)
        : queueNum(queueNum), totalPlayers(tot), preferRoles(first) {}

    // Get the size of the group
    int getSize() {
        return totalPlayers;
    }

    friend ostream& operator<<(ostream& os, const Group& group);

    // Iterator class
    class Iterator {
    private:
        vector<char>::iterator it; // Iterator for the preferRoles vector

    public:
        // Constructor
        explicit Iterator(vector<char>::iterator ptr) : it(ptr) {}

        // Dereference operator
        char& operator*() const {
            return *it;
        }

        // Pre-increment operator
        Iterator& operator++() {
            ++it;
            return *this;
        }

        // Post-increment operator
        Iterator operator++(int) {
            Iterator temp = *this;
            ++it;
            return temp;
        }

        // Equality operator
        bool operator==(const Iterator& other) const {
            return it == other.it;
        }

        // Inequality operator
        bool operator!=(const Iterator& other) const {
            return it != other.it;
        }
    };

    // Begin iterator
    Iterator begin() {
        return Iterator(preferRoles.begin());
    }

    // End iterator
    Iterator end() {
        return Iterator(preferRoles.end());
    }
};

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

#endif