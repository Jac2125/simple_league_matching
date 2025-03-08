#include <iostream>
#include "matching.h"
#include <chrono>

using namespace std;
using namespace std::chrono;

bool verifier(vector<vector<Group>>& matchings){
    for(vector<Group> team : matchings){
        vector<char> totalRoles{ROLES};
        for(Group g : team){
            
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    // Accept totalGroups as a command-line argument
    if (argc > 1) {
        totalGroups = MAX_ITERATE = stoi(argv[1]);  // Convert argument to int
    }
    
    vector<Group> groups{};
    genGroups(groups);

    vector<vector<Group>> matchingResult{};
    int pivot = 0;
    auto start = high_resolution_clock::now();
    while((pivot + 1 <= static_cast<int>(groups.size()))){
        
        vector<Group> selectedGroups{};
        vector<char> unselectedRoles{ROLES};
        //cout << pivot << endl;
        if(!addGroupGreedy(pivot, groups, selectedGroups, unselectedRoles)) pivot++;
        else pivot = 0;
        //cout << "Done Adding" << endl;
        if(unselectedRoles.empty()) matchingResult.push_back(selectedGroups);
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << duration.count() << endl;
    return 0;
}