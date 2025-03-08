#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include "matching.h"

using namespace std;
using namespace std::chrono;

// Function to compute mean
template<typename T>
T computeMean(const vector<T>& array) {
    double sum = 0;
    for (T t : array) sum += t;
    return sum / array.size();
}

// Function to compute median
template<typename T>
T computeMedian(vector<T> times) {
    sort(times.begin(), times.end());
    size_t n = times.size();
    if (n % 2 == 0)
        return (times[n / 2 - 1] + times[n / 2]) / 2.0;
    return times[n / 2];
}

int main() {
    vector<int> testSizes = {10, 20, 50, 100, 200, 500, 1000, 3000}; // Different values for totalGroups
    int iterationsPerSize = 5;  // Number of runs per totalGroups

    vector<int> unmatchedGroups{};

    for (int testSize : testSizes) {
        totalGroups = testSize;
        
        vector<double> times;
        vector<int> unmatchedG;

        for (int i = 0; i < iterationsPerSize; i++) {
            vector<Group> groups;
            genGroups(groups);  // Generate groups
            auto start = high_resolution_clock::now();
            
            vector<vector<Group>> matchingResult;
            int pivot = 0;

            while (pivot < groups.size()) {
                vector<Group> selectedGroups;
                vector<char> unselectedRoles = ROLES;

                if (!addGroupGreedy(pivot, groups, selectedGroups, unselectedRoles)) {
                    pivot++;
                } else {
                    pivot = 0;
                }

                if (unselectedRoles.empty()) {
                    matchingResult.push_back(selectedGroups);
                }
            }

            auto stop = high_resolution_clock::now();
            double duration = duration_cast<milliseconds>(stop - start).count();
            times.push_back(duration);
            unmatchedG.push_back(groups.size());
        }

        // Compute and display stats
        double mean = computeMean(times);
        double median = computeMedian(times);
        double unmatchedGroupMean = computeMean(unmatchedG);
        double minTime = *min_element(times.begin(), times.end());
        double maxTime = *max_element(times.begin(), times.end());

        cout << "Results for totalGroups = " << testSize << ":\n";
        cout << "  Mean Time:   " << mean << " ms\n";
        cout << "  Median Time: " << median << " ms\n";
        cout << "  Min Time:    " << minTime << " ms\n";
        cout << "  Max Time:    " << maxTime << " ms\n";
        cout << "  Unmatched Groups Mean: " << unmatchedGroupMean << endl << endl;
    }

    return 0;
}
