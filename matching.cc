#include <iostream>
#include "Group.h"
#include <random>

using namespace std;

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


int main(){
    
}
