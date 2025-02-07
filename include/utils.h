#ifndef UTILS_H
#define UTILS_H

#include <set>

class Utils {
public:
    // Function to create a random set with n unique numbers
    static std::set<int> createRandomSet(int n);

    // Function to get a random element from a given set
    static int getRandomElement(const std::set<int>& S);
};

#endif // UTILS_H