#include <iostream>
#include "matching.h"

using namespace std;


int main(){
    
    vector<Group> groups{};
    genGroups(groups);
    Group g1 = Group{0,2,{'t', 'j'}};
    Group g2 = Group{1,2,{'m', 'a'}};
    Group g3 = Group{2,1,{'s'}};
    
    //groups.push_back(g1);
    //groups.push_back(g2);
    //groups.push_back(g3);

    vector<vector<Group>> matchingResult{};
    int pivot = 0;
    while((pivot + 1 <= groups.size())){
        
        vector<Group> selectedGroups{};
        vector<char> unselectedRoles{ROLES};
        //cout << pivot << endl;
        if(!addGroupGreedy(pivot, groups, selectedGroups, unselectedRoles)) pivot++;
        else pivot = 0;
        //cout << "Done Adding" << endl;
        if(unselectedRoles.empty()) matchingResult.push_back(selectedGroups);
    }
    
    for(Group g : groups){
        cout << g;
    }

    cout << endl << endl;

    for(vector<Group> gVector : matchingResult){
        for(Group g : gVector){
            cout << g;
        }
        cout << endl;
    }
    

    return 0;
}