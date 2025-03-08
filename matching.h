#ifndef MATCHING_H
#define MATCHING_H

#include <vector>
#include "Group.h"

using namespace std;

extern int totalGroups;
extern int MAX_ITERATE;
extern const int MAX_ROLES;
extern const vector<char> ROLES;
extern const vector<double> ROLES_PROBABILITY;
extern const vector<int> GROUP_SIZE;
extern const vector<double> GROUP_SIZE_PROBABILITY;

template <typename T>
T chooseElement(const vector<T>& elements, const vector<double>& probabilities);

void deleteElement(char &c, vector<char>& roles, vector<double>& probs);
void genGroups(vector<Group>& groups);
int addGroupGreedy(int pivot, vector<Group>& groups, vector<Group>& selectedGroup, vector<char>& unselectedRoles);

#endif
