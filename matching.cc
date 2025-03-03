#include <iostream>
#include "Group.h"
#include <random>
#include <algorithm>

using namespace std;

const int totalGroups = 100;
const int MAX_ITERATE = 10;

const int MAX_ROLES = 5;
const vector<char> ROLES = {'t', 'j', 'm', 'a', 's'};
const vector<double> ROLES_PROBABILITY = {0.23, 0.19, 0.25, 0.21, 0.12};

const vector<int> GROUP_SIZE = {1, 2};
const vector<double> GROUP_SIZE_PROBABILITY ={0.6, 0.4};

// Function to choose an element based on given probabilities
template <typename T>
T chooseElement(const vector<T>& elements, const vector<double>& probabilities) {
    // Check if the sizes of elements and probabilities match
    if (elements.size() != probabilities.size()) {
        throw invalid_argument("Elements and probabilities must have the same size.");
    }

    // Check if probabilities sum to 1 (or close to it)
    double sum = accumulate(probabilities.begin(), probabilities.end(), 0.0);
    if (abs(sum - 1.0) > 1e-6) {
        throw invalid_argument("Probabilities must sum to 1.");
    }

    // Random number generator
    static random_device rd;
    static mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);

    // Generate a random number between 0 and 1
    double randomValue = dis(gen);

    // Cumulative probability calculation
    double cumulativeProbability = 0.0;
    for (size_t i = 0; i < elements.size(); ++i) {
        cumulativeProbability += probabilities[i];
        if (randomValue <= cumulativeProbability) {
            return elements[i];
        }
    }

    // Fallback (should not reach here if probabilities are valid)
    return elements.back();
}



void deleteElement(char &c, vector<char>& roles, vector<double>& probs){
    for(int i = 0; i < roles.size(); i++){
        if(roles.at(i) == c){
            roles.erase(roles.begin() + i);
            probs.erase(probs.begin() + i);
            double sum = 0;
            for(int j = 0; j < probs.size(); j++){
                sum += probs.at(j);
            }

            for(int k = 0; k < probs.size(); k++){
                probs[k] /= sum;
            }
            return;
        }
    }
}

void genGroups(vector<Group>& groups){
    for(int i  = 0; i < totalGroups; i++){
        int gpSize = chooseElement(GROUP_SIZE, GROUP_SIZE_PROBABILITY);
        
        vector<char> selectedRoles{};
        vector<char> unselectedRoles = ROLES;
        vector<double> unselectedProbs = ROLES_PROBABILITY;

        for(int j = 0; j < gpSize; j++){
            char role = chooseElement(unselectedRoles, unselectedProbs);
            selectedRoles.push_back(role);
            deleteElement(role, unselectedRoles, unselectedProbs);
        }
        Group gp{i, gpSize, selectedRoles};
        groups.push_back(gp);
    }
}

int addGroupGreedy(int pivot, vector<Group>& groups, vector<Group>& selectedGroup, vector<char>& unselectedRoles){
    for(int i = pivot; i < MAX_ITERATE; i++){
        pivot++;
        Group g = groups.at(i);
        int halt = 0;
        for(auto it = g.begin(); it != g.end(); it++){
            auto it2 = find(unselectedRoles.begin(), unselectedRoles.end(), *it);
            if(it2 != unselectedRoles.end()){
                halt = 1;
                break;
            }
        }

        if(halt) continue;

        selectedGroup.push_back(g);
        for(char r : g){
            for(int i = 0; i < unselectedRoles.size(); i++){
                if(unselectedRoles.at(i) == r){
                    unselectedRoles.erase(unselectedRoles.begin() + i);
                    break;
                }
            }
        } 
    }
    return pivot;
}

int main(){
    int pivot = 0;
    vector<Group> groups{};
    genGroups(groups);
    vector<Group> selected{};
    vector<char> unselected = ROLES;
    while(pivot != totalGroups){
        pivot = addGroupGreedy(pivot, groups, selected, unselected);
    }

}
