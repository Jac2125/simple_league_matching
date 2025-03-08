#include "matching.h"
#include <iostream>
#include <random>
#include <algorithm>
#include <numeric>

using namespace std;

int totalGroups = 2000;
int MAX_ITERATE = 2000;

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
    for(int i = 0; i < static_cast<int>(roles.size()); i++){
        if(roles.at(i) == c){
            roles.erase(roles.begin() + i);
            probs.erase(probs.begin() + i);
            double sum = 0;
            for(int j = 0; j < static_cast<int>(probs.size()); j++){
                sum += probs.at(j);
            }

            for(int k = 0; k < static_cast<int>(probs.size()); k++){
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

int addGroupGreedy(int pivot, vector<Group>& groups, vector<Group>& selectedGroup, vector<char>& unselectedRoles) {
    int success = 0;
    vector<int> adjustment;

    int limit = min(static_cast<int>(groups.size()), pivot + MAX_ITERATE); // Ensure correct limit

    for (int i = pivot; i < limit; i++) {
        Group& g = groups[i];

        // Corrected `all_of` usage
        if (!all_of(g.begin(), g.end(), [&](const char& role) {
            return find(unselectedRoles.begin(), unselectedRoles.end(), role) != unselectedRoles.end();
        })) {
            continue;
        }

        // Add group to selected list
        selectedGroup.push_back(g);
        adjustment.push_back(i);

        // Remove roles from unselectedRoles
        for (char r : g) {
            unselectedRoles.erase(remove(unselectedRoles.begin(), unselectedRoles.end(), r), unselectedRoles.end());
        }

        if (unselectedRoles.empty()) {
            success = 1;
            break;
        }
    }

    if (success) {
        // Erase in reverse order to prevent shifting issues
        reverse(adjustment.begin(), adjustment.end());
        for (int i : adjustment) {
            groups.erase(groups.begin() + i);
        }
    } else {
        selectedGroup.clear();
    }

    return success;
}

