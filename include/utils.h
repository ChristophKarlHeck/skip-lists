#ifndef UTILS_H
#define UTILS_H

#include <set>

// Function to create a random set with n unique numbers in the range [lower, upper]
std::set<int> createRandomSet(int n, int lower = 1, int upper = 100);

#endif // UTILS_H