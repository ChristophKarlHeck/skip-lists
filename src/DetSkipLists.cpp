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

    // Build SkipLists
    for (int level = 0; level < numberOfLists; level++) {

        int step = pow(2,level); // 2^level

        auto& nextVector = head.getNext();
        nextVector[level] = &nodes[step-1];
        head.setNext(nextVector);

        for (size_t i = step-1; i < nodes.size(); i += step) {

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

}

void DetSkipLists::print() {
    // Collect all node values from level 0
    std::vector<int> level0Positions;
    SkipListNode* current = &head;
    while (current) {
        if (current != &head) { // Skip the dummy head node
            level0Positions.push_back(current->getValue());
        }
        current = current->getNext()[0];
    }

    // Print each level
    for (int level = numberOfLists - 1; level >= 0; --level) {
        std::cout << "Level " << level << ": ";

        current = &head; // Start from the head for each level
        size_t positionIndex = 0;

        while (current) {
            // Move to the next node at the current level
            current = current->getNext()[level];

            if (!current) break;

            // Align the node's position to level 0
            while (positionIndex < level0Positions.size() &&
                   level0Positions[positionIndex] < current->getValue()) {
                std::cout << std::setw(4) << " "; // Print spacing for alignment
                ++positionIndex;
            }

            // Print the node's value
            std::cout << std::setw(4) << current->getValue();
            ++positionIndex;
        }

        std::cout << std::endl;
    }
}


DetSkipLists::DetSkipLists(std::set<int> S):
    elements(S),
    head(SkipListNode(-1, CalculateNumberOfLists(S.size()) + 1)),
    nodes(),
    numberOfLists(CalculateNumberOfLists(S.size() + 1))
{
    BuildSkipLists();            
}