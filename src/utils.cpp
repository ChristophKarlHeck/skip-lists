#include "utils.h"

#include <iostream>
#include <random>
#include <algorithm>

// Function to create a random set with n unique numbers
std::set<int> createRandomSet(int n, int lower, int upper) {
    std::set<int> randomSet;
    std::random_device rd;  // Seed for random number generation
    std::mt19937 gen(rd()); // Mersenne Twister random number generator
    std::uniform_int_distribution<> dis(lower, upper);

    while (randomSet.size() < n) {
        randomSet.insert(dis(gen)); // Insert a random number
    }

    return randomSet;
}