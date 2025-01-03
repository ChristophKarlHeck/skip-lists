#include <cmath> // For std::log
#include <iostream>
#include <iomanip> // For std::setw

#include "DetSkipLists.h"

int DetSkipLists::CalculateNumberOfLists(int n){
    
    // log2(n) <= i
    double log2 = std::log2(n);
    // Round floating-point number up to the nearest integer.
    int i = static_cast<int>(std::ceil(log2));

    return i;

}

void DetSkipLists::BuildSkipLists(void) {

    // Create nodes for all elements in the set
    for (auto value : elements) {

        nodes.push_back(SkipListNode(value, numberOfLists));
    }

    // Build the levels
    for (int level = 0; level < numberOfLists; ++level) {

        int step = pow(2,level); // 2^level

        for (size_t i = 0; i < nodes.size(); i += step) {

            if (i + step < nodes.size()) {

                // Get the next vector of the current node
                auto& nextVector = nodes[i].getNext();
                
                // Update the next pointer for the current level
                nextVector[level] = &nodes[i + step];
                
                // Set the updated next vector back to the node
                nodes[i].setNext(nextVector);
            }
        }
    }

    // Connect head to the first node
    for (int level = 0; level < numberOfLists; ++level) {
        if (!nodes.empty()) {
            // Get the next vector of the head node
            auto& headNext = head.getNext();

            // Set the next pointer at the current level to the first node in the list
            headNext[level] = &nodes[0];

            // Update the head's next vector
            head.setNext(headNext);
        }
    }
}

void DetSkipLists::print() {
    std::cout << "Skip List Levels:\n";

    for (int level = numberOfLists - 1; level >= 0; --level) {
        std::cout << "Level " << level << ": ";

        SkipListNode* current = &head; // Start from the head node
        while (current) {
            if (current != &head) { // Skip printing the dummy head's value
                std::cout << std::setw(3) << current->getValue() << " ";
            }

            // Access the next vector directly
            current = current->getNext()[level];
        }

        std::cout << std::endl;
    }
}


DetSkipLists::DetSkipLists(std::set<int> S):
    elements(S),
    head(SkipListNode(-1, CalculateNumberOfLists(S.size()))),
    nodes(),
    numberOfLists(CalculateNumberOfLists(S.size()))
{
    BuildSkipLists();            
}