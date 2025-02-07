#ifndef UTILS_H
#define UTILS_H

#include <set>

class Utils {
public:
    // Function to create a random set with n unique numbers
    static std::set<int> createRandomSet(int n);

    // Function to get a random element from a given set
    static int getRandomElementInSet(const std::set<int>& S);

    // Function to get a random element not in a given set
    static int getRandomElementNotInSet(const std::set<int>& S, int n);
};

#endif // UTILS_H