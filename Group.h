#ifndef GROUP_H
#define GROUP_H

#include <vector>
#include <ostream>
using namespace std;

class Group {
    int queueNum;
    int totalPlayers = 0;
    vector<char> preferRoles;

public:
    Group(int queueNum, int tot, vector<char> first)
        : queueNum(queueNum), totalPlayers(tot), preferRoles(first) {}

    int getSize() { return totalPlayers; }

    vector<char>& getRole() { return preferRoles; }

    // ✅ Use vector's built-in iterators
    vector<char>::iterator begin() { return preferRoles.begin(); }
    vector<char>::iterator end() { return preferRoles.end(); }
    vector<char>::const_iterator begin() const { return preferRoles.begin(); }
    vector<char>::const_iterator end() const { return preferRoles.end(); }

    friend ostream& operator<<(ostream& os, const Group& group);
};



#endif