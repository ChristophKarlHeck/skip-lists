#include "utils.h"
#include <random>
#include <stdexcept>
#include <iterator>

// Function to create a random set with n unique numbers
std::set<int> Utils::createRandomSet(int n) {

    std::set<int> randomSet;

    // std::random_device is a uniformly-distributed integer random number generator
    // that produces non-deterministic random numbers
    // Seed for random number generation -> same seed -> same sequence of random number
    std::random_device rd;  

    // mersenne_twister_engine is a random number engine based
    // on Mersenne Twister algorithm. It produces unsigned integer random numbers
    // of type UIntType (32-bit) on the interval [0,2^w) w=word size=32
    std::mt19937 gen(rd());

    // Produces random integer values i, uniformly distributed on the closed interval [1, n*10]
    std::uniform_int_distribution<> dis(1, n * 10); // Range: 

    // while since insert fails silently if input is already in set
    while (randomSet.size() < n) {
        // dis takes the raw random bits from gen and scales them to fit the desired range [1, n*10]
        randomSet.insert(dis(gen)); // Insert a random number
    }

    return randomSet;
}

// Function to get a random element from a given set
int Utils::getRandomElement(const std::set<int>& S) {

    if (S.empty()) {
        throw std::runtime_error("Set is empty");
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist(0, S.size() - 1);

    auto it = std::next(S.begin(), dist(gen));
    return *it;
}